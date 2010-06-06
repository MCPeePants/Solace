#ifndef SLC_CONTENT_RESOURCE_H
#define SLC_CONTENT_RESOURCE_H

#include <cstddef>
#include <utility>
#include <tr1/unordered_map>
#include <functional>

#include <boost/filesystem.hpp>
//#include <boost/functional/hash.hpp>

#include "content/resource_fwd.h"

namespace content{

  // TODO: move this somewhere more appropriate ;z33ky
  //  ^- core
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
   *   Classname(const PathKey &path); // see resource2-example | call Parent(path)-constructor
   *   
   * private:
   *   Classname(ResourceType &data); // used by Resource::get
   *    
   *   static void loadInternal(ResourceType &data, const PathKey &path);
   *   static void unloadInternal(ResourceType &data);
   * };
   * 
   * Classname::Manager::precache1("/path/resource1");
   * Classname resource1 = Classname::Manager::get("/path/resource1"); // must be precached (might change)
   * Classname resource2("/path/resource2"); // will also precache if needed*/
   
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
    class Loader;
    
  public:
    // TODO: name this just Path? ;z33ky
    typedef typename ResourceList::key_type PathKey;
    
    // TODO: return iterator? ;z33ky
    //  ^- or additionally for static latePrecache? ;z33ky
    //  ^- differentiate between precache and get at all? ;z33ky
    static void precache(const PathKey &key, const bool keep = false);
    static publicType get(const PathKey &key);
    
    static void startLoading(){ loader.launch();}
    static void stopLoading(){ loader.Terminate();}
    
    static void finishLoading(){ loader.finishLoading();}
    static bool isLoading(){ return loader.isRunning();}
    static bool hasFinishedLoading(){ return loader.hasFinishedLoading();}
    
    Resource(const PathKey &path);
    
  protected:
    Resource(ResourceListEntry entry);
    Resource(const Resource &other);
    virtual ~Resource();
    
    internalType& getResource(){ return listEntry->second.first;}
    
  private:
    // right accesibility?
    bool keepResource(){ return getRefCount() == keepResourceSize;}
    void incrementRefCount();
    void decrementRefCount();
    typename ResourceList::mapped_type::second_type& getRefCount(){ return listEntry->second.second;}
    
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
  
}

// late include due to base-class of nested-class being templated, thus not forward-declarable (or something)
#include "content/loader.h"

#include <content/Resource.inl>

#endif