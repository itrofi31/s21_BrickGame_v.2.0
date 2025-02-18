#ifndef TETRIS_WINDOW_H
#define TETRIS_WINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <chrono>

extern "C" {
#include "../../brick_game/tetris/tetris.h"
}

namespace s21 {

class TetrisWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit TetrisWindow(QWidget *parent = nullptr);
  ~TetrisWindow();

 protected:
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void paintEvent(QPaintEvent *) override;

 private:
  static const int CELL_SIZE = 30;
  static const int FIELD_OFFSET_X = 50;
  static const int FIELD_OFFSET_Y = 50;

  void initializeGame();
  void updateGame();
  void drawField(QPainter &painter);
  void drawNextFigure(QPainter &painter);
  void drawScore(QPainter &painter);
  void drawGrid(QPainter &painter);
  QColor getColorForCell(int value);

  QTimer timer_;
  std::chrono::steady_clock::time_point last_update_;
  std::chrono::milliseconds update_interval_;
};

}  // namespace s21

#endif  // TETRIS_WINDOW_H