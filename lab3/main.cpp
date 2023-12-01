
#include <curses.h>

#include "player.h"
#include "bullets.h"
#include "gameScreen.h"
#include "enemy.h"
#include "gameEngine.h"

int main() {
  gameScreen gameScreen;
  gameScreen.makeScreen();


  gameScreen.getConsoleDimensions();

  player player;

  enemy enemy;
  enemy.getPosition();


  gameEngine gameEngine(player, enemy);

  int c;

  while ('q' != (c = getch()) && gameEngine.gameStatus())
  {
    // clear the screen
    clear();

    // print title
    gameScreen.printTitle();

    gameScreen.displayTheBorder();

//    player.move(c);

    // discards user input that we haven't handled yet. MAY NOT BE WHAT YOU WANT!
    flushinp();

//    player.action();
//    enemy.action();

    gameEngine.update(c);

    // don't forget to call refresh/wrefresh to make your changes visible
    refresh();

  }

  // returns terminal to its normal state. DO NOT FORGET TO CALL ON EXIT!
  endwin();

  return 0;
}