#ifndef SLC_CONTENT_LOADER_H
#define SLC_CONTENT_LOADER_H

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

#include "content/loaderqueue.h"

namespace content{
  
  template<typename internalType, typename publicType>
  class Resource<internalType, publicType>::Loader : public sf::Thread
  {
    typedef sf::Lock ScopedLock;
    
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
    LoaderQueue<ResourceListEntry> loadQueue;
    mutable sf::Mutex finishedLoading;
    bool runs;
  };
  
}

#include <content/Loader.inl>

#endif