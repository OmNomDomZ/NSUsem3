#include "gameObject.h"

#include "bullets.h"

void gameObject::out(int y, int x, const std::string &s) {
  wmove(stdscr, y, x);
  wprintw(stdscr, "%s", s.c_str());
}

steady_clock_t gameObject::now() {
  return std::chrono::steady_clock::now();
}