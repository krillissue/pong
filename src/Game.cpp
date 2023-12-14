#include <Entity.hpp>
#include <Game.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Sprite.hpp>
#include <Window.hpp>

Game::Game(Window *window) : pr_window(window) {}

Game::~Game() { clean_up(); }
void Game::clean_up() { pr_window->clean_up(); }

void Game::mainloop() {
  SDL_Event event;

  while (true) {
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT)
      break;

    pr_window->clear_render();

    for (const Entity &entity : pr_entities)
      pr_window->render_sprite(entity.sprite, entity.x, entity.y);

    pr_window->display_render();
  }
}
