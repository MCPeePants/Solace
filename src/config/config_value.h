#ifndef SLC_CONFIG_CONFIG_VALUE_H
#define SLC_CONFIG_CONFIG_VALUE_H

#include <string>

struct lua_State;

namespace config{
    namespace ConfigType
    {
        enum Type
        {
            None,
            String,
            Number,
            Boolean
        };
    }

    class ConfigValue
    {
        private:
        friend class Config;

        ConfigValue(lua_State* L, int index = -1);
        void assertType(ConfigType::Type t);

        ConfigType::Type type;
        union
        {
            const char* m_string;
            double m_number;
            bool m_boolean;
        };

        public:
        ConfigType::Type getType();

        bool isNull();

        std::string string();
        double number();
        int integer();
        bool boolean();
    };
}

#endif
