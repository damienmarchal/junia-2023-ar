//
// Created by cload on 16/10/2023.
//

#include "Robot.h"

#include <utility>

// constructors
Robot::Robot(int x, int y) : Entite(x, y) {
    this->nom = "R";
    this->position[0] = x;
    this->position[1] = y;
    this->orientation = Direction::Nord;
}

// destructors
Robot::~Robot() = default;

// getters
float Robot::getBattery() { return this->battery; }

float Robot::getCapacity() { return this->capacity; }

float Robot::getSpeed() { return this->speed; }

// setters
void Robot::setBattery(float battery) { this->battery = battery; }
void Robot::setCapacity(float capacity) { this->capacity = capacity; }
void Robot::setSpeed(float speed) { this->speed = speed; }

// methods
void Robot::move(Direction direction) {
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

std::vector<std::vector<Entite*>> Robot::getScannerData(Environement env,int range) {
    /*
     * Permet de regarder autour du robot dans un rayon donné
     * @param range: rayon de vision du robot (en nombre de cases) (carré de neuf cases)
     */

    //récupère la carte de l'environement
    std::vector<std::vector<Entite*>> map = env.getMap();
    std::vector<std::vector<Entite*>> data; // tableau de données
    // on récupère la position du robot
    int x = this-> getPosition()[0];
    int y = this-> getPosition()[1];

    // on parcours les cases autour du robot
    switch (range) {
        case 1:
            // Génère une zone de 3x3 autour du robot
            for (int i = 0; i < 3; ++i) {
                data.push_back(std::vector<Entite *>());
                for (int j = 0; j < 3; ++j) {
                    data.at(i).push_back(map[x-1+i][y-1+j]);
                }
            }
            break;
        case 2:
            // Génère une zone de 5x5 autour du robot
            for (int i = 0; i < 5; ++i) {
                data.push_back(std::vector<Entite *>());
                for (int j = 0; j < 5; ++j) {
                    data.at(i).push_back(map[x-2+i][y-2+j]);
                }
            }
            break;
        default:
            std::cout << "Erreur: range invalide" << std::endl;
            break;
    }
    return data;
}


