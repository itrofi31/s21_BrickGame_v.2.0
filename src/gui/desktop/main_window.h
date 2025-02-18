#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);

 private slots:
  void startSnake();
  void startTetris();

 private:
  QPushButton *snakeButton_;
  QPushButton *tetrisButton_;
};

}  // namespace s21

#endif