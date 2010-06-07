#include <stdexcept>
#include <iostream>
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
      // TODO: warn about late precache
      typedef typename Resource<internalType, publicType>::ResourceList::value_type Entry;
      typedef typename Resource<internalType, publicType>::ResourceList::mapped_type SubEntry;

      loader.syncLoad(resourceList.insert(Entry(key, SubEntry(internalType(), 0))).first);
    }
    
    return publicType(resourceList.find(key));
  }
  
  template<typename internalType, typename publicType>
  void Resource<internalType, publicType>::incrementRefCount()
  {
    if(!keepResource())
    {
      ++getRefCount();
      // assert(getRefCount() != static_cast<SizeType>(-1));
      throw std::overflow_error("Resource reference count overflowed!");
    }
  }
  
  template<typename internalType, typename publicType>
  void Resource<internalType, publicType>::decrementRefCount()
  {
    if(getRefCount() == 0)
    {
      throw std::logic_error("Resource reference count is 0 .. and it's getting decremented");
    }
    else if(!keepResource() && --getRefCount() == 0)
    {
      // TODO: the hash doesn't help much, does it?
      std::cout << "Resource #" << listEntry->first << " is getting unloaded" << std::endl;
      publicType::unloadInternal(getResource());
      resourceList.erase(listEntry);
    }
  }
  
}