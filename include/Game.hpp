#ifndef GAME_HPP
#define GAME_HPP
#include <Entity.hpp>
#include <Window.hpp>
#include <vector>

class Game {
public:
  Game(Window *window);
  ~Game();

  void clean_up();

  void mainloop();

private:
  Window *pr_window;
  std::vector<Entity> pr_entities;
};
#endif
