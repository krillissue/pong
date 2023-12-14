#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <SDL2/SDL.h>
#include <string>

struct Sprite {
  SDL_Texture *texture;
  std::string name;
};
#endif
