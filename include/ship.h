#ifndef SHIP_H
#define SHIP_H

#include <cmath>
#include <algorithm>
#include <types.h>

class Ship {
public:
    Ship(int start_x, int start_y, int end_x, int end_y, Orientation orientation) : 
    start_x(start_x), start_y(start_y), end_x(end_x), end_y(end_y),
    orientation(orientation){
        int delta_x = std::abs(start_x - end_x);
        int delta_y = std::abs(start_y - end_y);
        ship_length = std::max(delta_x,delta_y) + 1;
    }

    bool IsAlive(){
        return alive;
    }

    int GetStartX() {
        return start_x;
    }

    int GetStartY() {
        return start_y;
    }

    int GetEndX() {
        return end_x;
    }

    int GetEndY() {
        return end_y;
    }
    
    bool EvaluateShot(int attempt_x, int attempt_y) {
        bool landed_shot = false;
        if(attempt_x == start_x) {
            if(attempt_y >= start_y && attempt_y <= end_y) {
                landed_shot = true;
            }
        } 
        else if(attempt_y == start_y) {
            if(attempt_x >= start_x && attempt_x <= end_x){
                landed_shot = true;
            }
        } 
        if (landed_shot) {
            RegisterLandedShot();
        }
        return landed_shot;
    }

    void RegisterLandedShot(){
        strike_count++;
        if(ship_length==strike_count){
            std::cout << "ship sunk" << std::endl;
            alive=false;
        }
    }

    Orientation GetOrientation(){
        return orientation;
    }

private:
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    int strike_count{0};
    int ship_length;
    bool alive{true};
    Orientation orientation;
};

#endif