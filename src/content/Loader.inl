#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

namespace content{

  template<typename internalType, typename publicType>
  Resource<internalType, publicType>::Loader::Loader()
    :loadQueue(), runs(false){}

  template<typename internalType, typename publicType>
  Resource<internalType, publicType>::Loader::~Loader(){}

  template<typename internalType, typename publicType>
  void Resource<internalType, publicType>::Loader::asyncLoad(ResourceListEntry resource)
  {
    loadQueue.push(resource);
  }

  template<typename internalType, typename publicType>
  void Resource<internalType, publicType>::Loader::asyncLoad(const std::vector<ResourceListEntry> &resources)
  {
    loadQueue.push(resources);
  }

  template<typename internalType, typename publicType>
  void Resource<internalType, publicType>::Loader::syncLoad(ResourceListEntry resource)
  {
    publicType::loadInternal(resource->second.first, resource->first);
  }

  template<typename internalType, typename publicType>
  void Resource<internalType, publicType>::Loader::syncLoad(const std::vector<ResourceListEntry> &resources)
  {
    for(typename std::vector<ResourceListEntry>::iterator iter = resources.begin();
        iter != resources.end(); ++iter)
      syncLoad(*iter);
  }

  template<typename internalType, typename publicType>
  void Resource<internalType, publicType>::Loader::finishLoading() const
  {
    ScopedLock lock(finishedLoading);
  }

  template<typename internalType, typename publicType>
  bool Resource<internalType, publicType>::Loader::hasFinishedLoading() const
  {
    return loadQueue.getSize() == 0;
  }

  template<typename internalType, typename publicType>
  void Resource<internalType, publicType>::Loader::launch()
  {
    if(!isRunning())
    {
      finishedLoading.Lock();
      // TODO: NEED TO SET THIS ATOMICALLY!
      runs = true;
      Launch();
    }
  }

  template<typename internalType, typename publicType>
  void Resource<internalType, publicType>::Loader::Run()
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