#ifndef SLC_CONFIG_CONFIG_H
#define SLC_CONFIG_CONFIG_H

#include<string>

#include "config/config_value.h"

struct lua_State;

namespace config{
    class Config
    {
        public:
        Config(const std::string& path);
        virtual ~Config();

        ConfigValue getValue(const std::string& key);
        ConfigValue operator[](const std::string& key);

        private:
        lua_State* L;
        int env;
    };
}

#endif
