#include "tetris_window.h"

#include <QKeyEvent>
#include <QPainter>

namespace s21 {

TetrisWindow::TetrisWindow(QWidget *parent) : QMainWindow(parent) {
  setFixedSize(600, 800);
  setWindowTitle("Tetris");

  initGame();

  connect(&timer_, &QTimer::timeout, this, &TetrisWindow::updateGame);
  timer_.start(110);
}

TetrisWindow::~TetrisWindow() {
  if (tetg != nullptr) {
    freeGame(tetg);
  }
}

void TetrisWindow::updateGame() {
  if (tetg == nullptr) return;

  GameInfo_t info = updateCurrentState();

  if (tetg->state == GAMEOVER) {
    timer_.stop();
    update();
    return;
  }

  if (!info.pause) {
    timer_.setInterval(500 - info.speed * 30);
  }

  update();
}

void TetrisWindow::keyPressEvent(QKeyEvent *event) {
  if (tetg == nullptr || event->isAutoRepeat()) return;

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

  userInput(action, false);
  update();
}

void TetrisWindow::paintEvent(QPaintEvent *) {
  if (tetg == nullptr) return;

  QPainter painter(this);
  drawGrid(painter);
  drawField(painter);
  drawNextFigure(painter);
  drawScore(painter);
}

void TetrisWindow::drawField(QPainter &painter) {
  GameInfo_t info = updateCurrentState();

  for (int y = 0; y < 20; y++) {
    for (int x = 0; x < 10; x++) {
      if (info.field[y][x] != 0) {
        QRect rect(FIELD_OFFSET_X + x * CELL_SIZE,
                   FIELD_OFFSET_Y + y * CELL_SIZE, CELL_SIZE, CELL_SIZE);

        painter.fillRect(rect, getColorForCell(info.field[y][x]));
        painter.drawRect(rect);
      }
    }
  }
}

void TetrisWindow::drawNextFigure(QPainter &painter) {
  GameInfo_t info = updateCurrentState();
  if (info.next) {
    int startX = FIELD_OFFSET_X + 350;  // Координаты X для следующей фигуры
    int startY = FIELD_OFFSET_Y + 180;  // Координаты Y для следующей фигуры
    int cellSize = 20;  // Размер ячейки для следующей фигуры (меньше основного)

    // Рисуем каждую ячейку следующей фигуры
    for (int y = 0; y < tetg->figurest->size; y++) {
      for (int x = 0; x < tetg->figurest->size; x++) {
        if (info.next[y][x] != 0) {
          QRect rect(startX + x * cellSize, startY + y * cellSize, cellSize,
                     cellSize);

          painter.fillRect(rect, getColorForCell(info.next[y][x]));
          painter.drawRect(rect);
        }
      }
    }
  }
}

void TetrisWindow::drawScore(QPainter &painter) {
  GameInfo_t info = updateCurrentState();

  // Настраиваем шрифт
  QFont font = painter.font();
  font.setPointSize(14);
  painter.setFont(font);

  // Координаты для текста
  int textX = FIELD_OFFSET_X + 350;
  int textY = FIELD_OFFSET_Y;
  int lineHeight = 30;

  // Рисуем всю информацию
  painter.drawText(textX, textY, "TETRIS");
  painter.drawText(textX, textY + lineHeight,
                   QString("Score: %1").arg(info.score));
  painter.drawText(textX, textY + 2 * lineHeight,
                   QString("High Score: %1").arg(info.high_score));
  painter.drawText(textX, textY + 3 * lineHeight,
                   QString("Level: %1").arg(info.level));
  painter.drawText(textX, textY + 4 * lineHeight,
                   QString("Speed: %1").arg(info.speed));

  // Отображаем следующую фигуру
  painter.drawText(textX, textY + 5 * lineHeight, "Next Figure:");

  // Отображаем состояние игры
  if (tetg->state == GAMEOVER) {
    painter.setPen(Qt::red);
    painter.drawText(textX, textY + 9 * lineHeight, "GAME OVER");
  } else if (info.pause) {
    painter.setPen(Qt::blue);
    painter.drawText(textX, textY + 9 * lineHeight, "PAUSE");
  }

  // Отображаем подсказки по управлению
  painter.setPen(Qt::gray);
  int controlsY = textY + 10 * lineHeight;
  painter.drawText(textX, controlsY, "Controls:");
  painter.drawText(textX, controlsY + lineHeight, "↑ - Rotate");
  painter.drawText(textX, controlsY + 2 * lineHeight, "← → - Move");
  painter.drawText(textX, controlsY + 3 * lineHeight, "↓ - Drop");
  painter.drawText(textX, controlsY + 4 * lineHeight, "P - Pause");
  painter.drawText(textX, controlsY + 5 * lineHeight, "Enter - Start");
  painter.drawText(textX, controlsY + 6 * lineHeight, "Q - Quit");
}

void TetrisWindow::drawGrid(QPainter &painter) {
  painter.setPen(Qt::lightGray);

  // Вертикальные линии
  for (int x = 0; x <= 10; x++) {
    painter.drawLine(FIELD_OFFSET_X + x * CELL_SIZE, FIELD_OFFSET_Y,
                     FIELD_OFFSET_X + x * CELL_SIZE,
                     FIELD_OFFSET_Y + 20 * CELL_SIZE);
  }

  // Горизонтальные линии
  for (int y = 0; y <= 20; y++) {
    painter.drawLine(FIELD_OFFSET_X, FIELD_OFFSET_Y + y * CELL_SIZE,
                     FIELD_OFFSET_X + 10 * CELL_SIZE,
                     FIELD_OFFSET_Y + y * CELL_SIZE);
  }
}

QColor TetrisWindow::getColorForCell(int value) {
  switch (value) {
    case 1:
      return Qt::red;
    case 2:
      return Qt::blue;
    case 3:
      return Qt::green;
    case 4:
      return Qt::yellow;
    case 5:
      return Qt::cyan;
    case 6:
      return Qt::magenta;
    case 7:
      return Qt::darkGreen;
    default:
      return Qt::white;
  }
}

void TetrisWindow::keyReleaseEvent(QKeyEvent *event) { event->accept(); }

}  // namespace s21