#include "cli.h"

void initGui() {
  initscr();
  curs_set(0);
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_YELLOW);
  init_pair(2, COLOR_GREEN, COLOR_GREEN);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_GREEN, COLOR_BLACK);
  init_pair(5, COLOR_RED, COLOR_RED);

  keypad(stdscr, TRUE);
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  scrollok(stdscr, TRUE);
}

void printMenu() {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      attron(COLOR_PAIR(3));
      mvaddch(i, j, ' ');
      attroff(COLOR_PAIR(3));
    }
  }
  attron(COLOR_PAIR(3));
  mvwprintw(stdscr, 1, 4, "BrickGame 2.0");
  attroff(COLOR_PAIR(3));
  attron(COLOR_PAIR(3));
  mvwprintw(stdscr, 5, 1, "Snake");
  mvwprintw(stdscr, 7, 1, "Tetris");
  attroff(COLOR_PAIR(3));

  attron(COLOR_PAIR(4));
  mvwprintw(stdscr, 3, 1, "Which game to play?");
  mvwprintw(stdscr, 4, 1, "---------------------");
  mvwprintw(stdscr, 5, 9, "-> press T");
  mvwprintw(stdscr, 7, 9, "-> press S");
  mvwprintw(stdscr, 9, 1, "Exit");
  mvwprintw(stdscr, 9, 9, "-> press ESC");
  attroff(COLOR_PAIR(4));
}

void printGame(GameInfo_t game, char* game_name) {
  printField(game);
  Game_name which_game = SNAKE;
  if (strcmp(game_name, "Tetris") == 0) {
    which_game = TETRIS;
  }

  attron(COLOR_PAIR(3));
  mvwprintw(stdscr, 1, 10, game_name);
  if (which_game == TETRIS) printNextFigure(game);
  attroff(COLOR_PAIR(3));

  printInfo(game);
  if (which_game == TETRIS) freeGui(game, 5, 20);
  refresh();
}

void printField(GameInfo_t game) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      int sym;
      if (game.field[i][j] == 0) sym = 1;
      if (game.field[i][j] == 1) sym = 2;
      if (game.field[i][j] == 2) sym = 5;
      attron(COLOR_PAIR(sym));
      mvaddch(i + 3, j * 2 + 2, ' ');
      mvaddch(i + 3, j * 2 + 3, ' ');
      attroff(COLOR_PAIR(sym));
    }
  }
}

void printNextFigure(GameInfo_t game) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      int sym = game.next[i][j] != 0 ? 2 : 0;
      attron(COLOR_PAIR(sym));
      mvaddch(i + 5, j * 2 + 28, ' ');
      mvaddch(i + 5, j * 2 + 29, ' ');
      attroff(COLOR_PAIR(sym));
    }
  }
}

void printInfo(GameInfo_t game) {
  attron(COLOR_PAIR(4));
  if (game.next) mvwprintw(stdscr, 3, 26, "Next figure:");
  mvwprintw(stdscr, 11, 26, "Lvl: %d", game.level);
  mvwprintw(stdscr, 13, 26, "Speed: %d", game.speed);
  mvwprintw(stdscr, 15, 26, "Score: %d", game.score);
  clrtoeol();
  mvwprintw(stdscr, 17, 26, "High score: %d", game.high_score);
  if (game.pause) {
    mvwprintw(stdscr, 12, 2, "Press ENTER to start");
  }
  attroff(COLOR_PAIR(4));
  attron(COLOR_PAIR(6));
  mvwprintw(stdscr, 24, 6, "Press:");
  mvwprintw(stdscr, 24, 14, "Start: 'Enter'");
  mvwprintw(stdscr, 25, 14, "Pause: 'p'");
  mvwprintw(stdscr, 26, 14, "Exit: 'q'");
  mvwprintw(stdscr, 27, 14, "Arrows to move");
  if (game.next) {
    mvwprintw(stdscr, 29, 14, "Arrow down to plant: 'v'");
    mvwprintw(stdscr, 28, 14, "Arrow up to rotate: '^'");
  }
  attroff(COLOR_PAIR(6));
}

UserAction_t getAction() {
  int ch = getch();

  if (ch == ERR) {
    return Action;
  }

  switch (ch) {
    case KEY_LEFT:
      return Left;
    case KEY_RIGHT:
      return Right;
    case KEY_UP:
      return Up;
    case KEY_DOWN:
      return Down;
    case '\n':
      return Start;
    case 'p':
      return Pause;
    case 'q':
      return Terminate;
    default:
      return Action;
  }
}
