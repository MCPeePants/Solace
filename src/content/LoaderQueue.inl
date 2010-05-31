#include <map>
#include <queue>

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

#define ResLoaderQueue(ret) template<typename restype> ret Resource<restype>::Manager::Loader::LoaderQueue
//#define ResLoaderQueueSpec(ret, spec) template<> ret Resource<spec>::Manager::Loader::LoaderQueue
#define NULLARG

ResLoaderQueue(NULLARG)::LoaderQueue(SizeType n)
{
  innerQueue.reserve(n);
}

ResLoaderQueue(NULLARG)::~LoaderQueue(){}

#undef NULLARG

template<typename restype>
typename Resource<restype>::Manager::Loader::LoaderQueue::Queue::value_type::first_type&
Resource<restype>::Manager::Loader::LoaderQueue::operator[](SizeType n)
{
#ifdef DEBUG
  assert(n < outerSize);
#endif
  return innerQueue[n].first();
}

ResLoaderQueue(SizeType)::getSize()
{
  ScopedLock(brb);
  return innerQueue.size();
}

ResLoaderQueue(SizeType)::getCapacity()
{
  ScopedLock(brb);
  return innerQueue.capacity();
}

#undef ResLoaderQueue
#undef ResLoaderQueueSpec