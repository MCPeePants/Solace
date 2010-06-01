#include <map>
#include <queue>

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

template<typename resourceType, typename outerType>
Resource<resourceType, outerType>::Loader::Loader()
  :loadQueue(){}

template<typename resourceType, typename outerType>
Resource<resourceType, outerType>::Loader::~Loader(){}

template<typename resourceType, typename outerType>
void Resource<resourceType, outerType>::Loader::asyncLoad(ResourceListEntry resource)
{
  loadQueue.push(resource);
}

template<typename resourceType, typename outerType>
void Resource<resourceType, outerType>::Loader::asyncLoad(const std::vector<ResourceListEntry> &resources)
{
  //TODO: look for a neat copying function
  for(typename std::vector<ResourceListEntry>::iterator iter = resources.begin();
      iter != resources.end(); ++iter)
    asyncLoad(*iter);
}

template<typename resourceType, typename outerType>
void Resource<resourceType, outerType>::Loader::syncLoad(ResourceListEntry resource)
{
  outerType::loadInternal(resource->second.first, resource->first);
}

template<typename resourceType, typename outerType>
void Resource<resourceType, outerType>::Loader::syncLoad(const std::vector<ResourceListEntry> &resources)
{
  for(typename std::vector<ResourceListEntry>::iterator iter = resources.begin();
      iter != resources.end(); ++iter)
    syncLoad(*iter);
}

template<typename resourceType, typename outerType>
void Resource<resourceType, outerType>::Loader::finishLoading() const
{
  ScopedLock lock(finishedLoading);
}

template<typename resourceType, typename outerType>
bool Resource<resourceType, outerType>::Loader::hasFinishedLoading() const
{
  return loadQueue.getSize() == 0;
}

template<typename resourceType, typename outerType>
void Resource<resourceType, outerType>::Loader::Run()
{
  ScopedLock lock(finishedLoading);
  
  while(!hasFinishedLoading())
    syncLoad(loadQueue.pop());
}