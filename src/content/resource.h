#ifndef SLC_CONTENT_RESOURCE_H
#define SLC_CONTENT_RESOURCE_H

#include <cstddef>
#include <map>
#include <queue>

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

namespace boost{ namespace filesystem{
  class path;
}}

namespace content{

  // TODO: move this somewhere more appropriate ;z33ky
  typedef std::size_t SizeType;
  typedef boost::filesystem::path Path;

  // heh.. nested classes.. good idea? bad idea?
  template<typename restype>
  class Resource
  {
  public:
    class Manager
    {
      typedef std::map<Path, Resource<restype> > ResList;
      // TODO: that loader is an adaption from a more general-purpose one I wrote before
      // there's probably stuff to remove from there, though they look useful ;z33ky
      class Loader : sf::Thread
      {
        // this class encapsulates a container for threaded access
        // one thread writes, multiple can read
        class LoaderQueue
        {
          typedef std::queue<std::pair<Resource<restype>*, Path> > Queue;
          typedef sf::Mutex Lock;
          typedef sf::Lock ScopedLock;
          
          friend class Loader;
        public:
          LoaderQueue(SizeType n = 0);
          ~LoaderQueue();
          
          typename Queue::value_type::first_type& operator[](SizeType n);
          
          SizeType getSize();
          SizeType getCapacity();
          
        private:
          Queue innerQueue;
          Lock brb;
          //SizeType outerSize;
        };
      public:
        Loader();
        ~Loader();
        
        const Resource asyncLoad(const Path &path);
        const std::vector<Resource> asyncLoad(const std::vector<Path> &paths);
        static const Resource syncLoad(const std::vector<Path> &path);
        
        void finishLoading() const;
        bool hasFinishedLoading() const;

      private:
        void Run();
        static void loadInternal(Resource res, Path path);

      private:
        LoaderQueue loadQueue;
        
      };
      public:
        Manager();
        ~Manager();
        
        const Resource& getResource(const typename ResList::key_type key);
    } Manager;
  public:
    Resource();
    ~Resource();
  };

#include "content/Resource.inl"
#include "content/Manager.inl"
#include "content/LoaderQueue.inl"
#include "content/Loader.inl"
  
}

#endif