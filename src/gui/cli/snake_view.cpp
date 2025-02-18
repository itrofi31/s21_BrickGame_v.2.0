#include "snake_view.h"

using namespace s21;

SnakeView::SnakeView(SnakeModel* model) : model(model) {}

void SnakeView::render() {
  GameInfo_t game_info = updateField();
  clear();
  char game_name[] = "Snake";
  printGame(game_info, game_name);
  refresh();

  int baseDelay = 600;
  int levelDelay = 30 * game_info.speed;
  int delay = baseDelay - levelDelay;

  if (delay < 100) delay = 100;
  timeout(delay);
}

UserAction_t SnakeView::processInput() { return getAction(); }

GameInfo_t SnakeView::updateField() {
  GameInfo_t game_info = {0};
  static int field[20][10] = {0};
  static int* field_ptrs[20];
  for (int i = 0; i < 20; ++i) {
    field_ptrs[i] = field[i];
  }
  game_info.field = field_ptrs;
  game_info.next = nullptr;

  // Очистка поля
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      field[i][j] = 0;
    }
  }

  // Отрисовка змейки
  const std::vector<Coord>& snake = model->getSnake();
  for (const auto& segment : snake) {
    if (segment.y >= 0 && segment.y < 20 && segment.x >= 0 && segment.x < 10) {
      field[segment.y][segment.x] = 1;
    }
  }

  // Отрисовка еды
  const Coord& food = model->getFood();
  if (food.y >= 0 && food.y < 20 && food.x >= 0 && food.x < 10) {
    field[food.y][food.x] = 2;
  }

  // Обновляем информацию об игре
  game_info.score = model->getScore();
  game_info.high_score = model->getHighScore();
  game_info.level = model->getLevel();
  game_info.speed = model->getSpeed();
  game_info.pause = (model->getState() == PAUSE);

  return game_info;
}