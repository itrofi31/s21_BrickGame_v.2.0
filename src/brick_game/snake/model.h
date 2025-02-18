#ifndef MODEL_H
#define MODEL_H
#include <vector>

#include "../common.h"
namespace s21 {

/**
 * @brief Перечисление направлений движения змейки
 */
enum Direction { UP, DOWN, LEFT, RIGHT };

/**
 * @brief Структура для хранения координат
 */
struct Coord {
  int x, y;  ///< Координаты x и y
};

/**
 * @brief Класс модели игры "Змейка"
 * @details Реализует основную логику игры, включая движение змейки,
 * обработку столкновений и подсчет очков
 */
class SnakeModel {
 public:
  static const int WIN_LENGTH = 200;  ///< Длина для победы
  static const int INITIAL_LENGTH = 4;  ///< Начальная длина змейки
  static const int POINTS_PER_LEVEL = 50;  ///< Очки для следующего уровня
  static const int MAX_LEVEL = 10;  ///< Максимальный уровень
  static const char* HIGH_SCORE_FILE;  ///< Файл для сохранения рекорда

  /**
   * @brief Конструктор класса
   * @details Инициализирует начальное состояние игры
   */
  SnakeModel();

  /**
   * @brief Деструктор класса
   * @details Сохраняет рекорд при необходимости
   */
  ~SnakeModel();

  /**
   * @brief Инициализация игры
   * @details Устанавливает начальное положение змейки и другие параметры
   */
  void initialize();

  /**
   * @brief Обновление состояния игры
   * @details Обрабатывает движение змейки и проверяет столкновения
   */
  void update();

  /**
   * @brief Изменение направления движения змейки
   * @param newDirection Новое направление движения
   */
  void changeDirection(Direction newDirection);

  /**
   * @brief Получение текущего положения змейки
   * @return Константная ссылка на вектор координат змейки
   */
  const std::vector<Coord>& getSnake() const { return snake; }

  /**
   * @brief Получение позиции еды
   * @return Константная ссылка на координаты еды
   */
  const Coord& getFood() const { return food; }

  /**
   * @brief Завершение игры
   */
  void gameOver();

  /**
   * @brief Обновление рекорда
   */
  void updateHighScore();

  /**
   * @brief Загрузка рекорда из файла
   */
  void loadHighScore();

  /**
   * @brief Сохранение рекорда в файл
   */
  void saveHighScore() const;

  /**
   * @brief Обновление уровня
   */
  void updateLevel();

  /**
   * @brief Установка ускорения
   * @param acc Флаг ускорения
   */
  void setAccelerated(bool acc) { accelerated = acc; }

  // Геттеры
  GameState getState() const { return state; }
  int getScore() const { return score; }
  int getHighScore() const { return highScore; }
  int getLevel() const { return level; }
  bool isPaused() const { return state == PAUSE; }
  bool isWin() const { return snake.size() >= WIN_LENGTH; }

  /**
   * @brief Получение текущей скорости
   * @return Текущая скорость движения змейки
   */
  int getSpeed() const {
    int baseSpeed = level;
    if (accelerated) baseSpeed *= 2;
    return baseSpeed;
  }

  /**
   * @brief Установка состояния игры
   * @param newState Новое состояние
   */
  void setState(GameState newState) { state = newState; }

 private:
  void moveSnake();       ///< Перемещение змейки
  void generateFood();    ///< Генерация новой еды
  bool checkCollision();  ///< Проверка столкновений
  bool isValidDirection(
      Direction newDir) const;  ///< Проверка корректности направления

  std::vector<Coord> snake;  ///< Координаты сегментов змейки
  Coord food;                ///< Координаты еды
  Direction currentDirection;  ///< Текущее направление
  GameState state;             ///< Состояние игры
  int score;                   ///< Текущий счет
  int highScore;               ///< Рекорд
  int level;                   ///< Текущий уровень
  bool accelerated;            ///< Флаг ускорения
  int width;                   ///< Ширина поля
  int height;                  ///< Высота поля
};

}  // namespace s21
#endif