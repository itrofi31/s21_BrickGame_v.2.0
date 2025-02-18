#include "model.h"

#include <ctime>
using namespace s21;

const char* SnakeModel::HIGH_SCORE_FILE = "snake_high_score.dat";

SnakeModel::SnakeModel()
    : currentDirection(DOWN),
      state(INIT),
      score(0),
      highScore(0),
      level(1),
      accelerated(false),
      width(10),
      height(20) {
  loadHighScore();
  initialize();
}

SnakeModel::~SnakeModel() {
  if (score > highScore) {
    saveHighScore();
  }
}

void SnakeModel::initialize() {
  snake.clear();
  for (int i = 0; i < INITIAL_LENGTH; ++i) {
    snake.push_back({5, 5 - i});
  }
  score = 0;
  level = 1;
  state = PAUSE;
  currentDirection = DOWN;
  accelerated = false;
  generateFood();
}

void SnakeModel::update() {
  if (state == MOVING) {
    moveSnake();
    if (checkCollision()) {
      state = GAMEOVER;
      updateHighScore();
    }
    if (isWin()) {
      state = GAMEOVER;
      score += 1000;
      updateHighScore();
    }
  }
}

bool SnakeModel::isValidDirection(Direction newDir) const {
  if (currentDirection == UP || currentDirection == DOWN) {
    return newDir == LEFT || newDir == RIGHT;
  }
  if (currentDirection == LEFT || currentDirection == RIGHT) {
    return newDir == UP || newDir == DOWN;
  }
  return false;
}

void SnakeModel::changeDirection(Direction newDirection) {
  if (isValidDirection(newDirection)) {
    currentDirection = newDirection;
  }
}

void SnakeModel::moveSnake() {
  Coord newHead = snake.front();
  switch (currentDirection) {
    case UP:
      newHead.y -= 1;
      break;
    case DOWN:
      newHead.y += 1;
      break;
    case LEFT:
      newHead.x -= 1;
      break;
    case RIGHT:
      newHead.x += 1;
      break;
  }

  snake.insert(snake.begin(), newHead);
  if (newHead.x == food.x && newHead.y == food.y) {
    score += 10;
    updateHighScore();
    updateLevel();
    generateFood();
  } else {
    snake.pop_back();
  }
}

void SnakeModel::generateFood() {
  std::vector<Coord> available_positions;

  // Собираем все свободные позиции
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      Coord pos = {x, y};
      bool is_snake = false;

      // Проверяем, не находится ли эта позиция в змейке
      for (const auto& segment : snake) {
        if (segment.x == pos.x && segment.y == pos.y) {
          is_snake = true;
          break;
        }
      }

      // Если позиция свободна, добавляем её в список доступных
      if (!is_snake) {
        available_positions.push_back(pos);
      }
    }
  }

  // Если есть свободные позиции, выбираем случайную из них
  if (!available_positions.empty()) {
    food = available_positions[rand() % available_positions.size()];
  }
}

bool SnakeModel::checkCollision() {
  const Coord& head = snake.front();
  if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height) {
    return true;
  }
  for (size_t i = 1; i < snake.size(); ++i) {
    if (head.x == snake[i].x && head.y == snake[i].y) {
      return true;
    }
  }
  return false;
}

void SnakeModel::loadHighScore() {
  FILE* file = fopen(HIGH_SCORE_FILE, "rb");
  if (file != NULL) {
    if (fscanf(file, "%d", &highScore) != 1) {
      highScore = 0;
    }
    fclose(file);
  } else {
    highScore = 0;
  }
}

void SnakeModel::saveHighScore() const {
  FILE* file = fopen(HIGH_SCORE_FILE, "wb");
  if (file != NULL) {
    fprintf(file, "%d", highScore);
    fclose(file);
  }
}

void SnakeModel::updateHighScore() {
  if (score > highScore) {
    highScore = score;
    saveHighScore();
  }
}

void SnakeModel::gameOver() { state = GAMEOVER; }

void SnakeModel::updateLevel() {
  int newLevel = (score / POINTS_PER_LEVEL) + 1;
  if (newLevel > MAX_LEVEL) {
    newLevel = MAX_LEVEL;
  }
  if (newLevel != level) {
    level = newLevel;
  }
}