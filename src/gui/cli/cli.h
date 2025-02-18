#ifndef CLI_H
#define CLI_H
#include <ncurses.h>
#include <string.h>

#include "../../brick_game/tetris/tetris.h"

typedef enum { TETRIS, SNAKE } Game_name;

/**
 * @brief Initializes the graphical user interface for the game. This function
 * sets up the terminal for displaying the game, initializes color pairs, and
 * configures terminal settings such as cursor visibility and input modes.
 */
void initGui();

/**
 * @brief Displays the menu with game selection. Allows to choose between tetris
 * and snake.
 */
void printMenu();

/**
 * @brief Prints the entire game state to the screen, including the game
 * field, the next figure, and game information like score and level. It
 * also refreshes the screen to update the display.
 * @param game: The current game state containing field, next figure, and
 * game
 * @param game_name Uses for dynamically displaying name of agame
 * stats.
 */
void printGame(GameInfo_t game, char* game_name);

/**
 * @brief Displays the game field on the screen. It iterates through each cell
 * of the game field and prints a space character with a color based on the
 * cell's state.
 * @param game: The current game state containing the field to be displayed.
 */
void printField(GameInfo_t game);

/**
 * @brief Displays the next figure on the screen in a designated area. It uses a
 * different color to distinguish the next figure from the game field.
 * @param game: The current game state containing the next figure to be
 * displayed.
 */
void printNextFigure(GameInfo_t game);

/**
 * @brief Prints game-related information such as the current level, speed,
 * score, and high score. It also displays controls and game status (e.g.,
 * paused) to the player.
 * @param game: The current game state containing information to be displayed.
 */
void printInfo(GameInfo_t game);

/**
 * @brief Reads a single character from the keyboard input and returns an action
 * based on the key pressed. Actions include moving the figure in different
 * directions, starting a new game, pausing, and terminating the game.
 * @return UserAction_t: The action to be taken based on the user's input.
 */
UserAction_t getAction();

#endif