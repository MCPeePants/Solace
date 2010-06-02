#ifndef SLC_CONTENT_RESOURCE_H
#define SLC_CONTENT_RESOURCE_H

#include <cstddef>
#include <map>
#include <queue>
#include <tr1/unordered_map>

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

#include <boost/filesystem.hpp>
//#include <boost/functional/hash.hpp>

#include "content/resource_fwd.h"

namespace content{

  // TODO: move this somewhere more appropriate ;z33ky
  typedef std::size_t SizeType;
  typedef boost::filesystem::path Path;
  // std::tr1::hash vs boost::hash ?
  struct PathHasher : public std::tr1::hash<Path::string_type>
  {
    result_type operator()(const Path &key) const
    {
      return operator()(key.string());
    }
  };

  /* usage: class Classname : public Resource<Classname>
   * {
   *   friend class Resource<Classname>; // uses private functions
   * public:
   *   typedef Resource<Classname> Manager;
   * 
   *   ~Classname();
   *   
   * private:
   *   Classname(); // must be default-constructable
   *   Classname(ResourceType &data); // used by Resource
   *    
   *   static void loadInternal(ResourceType &data, const PathKey &path);
   * };
   * 
   * Classname::Manager::precache("/path/resource");
   * Classname instance(Classname::Manager::get("/path/resource"));*/
   
   // TODO: outerType usually resourceType? ;z33ky
   // TODO: possibly better name for outerType. publicType? usageType? ;z33ky
   // TODO: rename resourceType to internalType? ;z33ky
   // TODO: bool keepResource && manual resource unloading ;z33ky
   // HACK: Parent-class (Resource) requires knowledge of Child-class and must be friended
   //   therefore, extenstion is made easy ;z33ky
   // TODO: add a function to actually start the Loader-thread ;z33ky
   // TODO: auto-start loading resources ;z33ky
   // TODO: error-handling ;z33ky
   // TODO: handling directories ;z33ky
   //   ^- boost/regex/vr/fileiter.hpp -> boost::file_iterator and if(str.back() == boost::filesystem::slash<Path>) str.push_back('*'); or something
  template<typename resourceType, typename outerType = resourceType>
  class Resource
  {
    typedef std::tr1::unordered_map<Path, std::pair<resourceType, SizeType>, PathHasher > ResourceList;
    
  protected:
    typedef resourceType ResourceType;
    typedef typename ResourceList::iterator ResourceListEntry;
    
  private:
    // TODO: that loader is an adaption from a more general-purpose one I wrote before
    //  there's probably stuff to remove from there, though they look useful ;z33ky
    // TODO: public accessors in Resource for finishLoading 'n stuff ;z33ky
    class Loader : sf::Thread
    {
      typedef sf::Lock ScopedLock;
      // this class encapsulates a container for threaded access
      // one thread writes, multiple can read
      class LoaderQueue
      {
        friend class Loader;
        
        typedef std::deque<ResourceListEntry> Queue;
        // typedef typename Queue::value_type QueueValue;
        typedef sf::Mutex Mutex;
        typedef sf::Lock ScopedLock;
      public:
        
        LoaderQueue(const SizeType n = 0);
        ~LoaderQueue();
          
        //QueueValue& operator[](const SizeType capacity);
        SizeType getSize() const;
          
      private:
        void push(ResourceListEntry elem);
        void push(const std::vector<ResourceListEntry> &elems);
        ResourceListEntry pop();
        
      private:
        Queue innerQueue;
        mutable Mutex writeAccess; // mutable so we can have getSize constant
        //SizeType outerSize;
      };
    public:
      Loader();
      ~Loader();
        
      void asyncLoad(ResourceListEntry resource);
      void asyncLoad(const std::vector<ResourceListEntry> &resources);
      static void syncLoad(ResourceListEntry resource);
      static void syncLoad(const std::vector<ResourceListEntry> &resources);
        
      void finishLoading() const;
      bool hasFinishedLoading() const;

    private:
      void Run();
      static void loadInternal(ResourceListEntry resource);

    private:
      LoaderQueue loadQueue;
      sf::Mutex finishedLoading;
    };
  public:
    // TODO: name this just Path? ;z33ky
    typedef typename ResourceList::key_type PathKey;
    
    Resource(ResourceListEntry entry);
    virtual ~Resource();
    
    // TODO: return iterator? ;z33ky
    //  ^- or additionally for static latePrecache? ;z33ky
    //  ^- differentiate between precache and get at all? ;z33ky
    static void precache(const PathKey &key);
    static outerType get(const PathKey &key);
    
  private:
    // TODO: write accessor for listEntry ;z33ky
    ResourceListEntry listEntry;
    static Loader loader;
    static ResourceList resourceList;
  };
  
  // static members of Resource
  template<typename resourceType, typename outerType>
  typename Resource<resourceType, outerType>::Loader Resource<resourceType, outerType>::loader;

  template<typename resourceType, typename outerType>
  typename Resource<resourceType, outerType>::ResourceList Resource<resourceType, outerType>::resourceList;

#include "content/Resource.inl"
#include "content/LoaderQueue.inl"
#include "content/Loader.inl"
  
}

#endif