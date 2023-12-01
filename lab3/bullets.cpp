
#include "bullets.h"

void bullets::action() {
  attron(COLOR_PAIR(bullet_color_pair));
  for (auto& bullet : bullets) {
    if ((now() - bullet.last_time) / 1ms > bulletSpeed) {
      bullet.h += bulletDirection;
      bullet.last_time = now();
    }
    out(bullet.h + bulletDirection, bullet.w, "*");
  }
  attroff(COLOR_PAIR(bullet_color_pair));
}

void bullets::removeBullets() {
  int h1, w1;
  getmaxyx(stdscr, h1, w1);
  bullets.erase(
      std::remove_if(bullets.begin(), bullets.end(), [h1](const Bullet& b) { return b.h < 2 || b.h > (h1 - 3);}),
      bullets.end()
  );
}

void bullets::addBullet(int w, int h, steady_clock_t time) {
  bullets.push_back(Bullet{w, h, time});
}

void bullets::defineBulletDirection(int h, int h1) {
  if (h >= h1 / 2)
  {
    bulletDirection = -1;
  }
  else
  {
    bulletDirection = 1;
  }
}

void bullets::setBulletSpeed(int speed) {
  bulletSpeed = speed;
}

void bullets::setBulletColor(const int color) {
  bullet_color_pair = color;
}

std::vector<bullets::Bullet>& bullets::getBullets()
{
  return bullets;
}
