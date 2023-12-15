#ifndef SOUND_HPP
#define SOUND_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

struct Sound {
  Mix_Chunk *chunk;
  std::string name;
};
#endif
