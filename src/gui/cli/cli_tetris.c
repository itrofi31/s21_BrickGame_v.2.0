#include "../../brick_game/tetris/tetris.h"
#include "../../gui/cli/cli.h"

void tetris() {
  clear();
  refresh();

  initGame();
  GameInfo_t game_info = updateCurrentState();
  printGame(game_info, "Tetris");
  refresh();

  while (tetg->state != GAMEOVER) {
    flushinp();
    userInput(getAction(), 0);
    game_info = updateCurrentState();

    if (tetg->state == GAMEOVER) {
      freeGui(game_info, tetg->figurest->size, tetg->field->height);
      continue;
    }

    printGame(game_info, "Tetris");
    refresh();
    timeout(600 - (30 * game_info.speed));
  };

  freeGame(tetg);
}