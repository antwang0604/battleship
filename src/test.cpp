
#include <vector>
#include <iostream>
#include <board.h>
#include <player.h>
#include <types.h>

std::vector<int> GenerateShipCoord(int start_x, int start_y, int orientation) {
    std::vector<int> ship_coords;
    ship_coords.push_back(start_x);
    ship_coords.push_back(start_y);
    if(orientation==1) {
        ship_coords.push_back(start_x+2);
        ship_coords.push_back(start_y);
    } else {
        ship_coords.push_back(start_x);
        ship_coords.push_back(start_y+2);
    }
    return ship_coords;
}

Orientation ConvertOrientation(int input){
    Orientation result = Orientation::unknown;
    if(input==1){
        result = Orientation::horizontal;
    } else if (input == 2) {
        result = Orientation::vertical;
    }
    return result;
}

void PromptNewShip(Player& player) {
    int ship_x;
    int ship_y;
    int orientation;

    std::cout << player.GetName() << ", Please place your first ship. Choose the Starting X" << std::endl;
    std::cin >> ship_x;
    std::cout << "Choose the Starting Y" << std::endl;
    std::cin >> ship_y;
    std::cout << "Is the ship horizontal (1) or vertical (2)?" << std::endl;
    std::cin >> orientation;
    auto ship_coord = GenerateShipCoord(ship_x,ship_y,orientation);
    player.AddShip(ship_coord[0],ship_coord[1],ship_coord[2],ship_coord[3], ConvertOrientation(orientation));
    player.PrintShipMap();
}

int main(){
    Player player1("Player1");

    

    while(player1.ship_count<3){
        PromptNewShip(player1);
    }

    std::cout << "Alive? " << player1.IsPlayerAlive() << std::endl;
    player1.PlayNextMove(0,0);
    player1.PlayNextMove(0,1);
    player1.PlayNextMove(0,1);
    player1.PlayNextMove(0,2);
    player1.PlayNextMove(0,3);
    player1.PlayNextMove(0,4);
    player1.PlayNextMove(0,5);
    std::cout << "Alive? " << player1.IsPlayerAlive() << std::endl;
    player1.PlayNextMove(2,3);
    player1.PlayNextMove(3,3);
    player1.PlayNextMove(4,3);
    std::cout << "Alive? " << player1.IsPlayerAlive() << std::endl;
    return 0;
}

