#include <map>
#include <queue>

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

template<typename resourceType, typename outerType>
Resource<resourceType, outerType>::Resource(ResourceListEntry entry)
  :listEntry(entry){
  if(!keepResource())
    ++getRefCount();
  // TODO: throw exception or something ;z33ky
  //assert(getRefCount != static_cast<SizeType>(-1));
}

template<typename resourceType, typename outerType>
Resource<resourceType, outerType>::Resource(const PathKey &path)
//:/*Resource*/listEntry(precache(path), resourceList.find(path))
// can't call base-constructor :(
// "invalid use of void expression"
{
  precache(path);
  listEntry = resourceList.find(path);
  if(!keepResource())
    ++getRefCount();
}

template<typename resourceType, typename outerType>
Resource<resourceType, outerType>::~Resource()
{
  if(!keepResource() && --getRefCount() == 0)
  {
    // TODO: debug information ("resource blah has been unloaded") ;z33ky
    outerType::unloadInternal(listEntry->second.first);
    resourceList.erase(listEntry);
  }
}

template<typename resourceType, typename outerType>
void Resource<resourceType, outerType>::precache(const PathKey &path, const bool keep)
{
  typedef typename Resource<resourceType, outerType>::ResourceList::value_type Entry;
  typedef typename Resource<resourceType, outerType>::ResourceList::mapped_type SubEntry;
  
  std::pair<ResourceListEntry, bool> insertion = resourceList.insert(Entry(path, SubEntry(resourceType(), keep ? keepResourceSize : 0)));
  
  if(insertion.second)
  {
    loader.asyncLoad(insertion.first);
    if(autoStartLoading)
      startLoading();
  }
}

template<typename resourceType, typename outerType>
outerType Resource<resourceType, outerType>::get(const PathKey &key)
{
  ResourceListEntry entry = resourceList.find(key);
  
  if(entry == resourceList.end())
  {
    // TODO warning ;z33ky
    // throw ResourceException("Cannot find Resource " + key);
  }
  
  return outerType(resourceList.find(key));
}