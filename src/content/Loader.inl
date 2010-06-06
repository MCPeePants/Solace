#include <map>
#include <queue>

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

namespace content{

  template<typename resourceType, typename outerType>
  Resource<resourceType, outerType>::Loader::Loader()
    :loadQueue(), runs(false){}

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
    loadQueue.push(resources);
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
  void Resource<resourceType, outerType>::Loader::launch()
  {
    if(!isRunning())
    {
      finishedLoading.Lock();
      // TODO: NEED TO SET THIS ATOMICALLY!
      runs = true;
      Launch();
    }
  }

  template<typename resourceType, typename outerType>
  void Resource<resourceType, outerType>::Loader::Run()
  {
    //assert(isRunning());
    //runs = true;
    //ScopedLock lock(finishedLoading);
    
    while(!hasFinishedLoading())
      syncLoad(loadQueue.pop());
    
    runs = false;
    finishedLoading.Unlock();
  }
  
}