
#include "player.h"

#include <curses.h>
#include <algorithm>

player::player()
{
  getmaxyx(stdscr, screenHeight, screenWidth);

  h = screenHeight / 2;
  w = screenWidth / 2;

  init_pair(player_color_pair, COLOR_YELLOW, COLOR_BLUE);
}

void player::move(int&c, std::vector<std::pair<int, int>> position, int bulletPosition) {
  switch(c) {
    case KEY_LEFT: --w; break;
    case KEY_RIGHT: ++w; break;
    case KEY_UP: --h; break;
    case KEY_DOWN: ++h; break;
  }
}

void player::action() {
  int h1, w1;
  getmaxyx(stdscr, h1, w1);
  h = std::clamp(h, 1, h1-3);
  w = std::clamp(w, 1, w1-2);
  attron(COLOR_PAIR(player_color_pair));
  out(h, w, "M");
  attroff(COLOR_PAIR(player_color_pair));
}

int player::getBulletDirection() {
  return bulletDirection;
}

std::vector<std::pair<int, int>> player::getObjects() {
  std::vector<std::pair<int, int>> positions;
  positions.emplace_back(h, w);
  return positions;
}

void player::removeObject(std::pair<int, int> object) {
  isAlive_ = false;
}

int player::getInf() { return score; }

void player::changeInf() {score++;}
