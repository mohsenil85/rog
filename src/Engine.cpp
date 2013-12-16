#include "libtcod.hpp"
#include "Actor.hpp"
#include "Map.hpp"
#include "Engine.hpp"
Engine::Engine(){
  TCODConsole::initRoot(80,50, "tut", false);
  player = new Actor (40,25,'@', TCODColor::white);
  actors.push(player);
  actors.push(new Actor(60,13, '$',TCODColor::yellow));
  map = new Map(80, 45);
}
Engine::~Engine(){
  actors.clearAndDelete();
  delete map;
}

void Engine::update(){
  TCOD_key_t key = TCODConsole::checkForKeypress();
  switch (key.c){
    case 'j':
      if (! map->isWall(player->x,player->y+1)){
        player->y++; 
      }
      break;
    case 'k': 
      if (! map->isWall(player->x,player->y-1)){
        player->y--; 
      }
      break;
    case 'l': 
      if (! map->isWall(player->x+1,player->y)){
        player->x++; 
      }
      break;
    case 'h': 
      if (! map->isWall(player->x-1,player->y)){
        player->x--; 
      }
      break;
    default: break;
  }
}

void Engine::render(){
  TCODConsole::root->clear();
  map-> render();
  for (Actor **iterator=actors.begin();
      iterator != actors.end();
      iterator++){
    (*iterator)->render();
  }
}
