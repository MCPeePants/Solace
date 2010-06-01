#ifndef SLC_CONTENT_SPRITE
#define SLC_CONTENT_SPRITE

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "content/resource_fwd.h"

namespace content{
  
  // sample using Resource
  // bad sample.. inlined constructors 'n stuff
  class Sprite
  {
    friend class Resource<sf::Image, Sprite>;
    typedef Resource<sf::Image, Sprite>::Key Key;
    typedef Resource<sf::Image, Sprite>::ResList::mapped_type ResImage;
    Sprite(ResImage &image):img(image), spr(img.first){ ++img.second;}
  public:
    ~Sprite(){ --img.second;}
  private:
    static void loadInternal(sf::Image &img, const Key &path){ img.LoadFromFile(path.string());}
    
  private:
    ResImage &img;
    sf::Sprite spr;
  };
  
  typedef Resource<sf::Image, Sprite> SpriteRes;
  
}

#endif