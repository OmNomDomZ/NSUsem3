#ifndef LAB3_GAMESCREEN_H
#define LAB3_GAMESCREEN_H

#include <curses.h>
#include <iostream>
#include <chrono>


class gameScreen{
private:
  int h1;
  int w1;

  const char* title_format_score_str = "Your score: %lu";

  const char* title_format_numOfEnemies_str = "The number of enemies: %lu";

  const char* title_Win_str = "Game Over";

  const char* title_gameOver_str = "Game Over";

  const int main_color_pair = 1;

public:
  void makeScreen();

  void getConsoleDimensions();

  void printTitle(int score, int numEnemies);

  void displayTheBorder();

  void gameOver();

  void printWinTitle(int score);
};



#endif