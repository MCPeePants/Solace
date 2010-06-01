#include <map>
#include <queue>

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

template<typename resourceType, typename outerType>
Resource<resourceType, outerType>::Resource(ResourceListEntry entry)
  :listEntry(entry){
  ++entry->second.second;
}

template<typename resourceType, typename outerType>
Resource<resourceType, outerType>::~Resource()
{
  if(--listEntry->second.second == 0)
  {
    // TODO: debug information ("resource blah has been unloaded")
    outerType::unloadInternal(listEntry->second.first);
    resourceList.erase(listEntry);
  }
}

template<typename resourceType, typename outerType>
void Resource<resourceType, outerType>::precache(const PathKey &path)
{
  typedef typename Resource<resourceType, outerType>::ResourceList::value_type Entry;
  typedef typename Resource<resourceType, outerType>::ResourceList::mapped_type SubEntry;
  // TODO: try out resourceList.equal_range? ;z33ky
  ResourceListEntry iter = resourceList.lower_bound(path);
  if(++iter != resourceList.end() && resourceList.key_comp()(iter->first, path)) return;
  loader.asyncLoad(resourceList.insert(--iter, Entry(path, SubEntry(resourceType(), 0))));
}

template<typename resourceType, typename outerType>
outerType Resource<resourceType, outerType>::get(const PathKey &key)
{
  ResourceListEntry entry = resourceList.find(key);
  if(entry == resourceList.end())
  {
    // TODO warning ;z33ky
  }
  return outerType(resourceList.find(key));
}