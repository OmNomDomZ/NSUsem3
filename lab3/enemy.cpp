#include "enemy.h"

void enemy::getPosition() {
  int h1, w1;
  getmaxyx(stdscr, h1, w1);

  h = 2;
  w = rand() % w1;
  init_pair(enemy_color_pair, COLOR_MAGENTA, COLOR_CYAN);

  enemyBullets.get();

}

void enemy::move()
{
  size_t direction = rand() % 2;
  if (direction % 2 == 0)
  {
    w++;
  }
  else
  {
    w--;
  }
}


void enemy::action()
{
  attron(COLOR_PAIR(enemy_color_pair));
  if ((now() - last_time) / 1ms > 300) {
    move();
    last_time = now();
  }
  out(h, w, "Z");
  attroff(COLOR_PAIR(enemy_color_pair));

  enemyBullets.addBullet(w, h, now());
  enemyBullets.action();
  enemyBullets.removeBullets();
}
