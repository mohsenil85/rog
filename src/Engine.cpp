#include "libtcod.hpp"
#include "Actor.hpp"
#include "Map.hpp"
#include "Engine.hpp"
Engine::Engine() : gameStatus(STARTUP), fovRadius(10) {
  TCODConsole::initRoot(80,50, "tut", false);
  player = new Actor (40,25,'@',"logan", TCODColor::white);
  actors.push(player);
  map = new Map(80, 45);
}
Engine::~Engine(){
  actors.clearAndDelete();
  delete map;
}

void Engine::update(){
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
    if (player->moveOrAttack(player->x+dx,player->y+dy)) {
      map->computeFov();
    }
  }

  if (gameStatus == NEW_TURN) {
    for (Actor **iterator=actors.begin(); 
        iterator!= actors.end();
        iterator++) {
      Actor *actor = *iterator;
      if (actor != player) {
        actor->update();
      }
    }
  }
  /*switch (key.c){
    case 'J':
    if (! map->isWall(player->x,player->y+5)){
    player->y=player->y+5; 
    computeFov=true;
    }
    break;
    case 'j':
    if (! map->isWall(player->x,player->y+1)){
    player->y++; 
    computeFov=true;
    }
    break;
    case 'K': 
    if (! map->isWall(player->x,player->y-5)){
    player->y=player->y-5; 
    computeFov=true;
    }
    break;
    case 'k': 
    if (! map->isWall(player->x,player->y-1)){
    player->y--; 
    computeFov=true;
    }
    break;
    case 'L': 
    if (! map->isWall(player->x+5,player->y)){
    player->x=player->x+5; 
    computeFov=true;
    }
    break;
    case 'l': 
    if (! map->isWall(player->x+1,player->y)){
    player->x++; 
    computeFov=true;
    }
    break;
    case 'H': 
    if (! map->isWall(player->x-5,player->y)){
    player->x=player->x-5; 
    computeFov=true;
    }
    break;
    case 'h': 
    if (! map->isWall(player->x-1,player->y)){
    player->x--; 
    computeFov=true;
    }
    break;
    default: break;
    }
    if (computeFov){
    map->computeFov();
    computeFov=false;
    }*/
}

void Engine::render(){
  TCODConsole::root->clear();
  map-> render();
  for (Actor **iterator=actors.begin();
      iterator != actors.end();
      iterator++){
    Actor *actor = *iterator;
    if (map->isInFov(actor->x,actor->y)) {
      (*iterator)->render();
    }
  }
}
