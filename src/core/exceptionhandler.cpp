#include <cstdlib>
#include <exception>
#include <iostream>

#include "core/staticconstructor.h"

static void terminate()
{
    try
    {
        throw;
    }
    catch(std::exception& ex)
    {
        std::cerr << "Unhandled exception :: " << ex.what() << std::endl;
    }
    catch(...)
    {
        std::cerr << "Unknown exception occurred\n";
        std::abort();
    }

    std::exit(1);
}

STATIC_INIT()
{
    std::set_terminate(terminate);
}
