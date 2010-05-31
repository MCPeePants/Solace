#include <map>
#include <queue>

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

#define Res(ret) template<typename restype> ret Resource<restype>
//#define ResourceSpec(ret, spec) template<> ret Resource<spec>
#define NULLARG

Res(NULLARG)::Resource(){}

Res(NULLARG)::~Resource(){}

#undef NULLARG

#undef Resource
#undef ResourceSpec