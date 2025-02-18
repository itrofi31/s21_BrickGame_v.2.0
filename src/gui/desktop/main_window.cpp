#include "main_window.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

#include "snake_window.h"
#include "tetris_window.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  setFixedSize(400, 300);
  setWindowTitle("Brick Games");

  // Создаем центральный виджет и layout
  QWidget *centralWidget = new QWidget(this);
  QVBoxLayout *layout = new QVBoxLayout(centralWidget);

  // Заголовок
  QLabel *titleLabel = new QLabel("Select Game", this);
  titleLabel->setAlignment(Qt::AlignCenter);
  QFont titleFont = titleLabel->font();
  titleFont.setPointSize(20);
  titleLabel->setFont(titleFont);

  // Кнопки
  snakeButton_ = new QPushButton("Snake", this);
  tetrisButton_ = new QPushButton("Tetris", this);

  // Добавляем виджеты в layout
  layout->addSpacing(30);
  layout->addWidget(titleLabel);
  layout->addSpacing(30);
  layout->addWidget(snakeButton_);
  layout->addWidget(tetrisButton_);
  layout->addStretch();

  // Устанавливаем центральный виджет
  setCentralWidget(centralWidget);

  // Подключаем сигналы
  connect(snakeButton_, &QPushButton::clicked, this, &MainWindow::startSnake);
  connect(tetrisButton_, &QPushButton::clicked, this, &MainWindow::startTetris);
}

void MainWindow::startSnake() {
  SnakeWindow *snake = new SnakeWindow();
  snake->show();
  this->hide();

  // Когда окно змейки закрывается, показываем главное меню
  connect(snake, &SnakeWindow::destroyed, this, &MainWindow::show);
}

void MainWindow::startTetris() {
  TetrisWindow *tetris = new TetrisWindow();
  tetris->show();
  this->hide();

  // Когда окно тетриса закрывается, показываем главное меню
  connect(tetris, &TetrisWindow::destroyed, this, &MainWindow::show);
}

}  // namespace s21