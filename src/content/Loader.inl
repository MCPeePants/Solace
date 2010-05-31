#include <map>
#include <queue>

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

#define ResLoader(ret) template<typename restype> ret Resource<restype>::Manager::Loader
//#define ResLoaderSpec(ret, spec) template<> ret Resource<spec>::Manager::Loader
#define NULLARG

ResLoader(NULLARG)::Loader()
  :loadQueue(){}

ResLoader(NULLARG)::~Loader(){}

#undef NULLARG

#undef ResLoader
#undef ResLoaderSpec