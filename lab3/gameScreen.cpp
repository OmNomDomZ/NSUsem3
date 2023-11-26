
#include "gameScreen.h"

void out(int y, int x, const std::string &s)
{
  wmove(stdscr, y, x);
  wprintw(stdscr, "%s", s.c_str());
}

void gameScreen::makeScreen() {
  setlocale(LC_ALL, "");

  // init curses
  initscr();
  // disable buffering
  cbreak();
  // disable input character echo
  noecho();
  // disable cursor
  curs_set(FALSE);
  // enable function keys as single character values, like KEY_LEFT, etc.
  keypad(stdscr, TRUE);
  // set a very small delay in milliseconds for getch/wgetch to wait for input. Without it, getch/wgetch would block.
  timeout(50);

  if (has_colors() == FALSE) {
    endwin();
    std::cerr << "Your terminal does not support color\n";
    exit(1);
  }
  start_color();
  init_pair(main_color_pair, COLOR_WHITE, COLOR_BLACK);
}

void gameScreen::getConsoleDimensions() {
  getmaxyx(stdscr, h1, w1);
}

void gameScreen::printTitle() {
//  ssize_t title_size = snprintf(NULL, 0, title_format_str, bullets.size());
  ssize_t title_size = snprintf(NULL, 0, title_format_str, 0);
  wmove(stdscr, 1, (w1-title_size)/2);
  wprintw(stdscr, title_format_str, 0);
//  wprintw(stdscr, title_format_str, bullets.size());
}

void gameScreen::displayTheBorder() {
  for (int i = 1; i < w1; ++i) {
    out(0, i, "-");
    out(h1-1, i, "-");
  }
  for (int i = 1; i < h1-1; ++i) {
    out(i, 0, "|");
    out(i, w1-1, "|");
  }
  out(0, 0, "+");
  out(0, w1-1, "+");
  out(h1-1, 0, "+");
  out(h1-1, w1-1, "+");
}