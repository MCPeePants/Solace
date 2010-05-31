#include <map>
#include <queue>

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

#define ResManager(ret) template<typename restype> ret Resource<restype>::Manager
//#define ResManagerSpec(ret, spec) template<> ret Resource<spec>::Manager
#define NULLARG

ResManager(NULLARG)::Manager(){}
ResManager(NULLARG)::~Manager(){}

#undef NULLARG

#undef ResManager
#undef ResManagerSpec