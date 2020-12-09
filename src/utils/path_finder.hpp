#pragma once
#include <utility>
#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>
//#include "../map/tile.hpp"
//#include "../enemies/enemy.hpp"
//#include "../map/map.hpp"


class PathFinder {
public:
//skicka in map och start rutan
    PathFinder(const std::string& map) : map_(map){
        //findPath();
        error_tile_.first = -1;
        error_tile_.second = -1;
        previous_tile_.first = -3;
        previous_tile_.second = -3;
        std::cout << "initialize" << std::endl;
    };

    //lagar en path och kollar om den e ok eller int.
    bool findPath() {
        std::ifstream file(map_);
        std::string line;
        std::getline(file,line);
        //tar bredd och höjd
        grid_width_  = stoi(line.substr(0, line.find('x')));
        grid_height_ = stoi(line.substr(line.find('x') + 1, line.find('x') + 2));

        //tar start punkter
        std::getline(file,line);
        x_start_ = stoi(line.substr(0, line.find(',')));
        y_start_ = stoi(line.substr(line.find(',') + 1, line.find(',') + 2));
 
        //tar slut punkter
        std::getline(file,line);
        x_end_ = stoi(line.substr(0, line.find(',')));
        y_end_ = stoi(line.substr(line.find(',') + 1, line.find(',') + 2));

        last_tile_.first = x_end_;
        last_tile_.second = y_end_;
        setCurrent(x_start_, y_start_);

        //addar start punkten till path vectorn
        path_.push_back(std::make_pair(x_start_, y_start_));
    
        //lagar en array som används för att kolla rutten
        while(std::getline(file,line)) {
            std::vector<int> vect;
            for (int i : line) {
                vect.push_back(i);
            }
            array_.push_back(vect);
        }
         file.close();
        //sätter en variabel
        //kollar rutten
        while(current_tile_ != last_tile_ && current_tile_ != error_tile_){
            setNext(current_tile_.first, current_tile_.second);
            path_.push_back(move());
        }
        
        if (current_tile_ == last_tile_){
            return true;
        } else {
            return false;
        }
    };

    /*friend bool operator!=(const std::pair<int,int> a, const std::pair<int,int> b){
        return (a.first != b.first || a.second != b.second);
    }*/

       //returnar pathen
    std::vector<std::pair<int,int>> getPath() {
        return path_;
    }

    void setCurrent(int x, int y){
        current_tile_.first = x;
        current_tile_.second = y;
    };

    void setPrevious(std::pair<int, int> tile) {
        previous_tile_.first = tile.first;
        previous_tile_.second = tile.second;
    };

    void setNext(int x, int y){
        if ((x + 1) < grid_width_) {
            next_tile_.push_back(std::make_pair(x + 1, y));
        }
        if ((x - 1) >= 0) {
            next_tile_.push_back(std::make_pair(x - 1, y));
        }   
        if ((y + 1) < grid_height_) {
            next_tile_.push_back(std::make_pair(x, y + 1));
        }
        if ((y - 1) >= 0) {
            next_tile_.push_back(std::make_pair(x, y - 1));
        }   
    };

    std::pair<int,int> move(){
        //kolla vilken ruta den e i
        //granska 4 runtvarande
        //kolla vad för typ av tile det är och att det int är previous
        
        for (std::pair<int, int> x : next_tile_){
            if(array_[x.second][x.first] == 48 && x != previous_tile_){
                setPrevious(current_tile_);
                setCurrent(x.first, x.second);
                next_tile_.clear();
                return current_tile_;
            }
        }
        setCurrent(-1, -1);
        return current_tile_;
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

private:
    std::pair<int, int>  previous_tile_;
    std::pair<int, int>  current_tile_;
    std::pair<int, int>  last_tile_;
    std::pair<int, int>  error_tile_;
    std::vector<std::pair<int, int>>  next_tile_;
    //Map* map_;
    std::vector<std::pair<int, int>> path_;
    const std::string map_;
    std::vector<std::vector<int>> array_;
    int x_start_;
    int y_start_;
    int grid_height_;
    int grid_width_;
    int x_end_;
    int y_end_;
};
//Map.gettile för att få coordinaterna
//tile.gettype för att få typen så att den vet vilken som e nästa

//spara alltid den gamla att den inte far dit
// skanna alla 4 tiles runtom för att kolla nästa lediga tile
// kolla att man får enemins position;

 /*
    std::pair<int,int> moveEnemy(Enemy enemy) {
        //int x = enemy.getx(); //finns int ännu
        //int y = enemy.gety(); // finns int ännu
        current_tile_ = enemy.GetTile();
        //setCurrent(x, y);
        setNext(current_tile_.first, current_tile_.second);
        return move();
    };*/