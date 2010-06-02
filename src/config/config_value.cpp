#include <string>
#include <stdexcept>

#include "config/config_value.h"
#include "lua/api.h"

namespace config{
    ConfigValue::ConfigValue(lua_State* L, int index)
    {
        switch(lua_type(L, -1))
        {
            case LUA_TSTRING:
                type = ConfigType::String;
                m_string = lua_tostring(L, -1);
                break;

            case LUA_TNUMBER:
                type = ConfigType::Number;
                m_number = lua_tonumber(L, -1);
                break;

            case LUA_TBOOLEAN:
                type = ConfigType::Boolean;
                m_boolean = lua_toboolean(L, -1);
                break;

            default:
                type = ConfigType::None;
        };
    }

    void ConfigValue::assertType(ConfigType::Type t)
    {
        if(t != type)
            throw std::runtime_error("Config value type mis-match"); //TODO: improve
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
