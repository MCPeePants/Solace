#include <map>
#include <queue>

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

template<typename resourceType, typename outerType>
Resource<resourceType, outerType>::Resource(){}

template<typename resourceType, typename outerType>
Resource<resourceType, outerType>::~Resource(){}

template<typename resourceType, typename outerType>
void Resource<resourceType, outerType>::precache(const typename ResList::key_type &path)
{
  typename ResList::iterator iter = resourceList.lower_bound(path);
  if(++iter != resourceList.end() && resourceList.key_comp()(iter->first, path)) return;
  loader.asyncLoad(*resourceList.insert(--iter, typename Resource<resourceType, outerType>::ResList::value_type(path, typename Resource<resourceType, outerType>::ResList::mapped_type(resourceType(), 0))));
}

template<typename resourceType, typename outerType>
outerType Resource<resourceType, outerType>::get(const typename ResList::key_type &key)
{
  ++resourceList[key].second;
  return outerType(resourceList[key]);
}