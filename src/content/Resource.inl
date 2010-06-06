#include <utility>

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

namespace content{

  template<typename internalType, typename publicType>
  Resource<internalType, publicType>::Resource(ResourceListEntry entry)
    :listEntry(entry){
    incrementRefCount();
  }
  
  template<typename internalType, typename publicType>
  Resource<internalType, publicType>::Resource(const Resource &other)
    :listEntry(other.listEntry){
    incrementRefCount();
  }

  template<typename internalType, typename publicType>
  Resource<internalType, publicType>::Resource(const PathKey &path)
  :/*Resource*/listEntry((precache(path), resourceList.find(path)))
  // can't call own constructor :(
  {
    incrementRefCount();
  }

  template<typename internalType, typename publicType>
  Resource<internalType, publicType>::~Resource()
  {
    decrementRefCount();
  }

  template<typename internalType, typename publicType>
  void Resource<internalType, publicType>::precache(const PathKey &path, const bool keep)
  {
    typedef typename Resource<internalType, publicType>::ResourceList::value_type Entry;
    typedef typename Resource<internalType, publicType>::ResourceList::mapped_type SubEntry;
    
    std::pair<ResourceListEntry, bool> insertion = resourceList.insert(Entry(path, SubEntry(internalType(), keep ? keepResourceSize : 0)));
    
    if(insertion.second)
    {
      loader.asyncLoad(insertion.first);
      if(autoStartLoading)
        startLoading();
    }
  }

  template<typename internalType, typename publicType>
  publicType Resource<internalType, publicType>::get(const PathKey &key)
  {
    ResourceListEntry entry = resourceList.find(key);
    
    if(entry == resourceList.end())
    {
      // TODO warning ;z33ky
      // throw ResourceException("Cannot find Resource " + key);
    }
    
    return publicType(resourceList.find(key));
  }
  
  template<typename internalType, typename publicType>
  void Resource<internalType, publicType>::incrementRefCount()
  {
    if(!keepResource())
      ++getRefCount();
    // TODO: throw exception or something ;z33ky
    //  assert(getRefCount() != static_cast<SizeType>(-1));
  }
  
  template<typename internalType, typename publicType>
  void Resource<internalType, publicType>::decrementRefCount()
  {
    if(!keepResource() && --getRefCount() == 0)
    {
      // TODO: debug information ("resource blah has been unloaded") ;z33ky
      publicType::unloadInternal(listEntry->second.first);
      resourceList.erase(listEntry);
    }
  }
  
}