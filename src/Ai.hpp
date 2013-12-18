class Ai{
  public:
    virtual void update(Actor *owner)=0;
};

class PlayerAi : public Ai {
  public:
    void update(Actor *owner);
  protected:
    bool moveOrAttack(Attacker *owner, int targetx, int targety);
};

void PlayerAi::update(Actor *owner){
  if (owner->destructible && owner->destructible->isDead()) {
    return;
  }
  int dx = 0, dy = 0;
  TCOD_key_t key = TCODConsole::checkForKeypress();
  if (gameStatus== STARTUP) map->computeFov();
  gameStatus = IDLE;
  switch (key.c){
    case 'K': dy=-5; break;
    case 'J': dy=+5; break;
    case 'H': dx=-5; break;
    case 'L': dx=+5; break;
    case 'k': dy=-1; break;
    case 'j': dy=+1; break;
    case 'h': dx=-1; break;
    case 'l': dx=+1; break;
  }

  if (dx != 0 || dy != 0){
    gameStatus = NEW_TURN;
    if (moveOrAttack(owner,owner->x+dx,owner->y+dy)) {
      map->computeFov();
    }
  }
}

bool PlayerAi::moveOrAttack(Actor *owner, int targetx, int targety){
  if  (engine.map->isWall(targetx, targety))  return false;
  for (Actor **iterator=engine.actors.begin();
      iterator != engine.actors.end();
      iterator++){
    if (actors->destructible
        && ! actors->destructible->isDead() 
        && actor->x == targetx
        && actor->y == targety){
      owner->attacker->attack(owner, actor);
      return false;
    }
  }

  for (Actor **iterator=engine.actors.begin();
      iterator != engine.actors.end();
      iterator++){
    Actor *actor = *iterator;


  }
}
