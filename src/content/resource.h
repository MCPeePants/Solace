#ifndef SLC_CONTENT_RESOURCE_H
#define SLC_CONTENT_RESOURCE_H

#include <cstddef>
#include <map>
#include <tr1/unordered_map>
#include <functional>
#include <queue>

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
      return std::tr1::hash<Path::string_type>::operator()(key.string());
    }
  };

  /* usage: class Classname : public Resource<Classname>
   * {
   *   friend class Resource<Classname>; // Resource uses private functions
   * public:
   *   typedef Resource<Classname> Manager; // static functions are not inherited; use alternative solutions if you wish
   *  
   *   Classname(const PathKey &path); // call Parent(path)-constructor
   *   
   * private:
   *   Classname(); // must be default-constructible // TODO: verify ;z33ky
   *   Classname(ResourceType &data); // used by Resource // TODO: might become obsolete
   *    
   *   static void loadInternal(ResourceType &data, const PathKey &path);
   *   static void unloadInternal(ResourceType &data);
   * };
   * 
   * Classname::Manager::precache("/path/resource");
   * Classname resource("/path/resource"); // will also precache if needed*/
   
   // HACK: Parent-class (Resource) requires knowledge of Child-class and must be friended
   //   therefore, extenstion is made easy ;z33ky
   // TODO: error-handling ;z33ky
   //   ^- I could provide general error-handling, but that should probably just be done by the individual child-class
   //   ^- maybe bool loadInternal to terminate the thread, though this could also be done from within that function
   // TODO: handling directories ;z33ky
   //   ^- boost/regex/vr/fileiter.hpp -> boost::file_iterator and if(str.back() == boost::filesystem::slash<Path>) str.push_back('*'); or something
   //   ^- will do later when the virtual filesystem is in place ;z33ky
   // TODO: change some (out-commented) asserts into exceptions ;z33ky
   // TODO: don't just "comment-throw" exceptions ;z33ky
  template<typename internalType, typename publicType = internalType>
  class Resource
  {
    typedef std::tr1::unordered_map<Path, std::pair<internalType, SizeType>, PathHasher> ResourceList;
    
  protected:
    typedef internalType ResourceType;
    typedef typename ResourceList::iterator ResourceListEntry;
    
  private:
    // TODO: that loader is an adaption from a more general-purpose one I wrote before
    //  there's probably stuff to remove from there, though they look useful ;z33ky
    class Loader : public sf::Thread
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
        // note: could use this and increment/decrement atomically to not require Mutex
        //   ^- need to implement canRead and couldRead
        //   ^- cstdatomic (C++0x)?
        //SizeType writeHead;
        //SizeType readHead;
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
      bool isRunning() const{ return runs;}
      
      void launch();

    private:
      void Run();
      static void loadInternal(ResourceListEntry resource);

    private:
      LoaderQueue loadQueue;
      mutable sf::Mutex finishedLoading;
      bool runs;
    };
  public:
    // TODO: name this just Path? ;z33ky
    typedef typename ResourceList::key_type PathKey;
    
    // TODO: return iterator? ;z33ky
    //  ^- or additionally for static latePrecache? ;z33ky
    //  ^- differentiate between precache and get at all? ;z33ky
    static void precache(const PathKey &key, const bool keep = false);
    // get -> obsolete? (Resource(const PathKey &path))
    static publicType get(const PathKey &key);
    static void startLoading(){ loader.launch();}
    static void finishLoading(){ loader.finishLoading();}
    static bool isLoading(){ return loader.isRunning();}
    static bool hasFinishedLoading(){ return loader.hasFinishedLoading();}
    static void stopLoading(){ loader.Terminate();}
    
    Resource(const PathKey &path);
    
  protected:
    Resource(ResourceListEntry entry);
    virtual ~Resource();
    
    internalType& getResource(){ return listEntry->second.first;}
    typename ResourceList::mapped_type::second_type& getRefCount(){ return listEntry->second.second;}
    
  private:
    // right accesibility?
    bool keepResource(){ return getRefCount() == keepResourceSize;}
    
  private:
    ResourceListEntry listEntry;
    static Loader loader;
    // TODO: on destruction check that resourceList.size() == 0? ;z33ky
    static ResourceList resourceList;
    const static SizeType keepResourceSize;
    const static bool autoStartLoading;
  };
  
  // static members of Resource
  template<typename resourceType, typename outerType>
  typename Resource<resourceType, outerType>::Loader Resource<resourceType, outerType>::loader;

  template<typename resourceType, typename outerType>
  typename Resource<resourceType, outerType>::ResourceList Resource<resourceType, outerType>::resourceList;
  
  template<typename resourceType, typename outerType>
  const SizeType Resource<resourceType, outerType>::keepResourceSize = static_cast<SizeType>(-1);
  
  // you can specialize this in your resource-child class to override default behavior
  // TODO: should this be a template parameter? ;z33ky
  template<typename resourceType, typename outerType>
  const bool Resource<resourceType, outerType>::autoStartLoading = true;

// TODO: move inl-files inclusion out of this namespace ! ;z33ky
#include "content/Resource.inl"
#include "content/LoaderQueue.inl"
#include "content/Loader.inl"
  
}

#endif