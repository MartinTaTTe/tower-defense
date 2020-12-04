#pragma once
#include <utility>
#include "../map/tile.hpp"
#include "../enemies/enemy.hpp"
#include "../map/map.hpp"


class FindPath {
public:
//skicka in map och start rutan
    FindPath(int x, int y, Map* map) {
        setCurrent(x, y);
        map_ = map;
    };

    std::pair<int, int> getPrevious(){
        return previous_tile_;
    };

    std::pair<int, int> getCurrent(){
        return current_tile_;
    };

    std::vector<std::pair<int, int>> getNext(){
        return next_tile_;
    };

    void setCurrent(int x, int y){
        current_tile_.first = x;
        current_tile_.second = y;
    };

    void setPrevious(std::pair<int, int> tile) {
        previous_tile_ = tile;
    };

    void setNext(int x, int y){
        next_tile_.push_back(std::make_pair(x + 1, y));
        next_tile_.push_back(std::make_pair(x - 1, y));
        next_tile_.push_back(std::make_pair(x, y + 1));
        next_tile_.push_back(std::make_pair(x, y - 1));

    };

    std::pair<int,int> move(){
        //kolla vilken ruta den e i
        //granska 4 runtvarande
        //kolla vad för typ av tile det är och att det int är previous
        for (std::pair<int, int> x : next_tile_){
            if(map_.GetTile(x.first, x.second).GetType() == Path && x != previous_tile_){
                setPrevious(current_tile_);
                setCurrent(x.first, x.second);
                break;
            }
        }
        return current_tile_;
    };

    std::pair<int,int> moveEnemy(Enemy enemy) {
        //int x = enemy.getx(); //finns int ännu
        //int y = enemy.gety(); // finns int ännu
        current_tile_ = enemy.GetTile();
        //setCurrent(x, y);
        setNext(current_tile_.first, current_tile_.second);
        return move();
    };


private:
    std::pair<int, int>  previous_tile_;
    std::pair<int, int>  current_tile_;
    std::vector<std::pair<int, int>>  next_tile_;
    Map* map_;


};
//Map.gettile för att få coordinaterna
//tile.gettype för att få typen så att den vet vilken som e nästa

//spara alltid den gamla att den inte far dit
// skanna alla 4 tiles runtom för att kolla nästa lediga tile
// kolla att man får enemins position;