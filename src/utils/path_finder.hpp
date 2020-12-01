#pragma once
#include "../map/tile.hpp"
#include "../enemies/enemy.hpp"
#include "../map/map.hpp"


class FindPath {
public:
    FindPath();

    Grid getPrevious(){
        return previous_tile;
    }

    Grid getCurrent(){
        return current_tile;
    }

    void setCurrent(Enemy enemy){
        current_tile = enemy.getCoordinates(); //inte rätt
    }

    bool next(Enemy enemy){
        //kolla vilken ruta den e i
        //granska 4 runtvarande
        //kolla vad för typ av tile det är och att det int är previous
        if (current_tile[x+1][y].type == path ){

        }
    }


private:
    Grid  previous_tile;
    Grid  current_tile;
    Grid  next_tile;


}
//Map.gettile för att få coordinaterna
//tile.gettype för att få typen så att den vet vilken som e nästa

//spara alltid den gamla att den inte far dit
// skanna alla 4 tiles runtom för att kolla nästa lediga tile
// kolla att man får enemins position