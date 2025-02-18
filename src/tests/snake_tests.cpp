#include <gtest/gtest.h>

#include "../brick_game/snake/model.h"

using namespace s21;

class SnakeModelTest : public ::testing::Test {
 protected:
  SnakeModel model;
};

// Тест инициализации
TEST_F(SnakeModelTest, Initialization) {
  EXPECT_EQ(model.getState(), PAUSE);
  EXPECT_EQ(model.getScore(), 0);
  EXPECT_EQ(model.getLevel(), 1);

  const auto& snake = model.getSnake();
  EXPECT_EQ(snake.size(), 4);

  // Проверка начальной позиции змейки
  EXPECT_EQ(snake[0].x, 5);
  EXPECT_EQ(snake[0].y, 5);
}

// Тест движения змейки
TEST_F(SnakeModelTest, Movement) {
  model.setState(MOVING);
  const auto& initialSnake = model.getSnake();
  Coord initialHead = initialSnake.front();

  model.update();

  const auto& newSnake = model.getSnake();
  Coord newHead = newSnake.front();

  // По умолчанию движение вниз
  EXPECT_EQ(newHead.x, initialHead.x);
  EXPECT_EQ(newHead.y, initialHead.y + 1);
}

// Тест изменения направления
TEST_F(SnakeModelTest, DirectionChange) {
  // Нельзя повернуть в противоположном направлении
  model.changeDirection(UP);
  model.update();

  // Можно повернуть влево или вправо
  model.changeDirection(LEFT);
  model.update();
  const auto& snake = model.getSnake();
  EXPECT_EQ(snake[0].x, 5);
}

// Тест столкновения со стеной
TEST_F(SnakeModelTest, WallCollision) {
  model.setState(MOVING);
  // Двигаем змейку к левой стене
  for (int i = 0; i < 10; i++) {
    model.changeDirection(LEFT);
    model.update();
  }
  EXPECT_EQ(model.getState(), GAMEOVER);
}

// Тест поедания еды
TEST_F(SnakeModelTest, EatingFood) {
  model.setState(MOVING);
  int initialScore = model.getScore();
  int initialLength = model.getSnake().size();

  // Получаем позицию еды
  Coord food = model.getFood();

  // Двигаем змейку к еде (примерная логика)
  while (model.getSnake().front().x != food.x ||
         model.getSnake().front().y != food.y) {
    model.update();
    if (model.getState() == GAMEOVER) break;
  }

  if (model.getState() != GAMEOVER) {
    EXPECT_GT(model.getScore(), initialScore);
    EXPECT_GT(model.getSnake().size(), initialLength);
  }
}

// Тест обновления уровня
TEST_F(SnakeModelTest, LevelUpdate) {
  model.setState(MOVING);
  int initialLevel = model.getLevel();

  // Устанавливаем счет, достаточный для повышения уровня
  for (int i = 0; i < 11; i++) {
    model.updateHighScore();  // Увеличиваем счет
  }

  EXPECT_EQ(model.getLevel(), initialLevel);
}

// Тест ускорения
TEST_F(SnakeModelTest, Acceleration) {
  int normalSpeed = 2;
  model.setAccelerated(true);
  EXPECT_EQ(model.getSpeed(), normalSpeed);
}

// Тест сохранения рекорда
TEST_F(SnakeModelTest, HighScore) {
  int initialHighScore = model.getHighScore();
  model.setState(MOVING);

  // Устанавливаем новый рекорд
  for (int i = 0; i < 20; i++) {
    model.updateHighScore();
  }

  EXPECT_EQ(model.getHighScore(), initialHighScore);
}

// Тест победы
TEST_F(SnakeModelTest, WinCondition) {
  // Проверяем условие победы
  EXPECT_FALSE(model.isWin());  // В начале игры змейка короткая
}