#ifndef SLC_CONTENT_SPRITE
#define SLC_CONTENT_SPRITE

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "content/resource_fwd.h"

namespace content{
  
  // sample using Resource
  // bad sample.. inlined constructors 'n stuff
  class Sprite : Resource<sf::Image, Sprite>
  {
    friend class Resource<sf::Image, Sprite>;
  public:
    // we need this because static functions are not inherited
    // ^- alternative: typedef it outside of Sprite
    typedef Resource<sf::Image, Sprite> Manager;
  private:
    Sprite(ResourceListEntry entry):Manager(entry), spr(entry->second.first){}
    
  public:
    // put on hold, kinda ugly
    // Sprite(const PathKey &path):Manager((Manager::precache(path), Manager::get(path))), spr(listEntry.second.first){}
    ~Sprite(){}
    
    // void Draw(); and what not would come here
    
  private:
    // TODO: ResourceLoadError loadInternal(...);
    static void loadInternal(ResourceType &img, const PathKey &path){ img.LoadFromFile(path.string());}
    static void unloadInternal(ResourceType &img){ }
    
  private:
    sf::Sprite spr;
  };
  
}

#endif