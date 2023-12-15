#include <ErrorType.hpp>
#include <Game.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Window.hpp>
#include <iostream>
#include <tools/crash.hpp>

void help(std::string arg0, bool error) {
  if (error) {
    std::cerr << "usage: " << arg0 << " [help] [accelerated] [vsync]"
              << std::endl;
    std::cerr << " - help: prints this help page" << std::endl;
    std::cerr << " - accelerated: uses hardware acceleration (uses a GPU)"
              << std::endl;
    std::cerr << " - vsync: uses vertical sync (caps the framerate at "
                 "monitor's refresh rate)"
              << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "usage: " << arg0 << " [help] [accelerated] [vsync]"
            << std::endl;
  std::cout << " - help: prints this help page" << std::endl;
  std::cout << " - accelerated: uses hardware acceleration (uses a GPU)"
            << std::endl;
  std::cout << " - vsync: uses vertical sync (caps the framerate at monitor's "
               "refresh rate)"
            << std::endl;
  exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  bool accelerated = false;
  bool vsync = false;

  if (argc > 1)
    for (int i = 1; i < argc; i++) {
      std::string argStr = argv[i];
      if (argStr == "help")
        help(argv[0], false);
      else if (argStr == "accelerated")
        accelerated = true;
      else if (argStr == "vsync")
        vsync = true;
      else
        help(argv[0], true);
    }

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != EXIT_SUCCESS)
    crash("SDL_Init failed.", ErrorType::SDL);

  if (!IMG_Init(IMG_INIT_PNG))
    crash("IMG_Init failed.", ErrorType::IMG);

  Window window("Pong", 640, 480, accelerated, vsync);
  window.load_sprite("res/gfx/ball.png", "ball");

  Game game(&window);
  game.mainloop();
  game.clean_up();

  SDL_Quit();
  IMG_Quit();

  return EXIT_SUCCESS;
}
