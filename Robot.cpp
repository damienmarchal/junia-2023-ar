//
// Created by cload on 16/10/2023.
//

#include "Robot.h"

#include <utility>

Robot::Robot(int x, int y) : Entite(x, y) {
    this->nom = "R";
    this->position[0] = x;
    this->position[1] = y;
    this->orientation = Direction::Nord;

}

void Robot::deplacer(Direction direction) {
    switch (direction) {
        case Direction::Nord:
            position[1]++;
            break;
        case Direction::Est:
            position[0]++;
            break;
        case Direction::Sud:
            position[1]--;
            break;
        case Direction::Ouest:
            position[0]--;
            break;
    }
}


void Robot::arroser() {
    if(this->position[0] == 0 && this->position[1] == 0)
    std::cout << "Arrosage en cours" << std::endl;


}
