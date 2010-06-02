#include <map>
#include <queue>

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

template<typename resourceType, typename outerType>
Resource<resourceType, outerType>::Loader::LoaderQueue::LoaderQueue(SizeType capacity)
{
  // TODO: can we not reserve memory? ;z33ky
  //innerQueue.reserve(capacity);
}

template<typename resourceType, typename outerType>
Resource<resourceType, outerType>::Loader::LoaderQueue::~LoaderQueue(){}

#if 0 // obsolete, not well thought through :V
template<typename resType>
typename Resource<resType>::Loader::LoaderQueue::QueueValue&
Resource<resType>::Loader::LoaderQueue::operator[](SizeType n)
{
#ifdef DEBUG
  assert(n < getSize());
#endif
  return innerQueue[n].first();
}
#endif

template<typename resourceType, typename outerType>
SizeType Resource<resourceType, outerType>::Loader::LoaderQueue::getSize() const
{
#if 0
  if(!writeAccess.TryLock())
    return outerSize;
    
  SizeType ret = innerQueue.size();
  
  writeAccess.Unlock();
  return ret;
#else
  ScopedLock lock(writeAccess);
  return innerQueue.size();
#endif
}

template<typename resourceType, typename outerType>
void Resource<resourceType, outerType>::Loader::LoaderQueue::push(ResourceListEntry elem)
{
  ScopedLock lock(writeAccess);
  innerQueue.push_back(elem);
}

template<typename resourceType, typename outerType>
void Resource<resourceType, outerType>::Loader::LoaderQueue::push(const std::vector<ResourceListEntry> &elems)
{
  ScopedLock(writeAccess);
  innerQueue.insert(innerQueue.back(), elems.begin(), elems.end());
}

template<typename resourceType, typename outerType>
typename Resource<resourceType, outerType>::ResourceListEntry
Resource<resourceType, outerType>::Loader::LoaderQueue::pop()
{
  ResourceListEntry front = innerQueue.front();
  innerQueue.pop_front();
  return front;
}