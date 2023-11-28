#include "enemy.h"

#include "random"
#include "algorithm"

enemy::enemy() : enemies(numEnemies, {0, 0, now()})
{
  getmaxyx(stdscr, screenHeight, screenWidth);
}

void enemy::getPosition() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(1, 1000);
  int count = 0;

  for (auto& enemy : enemies)
  {
    enemy.h = std::clamp(enemy.h, 1, screenHeight - 2);
    enemy.w = std::clamp(enemy.w, 1, screenWidth - 2);

    std::uniform_int_distribution<> distr(count * screenWidth / numEnemies, screenWidth / numEnemies * (count + 1));

    enemy.h = 2;

    int randomNum = distr(gen);
    enemy.w = randomNum % screenWidth;

    init_pair(enemy_color_pair, COLOR_BLACK, COLOR_RED);
    init_pair(enemy_bullet_color, COLOR_RED, COLOR_BLACK);

    enemyBullets.setBulletSpeed(enemyBulletsSpeed);
    enemyBullets.setBulletColor(enemy_bullet_color);
    enemyBullets.defineBulletDirection(enemy.h, screenHeight);

    count++;
  }
}

void enemy::move(Enemy& enemy)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(1, 10);
  int direction = distr(gen);

  if (direction % 2 == 0 && enemy.w < screenWidth - 2)
  {
    enemy.w++;
  }
  else if (enemy.w > 1)
  {
    enemy.w--;
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
        DownMove(enemy);
        removeEnemy();
      }
      move(enemy);
      enemy.last_time = now();
      enemyBullets.addBullet(enemy.w, enemy.h, now());
    }
    out(enemy.h, enemy.w, "Z");
    enemyBullets.action();
    enemyBullets.removeBullets();
  attroff(COLOR_PAIR(enemy_color_pair));
  }
}

void enemy::DownMove(enemy::Enemy &enemy) {
  ++enemy.h;
}

void enemy::removeEnemy() {
  enemies.erase(
      std::remove_if(enemies.begin(), enemies.end(), [this](const Enemy& enemy) {return enemy.h >= (screenHeight - 1);}),
      enemies.end()
      );
}

