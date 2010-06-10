#include <string>
#include <stdexcept>

#include "config/config_value.h"
#include "lua/api.h"

namespace config{
    ConfigValue::ConfigValue(lua_State* L, int index)
    {
        switch(lua_type(L, index))
        {
            case LUA_TSTRING:
                type = ConfigType::String;
                m_string = lua_tostring(L, index);
                break;

            case LUA_TNUMBER:
                type = ConfigType::Number;
                m_number = lua_tonumber(L, index);
                break;

            case LUA_TBOOLEAN:
                type = ConfigType::Boolean;
                m_boolean = lua_toboolean(L, index);
                break;

            default:
                type = ConfigType::None;
        };
    }

    void ConfigValue::assertType(ConfigType::Type t)
    {
        // TODO: improve
        if(isNull())
            throw std::runtime_error("Configuration value not set");
        else if(t != type)
            throw std::runtime_error("Configuration value type mis-match");
    }

    bool ConfigValue::isNull()
    {
        return type == ConfigType::None;
    }

    ConfigType::Type ConfigValue::getType()
    {
        return type;
    }

    std::string ConfigValue::string()
    {
        assertType(ConfigType::String);
        return m_string;
    }

    double ConfigValue::number()
    {
        assertType(ConfigType::Number);
        return m_number;
    }

    int ConfigValue::integer()
    {
        assertType(ConfigType::Number);
        return static_cast<int>(m_number);
    }

    bool ConfigValue::boolean()
    {
        assertType(ConfigType::Boolean);
        return m_boolean;
    }
}
