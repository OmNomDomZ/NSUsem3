#include "enemy.h"

#include "random"
#include "algorithm"

enemy::enemy() : enemies(numEnemies, {0, 0, now()})
{
  getmaxyx(stdscr, screenHeight, screenWidth);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(1, 1000);
  int count = 0;

  for (auto& enemy : enemies)
  {
    enemy.h = std::clamp(enemy.h, 1, screenHeight - 2);
    enemy.w = std::clamp(enemy.w, 1, screenWidth - 2);

    std::uniform_int_distribution<> distr(count * screenWidth / numEnemies, screenWidth / numEnemies * (count + 1));

    enemy.h = 3;

    int randomNum = distr(gen);
    enemy.w = randomNum % screenWidth;

    init_pair(enemy_color_pair, COLOR_WHITE, COLOR_YELLOW);

    count++;
  }
}

void enemy::move(int& enemyWidth, std::vector<std::pair<int, int>> position, int bulletPosition) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(1, 10);
  int randomNum = distr(gen);

  if (randomNum % 2 == 0 && enemyWidth < screenWidth - 2)
  {
    enemyWidth++;
  }
  else if (enemyWidth > 1)
  {
    enemyWidth--;
  }
}

void enemy::action()
{
  for (auto& enemy : enemies)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 10);
    int randomNum = distr(gen);
    attron(COLOR_PAIR(enemy_color_pair));
    if ((now() - enemy.last_time) / 1ms > enemySpeed) {
      if (randomNum == 1)
      {
        if (enemy.h <= screenHeight - 7)
        {
          DownMove(enemy);
        }
      }
      move(enemy.w, {}, 0);
      enemy.last_time = now();
    }
    out(enemy.h, enemy.w, "Z");
  attroff(COLOR_PAIR(enemy_color_pair));
  }
}

std::vector<std::pair<int, int>> enemy::getObjects() {
  std::vector<std::pair<int, int>> positions;
  for (auto i = enemies.begin(); i < enemies.end(); ++i)
  {
    positions.emplace_back(i->h, i->w);
  }
  return positions;
}

void enemy::removeEnemy(const enemy::Enemy& enemyToRemove) {
  auto it = std::find_if(enemies.begin(), enemies.end(),
                         [&enemyToRemove](const Enemy& enemy) {
                           return enemy.w == enemyToRemove.w && enemy.h == enemyToRemove.h;
                         });

  if (it != enemies.end()) {
    enemies.erase(it);
  }
}

void enemy::DownMove(enemy::Enemy &enemy) {
  ++enemy.h;
}

int enemy::getBulletDirection() {
  return bulletDirection;
}

void enemy::removeObject(std::pair<int, int> object) {
  for (auto& enemy : enemies)
  {
    if(enemy.h == object.first && enemy.w == object.second)
    {
      removeEnemy(enemy);
    }
  }

}
int enemy::getInf() { return numEnemies; }

void enemy::changeInf() {numEnemies--;}
