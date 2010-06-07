#ifndef SLC_CONTENT_SPRITE
#define SLC_CONTENT_SPRITE

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "content/resource_fwd.h"

namespace content{
  
  // sample using Resource
  // bad sample.. inlined constructors 'n stuff
  class Sprite : public Resource<sf::Image, Sprite>
  {
    friend class Resource<sf::Image, Sprite>;
  private:
    Sprite(ResourceListEntry entry):Base(entry), spr(getResource()){}
    
  public:
    Sprite(const PathKey &path):Base(path), spr(getResource()){}
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