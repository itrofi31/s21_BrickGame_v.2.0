#ifndef COMMON_H
#define COMMON_H
/**
 * @enum UserAction_t
 * @brief Enumerates possible user actions in the game.
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * @enum GameState
 * @brief Enumerates possible states in the game.
 */
typedef enum { INIT, DROP, MOVING, COLLISION, PAUSE, GAMEOVER } GameState;

#endif