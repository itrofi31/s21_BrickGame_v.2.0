#ifndef SNAKE_VIEW_H
#define SNAKE_VIEW_H
#include <ncurses.h>

#include "../../brick_game/snake/controller.h"
#include "cli_loop.h"

namespace s21 {

class SnakeView {
 public:
  explicit SnakeView(SnakeModel* model);
  void render();
  UserAction_t processInput();
  GameInfo_t updateField();

 private:
  SnakeModel* model;
};

}  // namespace s21
#endif