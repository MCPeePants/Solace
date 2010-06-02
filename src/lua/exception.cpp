#include <exception>

#include "lua/exception.h"
#include "lua/api.h"

namespace lua{
    LuaException::LuaException(int error, const char* what)
    {
        m_what = what;
        m_error = error;
    }

    const char* LuaException::what() const throw()
    {
        return m_what;
    }

    int LuaException::errorCode() const throw()
    {
        return m_error;
    }
}
