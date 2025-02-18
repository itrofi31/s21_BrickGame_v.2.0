#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "model.h"

namespace s21 {

class SnakeController {
 public:
  SnakeController(SnakeModel* model);
  void handleInput(UserAction_t action, bool hold);
  void startGame();
  void update();
  SnakeModel* getModel() const;

 private:
  SnakeModel* model;
};
}  // namespace s21
#endif