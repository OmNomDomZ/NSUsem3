#include "bullets.h"

void bullets::move(int& c, std::vector<std::pair<int, int>> position, int bulletPosition) {
  if (c == ' ')
  {
    addBullet(position[0].first, position[0].second, now());
  }
  defineBulletDirection(bulletPosition);
}

void bullets::action() {
  init_pair(bullet_color_pair, COLOR_RED, COLOR_BLACK);

  attron(COLOR_PAIR(bullet_color_pair));
  for (auto& bullet : bullets) {
    if ((now() - bullet.last_time) / 1ms > bulletSpeed) {
      bullet.h += getBulletDirection();
      bullet.last_time = now();
    }
    out(bullet.h + getBulletDirection(), bullet.w, "*");
  }
  removeBullets();
  attroff(COLOR_PAIR(bullet_color_pair));
}

void bullets::removeBullets() {
  getmaxyx(stdscr, screenHeight, screenWidth);
  bullets.erase(
      std::remove_if(bullets.begin(), bullets.end(), [this](const Bullet& b) { return b.h < 2 || b.h > (screenHeight - 3);}),
      bullets.end()
  );
}

void bullets::addBullet(int w, int h, steady_clock_t time) {
  bullets.push_back(Bullet{w, h, time});
}

void bullets::defineBulletDirection(int bulletDir) {
    bulletDirection = bulletDir;

}

std::vector<std::pair<int, int>> bullets::getObjects() {
  std::vector<std::pair<int, int>> positions;
  for (auto i = bullets.begin(); i < bullets.end(); ++i)
  {
    positions.emplace_back(i->h, i->w);
  }
  return positions;
}
int bullets::getBulletDirection() { return bulletDirection; }

void bullets::removeObject(std::pair<int, int> object) {}

int bullets::getInf() { return 0; }

void bullets::changeInf() {}
