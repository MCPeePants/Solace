#ifndef SLC_CONTENT_RESOURCE_H
#define SLC_CONTENT_RESOURCE_H

#include <cstddef>
#include <map>
#include <queue>

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

#include <boost/filesystem.hpp>

#include "content/resource_fwd.h"

namespace content{

  // TODO: move this somewhere more appropriate ;z33ky
  typedef std::size_t SizeType;
  typedef boost::filesystem::path Path;

  /* usage: class Classname : public Resource<Classname>
   * {
   *   friend class Resource<Classname>;
   *   //...
   *   void loadInternal(const typename Resource<Classname>::ResList::key_type &path);
   * }*/
   // TODO: major clean up, esp. typedefs! ;z33ky
   // TODO: outerType usually resourceType?
   // TODO: possibly better name for outerType. publicType? usageType?
  template<typename resourceType, typename outerType = resourceType>
  class Resource
  {
    // friend class outerType;
    // urgs
    public:
    typedef std::map<Path, std::pair<resourceType, SizeType> > ResList;
    private:
    // TODO: that loader is an adaption from a more general-purpose one I wrote before
    // there's probably stuff to remove from there, though they look useful ;z33ky
    class Loader : sf::Thread
    {
      typedef sf::Lock ScopedLock;
      // this class encapsulates a container for threaded access
      // one thread writes, multiple can read
      class LoaderQueue
      {
        typedef std::deque<typename Resource<resourceType, outerType>::ResList::value_type> Queue;
        typedef typename Queue::value_type QueueValue;
        typedef sf::Mutex Mutex;
        typedef sf::Lock ScopedLock;
        
        friend class Loader;
      public:
        LoaderQueue(const SizeType n = 0);
        ~LoaderQueue();
          
        //QueueValue& operator[](const SizeType capacity);
          
        SizeType getSize() const;
          
      private:
        void push(QueueValue &elem);
        void push(const std::vector<QueueValue> &elems);
        QueueValue& pop();
      private:
        Queue innerQueue;
        mutable Mutex writeAccess;
        //SizeType outerSize;
      };
    public:
      Loader();
      ~Loader();
        
      void asyncLoad(typename Resource<resourceType, outerType>::ResList::value_type &resource);
      void asyncLoad(const std::vector<typename Resource<resourceType, outerType>::ResList::value_type> &resources);
      static void syncLoad(typename Resource<resourceType, outerType>::ResList::value_type &resource);
      static void syncLoad(const std::vector<typename Resource<resourceType, outerType>::ResList::value_type> &resources);
        
      void finishLoading() const;
      bool hasFinishedLoading() const;

    private:
      void Run();
      static void loadInternal(typename Resource<resourceType, outerType>::ResList::value_type &resource);

    private:
      LoaderQueue loadQueue;
      sf::Mutex finishedLoading;
    };
  public:
    Resource();
    ~Resource();
    
    typedef typename ResList::key_type Key;
    
    static void precache(const Key &key);
    static outerType get(const typename ResList::key_type &key);
    
  protected:
    static ResList& getResourceList(){ return resourceList; }
    
  private:
    static Loader loader;
    static ResList resourceList;
  };
  
  template<typename resourceType, typename outerType>
  typename Resource<resourceType, outerType>::Loader Resource<resourceType, outerType>::loader;
  template<typename resourceType, typename outerType>
  typename Resource<resourceType, outerType>::ResList Resource<resourceType, outerType>::resourceList;

#include "content/Resource.inl"
#include "content/LoaderQueue.inl"
#include "content/Loader.inl"
  
}

#endif