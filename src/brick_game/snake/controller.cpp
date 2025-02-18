#include "controller.h"

using namespace s21;

SnakeController::SnakeController(SnakeModel* model) : model(model) {}

void SnakeController::handleInput(UserAction_t action, bool hold) {
  if (!hold) {
    switch (action) {
      case Start:
        if (model->getState() == PAUSE || model->getState() == INIT) {
          model->setState(MOVING);
        }
        break;
      case Pause:
        if (model->getState() == MOVING) {
          model->setState(PAUSE);
        } else if (model->getState() == PAUSE) {
          model->setState(MOVING);
        }
        break;
      case Terminate:
        model->gameOver();
        break;
      case Left:
        if (model->getState() == MOVING) {
          model->changeDirection(LEFT);
        }
        break;
      case Right:
        if (model->getState() == MOVING) {
          model->changeDirection(RIGHT);
        }
        break;
      case Up:
        if (model->getState() == MOVING) {
          model->changeDirection(UP);
        }
        break;
      case Down:
        if (model->getState() == MOVING) {
          model->changeDirection(DOWN);
        }
        break;
      default:
        break;
    }
  }
}

void SnakeController::update() {
  if (model->getState() == MOVING) {
    model->update();
  }
}

void SnakeController::startGame() {
  handleInput(Start, false);
  while (model->getState() != GAMEOVER) {
    update();
  }
}

SnakeModel* SnakeController::getModel() const { return model; }
