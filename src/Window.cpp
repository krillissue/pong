#include <ErrorType.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Sprite.hpp>
#include <Window.hpp>
#include <string>
#include <tools/crash.hpp>

Window::Window(std::string title, int w, int h, bool accelerated, bool vsync)
    : pr_window(NULL), pr_renderer(NULL) {
  pr_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

  if (!pr_window)
    crash("SDL_CreateWindow failed.", ErrorType::SDL);

  int renderer_flags = 0;

  if (accelerated)
    renderer_flags = renderer_flags | SDL_RENDERER_ACCELERATED;
  if (vsync)
    renderer_flags = renderer_flags | SDL_RENDERER_PRESENTVSYNC;

  pr_renderer = SDL_CreateRenderer(pr_window, -1, renderer_flags);

  {
    int player_w = 16;
    int player_h = 80;

    SDL_Surface *surface =
        SDL_CreateRGBSurface(0, player_w, player_h, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));
    pr_sprites.push_back(
        {.texture = SDL_CreateTextureFromSurface(pr_renderer, surface),
         .name = "player"});
    SDL_FreeSurface(surface);
  }
}

Window::~Window() { clean_up(); }

void Window::clean_up() {
  SDL_DestroyRenderer(pr_renderer);
  SDL_DestroyWindow(pr_window);

  for (const Sprite &sprite : pr_sprites)
    SDL_DestroyTexture(sprite.texture);
}

void Window::load_sprite(std::string sprite_path, std::string sprite_name) {
  SDL_Texture *texture = NULL;
  texture = IMG_LoadTexture(pr_renderer, sprite_path.c_str());

  if (!texture)
    crash("IMG_LoadTexture failed.", ErrorType::IMG);

  pr_sprites.push_back({.texture = texture, .name = sprite_name});
}

void Window::render_sprite(std::string sprite_name, int x, int y) {
  SDL_Texture *sprite_texture = NULL;

  for (const Sprite &sprite : pr_sprites)
    if (sprite.name == sprite_name)
      sprite_texture = sprite.texture;

  if (!sprite_texture)
    crash("Cannot render sprite " + sprite_name +
              " because it was not found in window.pr_sprites",
          ErrorType::CUSTOM);

  SDL_Rect dst = {
      .x = x,
      .y = y,
      .w = 0,
      .h = 0,
  };

  SDL_QueryTexture(sprite_texture, NULL, NULL, &dst.w, &dst.h);
  SDL_RenderCopy(pr_renderer, sprite_texture, NULL, &dst);
}

void Window::load_sound(std::string sound_path, std::string sound_name) {
  Mix_Chunk *chunk = NULL;
  chunk = Mix_LoadWAV(sound_path.c_str());

  if (!chunk)
    crash("Mix_LoadWAV failed.", ErrorType::MIX);

  pr_sounds.push_back({.chunk = chunk, .name = sound_name});
}

void Window::play_sound(std::string sound_name) {
  Mix_Chunk *sound_chunk = NULL;

  for (const Sound &sound : pr_sounds)
    if (sound.name == sound_name)
      sound_chunk = sound.chunk;

  if (!sound_chunk)
    crash("Cannot play sound " + sound_name +
              " because it was not found in window.pr_sounds",
          ErrorType::CUSTOM);

  Mix_PlayChannel(-1, sound_chunk, 0);
}

void Window::display_render() { SDL_RenderPresent(pr_renderer); }
void Window::clear_render() { SDL_RenderClear(pr_renderer); }
