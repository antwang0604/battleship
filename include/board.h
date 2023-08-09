#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <types.h>
#include <iostream>
#include <ship.h>


class Board {
public:

    Board():
        board_size(5),
        max_ship_count(3),
        board(board_size,std::vector<CellStatus>(board_size,CellStatus::unknown)),
        ship_map(board_size,std::vector<int>(board_size,-1)){
        };

    void ShowMap() {
        for(auto curr_row:ship_map){
            std::cout << "|";
            for(auto curr_cell:curr_row){
                if(curr_cell == -1){
                    std::cout << "  |";
                } else{
                    std::cout << " " << curr_cell << "|";
                }
            }
            std::cout << std::endl;
        }
    }

    void DisplayBoard(){
        for(auto curr_row:board){
            std::cout << "|";
            for(auto curr_cell:curr_row){
                if(curr_cell == CellStatus::unknown) {
                    std::cout << "  |";
                }
                else if(curr_cell == CellStatus::hit) {
                    std::cout << " □|";
                }
                else if(curr_cell == CellStatus::sink) {
                    std::cout << " ■|";
                }
                else if(curr_cell == CellStatus::miss) {
                    std::cout << " X|";
                }
            }
            std::cout << std::endl;
        }
    }
    bool AddShip(Ship& ship) {
        if(ship_ids.size()==max_ship_count) {
            return false;
        }

        
        int start_x = ship.GetStartX();
        int start_y = ship.GetStartY();
        std::vector<std::pair<int,int>> coords;

        if(ship.GetOrientation() == Orientation::horizontal){
            for(int i=0;i<3;i++){
                coords.push_back(std::make_pair(start_x+i,start_y));
            }
        } 
        else if(ship.GetOrientation() == Orientation::vertical){
            for(int i=0;i<3;i++){
                coords.push_back(std::make_pair(start_x,start_y+i));
            }
        } else {
            return false;
        }

        int ship_id = ship_ids.size();
        bool ShipPlaceable = true;

        for(auto coord : coords) {
            int x = coord.first;
            int y = coord.second;
            if(x<0 || y<0 || x>=board_size || y>=board_size){
                // if out of bounds
                ShipPlaceable = false;
            } else {
                if(ship_map[x][y] != -1) {
                    // or spot is already taken by another ship
                    ShipPlaceable = false;
                }
            }
        }

        if(ShipPlaceable) {
            ship_ids.push_back(ship);
            for(auto coord : coords) {
                ship_map[coord.first][coord.second] = ship_id;
            }
            return true;
        } else {
            return false;
        }
    }

    void HandleShipSunk(int x, int y, int ship_id) {
        int start_x = ship_ids[ship_id].GetStartX();
        int start_y = ship_ids[ship_id].GetStartY();
        int end_x = ship_ids[ship_id].GetEndX();
        int end_y = ship_ids[ship_id].GetEndY();
        if(start_x == end_x) {
            for(int i=start_y; i<=end_y; i++) {
                board[start_x][i] = CellStatus::sink;
            }
        } else {
            for(int i=start_x; i<=end_x; i++) {
                board[i][start_y] = CellStatus::sink;
            }
        }
    }

    void FireAway(int x, int y) {
        // if lands on nothing
        if(ship_map[x][y] == -1){
            board[x][y] = CellStatus::miss;
        }
        // if lands on empty land
        else{
            int ship_id = ship_map[x][y];
            ship_ids[ship_id].RegisterLandedShot();
            if(ship_ids[ship_id].IsAlive()){
                board[x][y] = CellStatus::hit;
            } else {
                HandleShipSunk(x,y,ship_id);
            }
        }
    }

    bool EvaluateShot(int x, int y) {
        bool IsValidShot = false;
        if(x<0 || y<0 || x >= board_size || y >= board_size){
            IsValidShot = false;
        } else {
            if (board[x][y] == CellStatus::unknown) {
                IsValidShot = true;
            }
        }

        if(IsValidShot){
            FireAway(x,y);
        }

        return IsValidShot;
    }

    bool AllShipsSunk() {
        bool result = true;
        for (auto n:ship_ids) {
            if(n.IsAlive()==true){
                result = false;
                break;
            }
        }
        return result;
    }
    

private:
    int board_size;
    int max_ship_count;
    std::vector<Ship> ship_ids; // ship ID corresponding to the actual ship object
    std::vector<std::vector<CellStatus>> board; // represents the display status of each cell
    std::vector<std::vector<int>> ship_map; // represents the location of each ship, using ship ID
};


#endif