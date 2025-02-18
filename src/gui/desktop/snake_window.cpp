#include "snake_window.h"

#include <QKeyEvent>
#include <QPainter>

namespace s21 {

SnakeWindow::SnakeWindow(QWidget *parent)
    : QMainWindow(parent), controller_(&model_) {
  setFixedSize(600, 800);
  setWindowTitle("Snake");
  initializeGame();

  connect(&timer_, &QTimer::timeout, this, &SnakeWindow::updateGame);
  timer_.start(100);  // Начальный интервал
}

void SnakeWindow::initializeGame() {
  // Инициализация начального состояния игры
  model_.initialize();
}

void SnakeWindow::keyPressEvent(QKeyEvent *event) {
  UserAction_t action = Action;

  switch (event->key()) {
    case Qt::Key_Left:
      action = Left;
      break;
    case Qt::Key_Right:
      action = Right;
      break;
    case Qt::Key_Up:
      action = Up;
      break;
    case Qt::Key_Down:
      action = Down;
      break;
    case Qt::Key_P:
      action = Pause;
      break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
      action = Start;
      break;
    case Qt::Key_Q:
      close();
      return;
  }

  controller_.handleInput(action, false);
  update();
}

void SnakeWindow::keyReleaseEvent(QKeyEvent *event) { event->accept(); }

void SnakeWindow::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  drawField(painter);
  drawScore(painter);
}

void SnakeWindow::updateGame() {
  controller_.update();

  // Обновляем интервал таймера в зависимости от скорости
  int baseDelay = 600;
  int levelDelay = 30 * model_.getSpeed();
  int delay = baseDelay - levelDelay;
  if (delay < 100) delay = 100;
  timer_.setInterval(delay);

  update();
}

void SnakeWindow::drawField(QPainter &painter) {
  // Рисуем сетку
  painter.setPen(Qt::lightGray);
  for (int x = 0; x <= 10; x++) {
    painter.drawLine(FIELD_OFFSET_X + x * CELL_SIZE, FIELD_OFFSET_Y,
                     FIELD_OFFSET_X + x * CELL_SIZE,
                     FIELD_OFFSET_Y + 20 * CELL_SIZE);
  }
  for (int y = 0; y <= 20; y++) {
    painter.drawLine(FIELD_OFFSET_X, FIELD_OFFSET_Y + y * CELL_SIZE,
                     FIELD_OFFSET_X + 10 * CELL_SIZE,
                     FIELD_OFFSET_Y + y * CELL_SIZE);
  }

  // Рисуем змейку
  painter.setPen(Qt::black);
  const auto &snake = model_.getSnake();
  for (const auto &segment : snake) {
    QRect rect(FIELD_OFFSET_X + segment.x * CELL_SIZE,
               FIELD_OFFSET_Y + segment.y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    painter.fillRect(rect, Qt::green);
    painter.drawRect(rect);
  }

  // Рисуем еду
  const auto &food = model_.getFood();
  QRect foodRect(FIELD_OFFSET_X + food.x * CELL_SIZE,
                 FIELD_OFFSET_Y + food.y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
  painter.fillRect(foodRect, Qt::red);
  painter.drawRect(foodRect);
}

void SnakeWindow::drawScore(QPainter &painter) {
  // Настраиваем шрифт
  QFont font = painter.font();
  font.setPointSize(14);
  painter.setFont(font);

  // Координаты для текста
  int textX = 50 + 350;
  int textY = 50;
  int lineHeight = 30;

  // Получаем информацию о состоянии игры
  int score = model_.getScore();
  int highScore = model_.getHighScore();
  int level = model_.getLevel();
  int speed = model_.getSpeed();

  // Рисуем всю информацию
  painter.setPen(Qt::black);
  painter.drawText(textX, textY, "SNAKE");
  painter.drawText(textX, textY + lineHeight, QString("Score: %1").arg(score));
  painter.drawText(textX, textY + 2 * lineHeight,
                   QString("High Score: %1").arg(highScore));
  painter.drawText(textX, textY + 3 * lineHeight,
                   QString("Level: %1").arg(level));
  painter.drawText(textX, textY + 4 * lineHeight,
                   QString("Speed: %1").arg(speed));

  // Отображаем состояние игры
  if (model_.getState() == GAMEOVER) {
    painter.setPen(Qt::red);
    painter.drawText(textX, textY + 6 * lineHeight, "GAME OVER");
  } else if (model_.isPaused()) {
    painter.setPen(Qt::blue);
    painter.drawText(textX, textY + 6 * lineHeight, "PAUSE");
  }

  if (model_.isWin()) {
    painter.setPen(Qt::green);
    painter.drawText(textX, textY + 7 * lineHeight, "YOU WIN!");
  }

  // Отображаем подсказки по управлению
  painter.setPen(Qt::gray);
  int controlsY = textY + 9 * lineHeight;
  painter.drawText(textX, controlsY, "Controls:");
  painter.drawText(textX, controlsY + lineHeight, "↑ ↓ ← → - Move");
  painter.drawText(textX, controlsY + 2 * lineHeight, "P - Pause");
  painter.drawText(textX, controlsY + 3 * lineHeight, "Enter - Start");
  painter.drawText(textX, controlsY + 4 * lineHeight, "Q - Quit");
}

SnakeWindow::~SnakeWindow() {
  // Cleanup if needed
}

}  // namespace s21