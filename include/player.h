#ifndef PLAYER_H
#define PLAYER_H

#include <board.h>
#include <ship.h>
#include <string>

class Player {
public:
    Player(std::string name) : name(name) {}

    std::string GetName() {
        return this->name;
    }

    bool IsPlayerAlive() {
        return !board.AllShipsSunk();
    }
    bool PlayNextMove(int x, int y){
        if(board.EvaluateShot(x,y)) {
            return true;
        } else {
            std::cout << "Not a Valid Shot" << std::endl;
            return false;
        }
    }
    bool AddShip(int start_x, int start_y, int end_x, int end_y, Orientation orientation) {
        auto ship = Ship(start_x, start_y, end_x, end_y, orientation);
        bool success = board.AddShip(ship);
        if(success) {
            std::cout << "Ship Added!" << std::endl;
            ship_count++;
        } else {
            std::cout << "Unable to Add Ship" << std::endl;
        }
        return success;
    }

    bool AddShip(int start_x, int start_y, Orientation orientation, int length) {
        auto ship = Ship(start_x, start_y, orientation, length);
        bool success = board.AddShip(ship);
        if(success) {
            std::cout << "Ship Added!" << std::endl;
            ship_count++;
        } else {
            std::cout << "Unable to Add Ship" << std::endl;
        }
        return success;
    }

    int GetShipCount(){
        return ship_count;
    }

    void PrintGameBoard() {
        board.DisplayBoard();
    }

    void PrintShipMap(){
        board.ShowMap();
    }
private:
    int ship_count=0;
    Board board;
    std::string name;
};

#endif