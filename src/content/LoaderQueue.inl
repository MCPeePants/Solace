#include <queue>

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>

namespace content{

  template<typename T>
  LoaderQueue<T>::LoaderQueue(SizeType capacity)
  {
    // TODO: can we not reserve memory? ;z33ky
    //innerQueue.reserve(capacity);
  }

  template<typename T>
  LoaderQueue<T>::~LoaderQueue(){}

  #if 0 // obsolete, not well thought through :V
  template<T>
  LoaderQueue<T>::operator[](SizeType n)
  {
  #ifdef DEBUG
    assert(n < getSize());
  #endif
    return innerQueue[n].first();
  }
  #endif

  template<typename T>
  SizeType LoaderQueue<T>::getSize() const
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

  template<typename T>
  void LoaderQueue<T>::push(T elem)
  {
    ScopedLock lock(writeAccess);
    innerQueue.push_back(elem);
  }

  template<typename T>
  template<typename Container>
  void LoaderQueue<T>::push(const Container &elems)
  {
    ScopedLock(writeAccess);
    innerQueue.insert(innerQueue.back(), elems.begin(), elems.end());
  }

  template<typename T>
  T LoaderQueue<T>::pop()
  {
    T front = innerQueue.front();
    innerQueue.pop_front();
    return front;
  }
  
}