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

        Config getSub(const std::string& key);

        std::string get(const std::string& key, const std::string& def);
        double get(const std::string& key, double def);
        int get(const std::string& key, int def);
        bool get(const std::string& key, bool def);

        private:
        Config(const Config& parent, const std::string& key);
        lua_State* L;
        int env;
    };
}

#endif
