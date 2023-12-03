#include <curses.h>

#include "player.h"
#include "bullets.h"
#include "gameScreen.h"
#include "enemy.h"
#include "gameObject.h"
#include "gameEngine.h"
#include <thread>

int main() {

  gameScreen gameScreen;
  gameScreen.makeScreen();


  gameScreen.getConsoleDimensions();

  gameEngine gameEngine(gameScreen);

  int c;

  while ('q' != (c = getch()) && gameEngine.gameStatus())
  {
    // clear the screen
    clear();

    gameEngine.update(c);

    // discards user input that we haven't handled yet. MAY NOT BE WHAT YOU WANT!
    flushinp();

    // don't forget to call refresh/wrefresh to make your changes visible
    refresh();

  }

  if (!gameEngine.gameStatus())
  {
    clear();
    flushinp();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    refresh();

    getch();
  }

  // returns terminal to its normal state. DO NOT FORGET TO CALL ON EXIT!
  endwin();

  return 0;
}