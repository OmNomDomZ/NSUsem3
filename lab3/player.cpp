
#include "player.h"

#include <curses.h>
#include <algorithm>

player::player()
{
  getmaxyx(stdscr, screenHeight, screenWidth);

  h = screenHeight / 2;
  w = screenWidth / 2;

  ok = 1;

  init_pair(player_color_pair, COLOR_YELLOW, COLOR_BLUE);
  init_pair(player_bullet_color_pair, COLOR_GREEN, COLOR_BLACK);

  playerBullets.setBulletColor(player_bullet_color_pair);
  playerBullets.setBulletSpeed(playerBulletSpeed);
  playerBullets.defineBulletDirection(h, screenHeight);
}

void player::move(int c) {
  switch(c) {
  case KEY_LEFT: --w; break;
  case KEY_RIGHT: ++w; break;
  case KEY_UP: --h; break;
  case KEY_DOWN: ++h; break;
  case ' ': playerBullets.addBullet(w, h, now()); break;
  }
}

void player::action() {
  int h1, w1;
  getmaxyx(stdscr, h1, w1);
  w = std::clamp(w, 1, w1-2);
  h = std::clamp(h, 1, h1-2);
  attron(COLOR_PAIR(player_color_pair));
  out(h, w, "M");
  attroff(COLOR_PAIR(player_color_pair));

  playerBullets.action();
  playerBullets.removeBullets();
}

bullets& player::getBullets() {
  return playerBullets;
}

int player::getHeight() {
  return h;
}

int player::getWidth() {
  return w;
}

bool player::isAlive()
{
  return ok;
}

void player::dead()
{
  ok = false;
}


