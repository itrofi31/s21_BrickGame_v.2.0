#ifndef SNAKE_WINDOW_H
#define SNAKE_WINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "../../brick_game/snake/controller.h"
#include "../../brick_game/snake/model.h"

namespace s21 {

class SnakeWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit SnakeWindow(QWidget *parent = nullptr);
  virtual ~SnakeWindow();

 protected:
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

 private slots:
  void updateGame();

 private:
  static const int CELL_SIZE = 30;
  static const int FIELD_OFFSET_X = 50;
  static const int FIELD_OFFSET_Y = 50;

  SnakeModel model_;
  SnakeController controller_;
  QTimer timer_;
  void initializeGame();
  void drawField(QPainter &painter);
  void drawScore(QPainter &painter);
};

}  // namespace s21

#endif