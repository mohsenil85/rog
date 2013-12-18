#include <stdio.h>
#include "main.hpp"

Destructible::Destructible(float maxHp, float defense, const char *corpseName):
  maxHp(maxHp), defense(defense), corpseName(corpseName){
  }

float Destructible::takeDamage(Actor *owner, float damage) {
  damage -= defense;
  (if damage > 0) {
    hp -= damage;
    if (hp <= 0){
      die(owner);
    }
  } else {
    damage = 0;
  }
  return damage;
}

void Destructible::die(Actor *owner) {
  owner->ch='%';
  owner->col=TCODColor::darkRed;
  owner->name=corpseName;
  owner->blocks=false;
  engine.sendToBack(owner);
}

void MonsterDestructible::die(Actor *owner) {
  printf("%s dies\n", owner->name);
  Destructible::die(owner);
}
void PlayerDestructible::die(Actor *owner) {
  printf("you die!\n");
  Destructible::die(owner);
  engine.gameStatus=Engine::DEFEAT;
}
