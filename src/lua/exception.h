#ifndef SLC_LUA_EXCEPTION_H
#define SLC_LUA_EXCEPTION_H

#include <exception>

namespace lua{
    class LuaException : public std::exception
    {
        private:
        const char* m_what;
        int m_error;

        public:
        LuaException(int error, const char* msg);

        virtual const char* what() const throw();
        int errorCode() const throw();
    };
}
#endif
