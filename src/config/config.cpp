#include <string>

#include "config/config.h"

#include "lua/api.h"
#include "lua/exception.h"

namespace config{
    Config::Config(const std::string& path) : L(luaL_newstate())
    {
        int error = luaL_dofile(L, path.c_str());
        if(error != 0)
            throw lua::LuaException(error, lua_tostring(L, -1));
    }

    Config::Config(const Config& parent, const std::string& key) : L(parent.L)
    {
    }

    Config::~Config()
    {
        lua_close(L);
    }

    ConfigValue Config::getValue(const std::string& key)
    {
        lua_getglobal(L, key.c_str());
        ConfigValue v(L, -1);
        lua_pop(L, 1);

        return v;
    }

    ConfigValue Config::operator[](const std::string& key)
    {
        return getValue(key);
    }

    Config Config::getSub(const std::string& key)
    {
        return Config(*this, key);
    }

    std::string Config::get(const std::string& key, const std::string& def)
    {
        ConfigValue v = getValue(key);
        return v.isNull()? def : v.string();
    }

    double Config::get(const std::string& key, double def)
    {
        ConfigValue v = getValue(key);
        return v.isNull()? def : v.number();
    }

    int Config::get(const std::string& key, int def)
    {
        ConfigValue v = getValue(key);
        return v.isNull()? def : v.integer();
    }

    bool Config::get(const std::string& key, bool def)
    {
        ConfigValue v = getValue(key);
        return v.isNull()? def : v.boolean();
    }
}
