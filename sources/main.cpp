#include <SDL.h>
#include "game.h"

int main(int argc, char*argv[]) {
  std::ignore = argc;
  std::ignore = argv;
  const int FPS = 60;
  const int FRAME_DELAY = 1000 / FPS;

  Game game("Tetris", FPS); // NOLINT

  uint32_t frame_start;
  uint32_t frame_time;

  while (game.running()) {
    frame_start = SDL_GetTicks();

    game.handle_events();
    game.update();
    game.render();

    frame_time = SDL_GetTicks() - frame_start;

    if (FRAME_DELAY > frame_time)
      SDL_Delay(FRAME_DELAY - frame_time);
  }

  game.clean();

  return 0;
}
