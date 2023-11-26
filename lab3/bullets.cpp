
#include "bullets.h"


void bullets::get() {
  init_pair(bullet_color_pair, COLOR_RED, COLOR_BLACK);
}

void bullets::action() {
  attron(COLOR_PAIR(bullet_color_pair));
  for (Bullet& b : bullets) {
    defineBulletDirection(b.h);
    if ((now() - b.last_time) / 1ms > 300) {
      b.h += bulletDirection;
      b.last_time = now();
    }
    out(b.h + bulletDirection, b.w, "*");
  }
  attroff(COLOR_PAIR(bullet_color_pair));
}

void bullets::removeBullets() {
  int h1, w1;
  getmaxyx(stdscr, h1, w1);
  bullets.erase(
      std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) { return b.h < 2 /*| b.h > (h1 - 2)*/; }),
      bullets.end()
  );
}

void bullets::addBullet(int w, int h, steady_clock_t time) {
  bullets.push_back(Bullet{w, h, time});
}

void bullets::defineBulletDirection(int h) {
  int h1, w1;
  getmaxyx(stdscr, h1, w1);
  Bullet b = bullets.front();
  if (b.h >= h1 / 2)
  {
    bulletDirection = -1;
  }
  else
  {
    bulletDirection = 1;
  }
}