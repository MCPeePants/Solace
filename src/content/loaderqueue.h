#ifndef SLC_CONTENT_LOADERQUEUE_H
#define SLC_CONTENT_LOADERQUEUE_H

#include <queue>

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>

// TODO: move to core
namespace content{
  
  // this class encapsulates a container for threaded access
  // one thread writes, multiple can read
  // TODO: new name needed
  template<typename T>
  class LoaderQueue
  {
    typedef std::deque<T> Queue;
    // typedef typename Queue::value_type QueueValue;
    typedef sf::Mutex Mutex;
    typedef sf::Lock ScopedLock;
    
  public:
    LoaderQueue(const SizeType n = 0);
    ~LoaderQueue();
          
    //QueueValue& operator[](const SizeType capacity);
    SizeType getSize() const;
    
    void push(T elem);
    template<typename Container>
    void push(const Container &elems);
    T pop();
    
  private:
    Queue innerQueue;
    mutable Mutex writeAccess; // mutable so we can have getSize constant
    //SizeType outerSize;
    // note: could use this and increment/decrement atomically to not require Mutex
    //   ^- need to implement canRead and couldRead
    //   ^- cstdatomic (C++0x)?
    //SizeType writeHead;
    //SizeType readHead;
  };
  
}

#include <content/LoaderQueue.inl>

#endif