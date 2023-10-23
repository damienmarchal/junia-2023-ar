
#include "Robot.h"

    Robot::Robot(int id, Environment& map, int pos_x, int pos_y) {
        this->id = id;
        this->pos_x = pos_x;
        this->pos_y = pos_y;
        map.map_etat[pos_y][pos_x] = Etat::robot;
    }

    int Robot::get_id() {
        return this->id;
    }
    int Robot::get_pos_x() {
        return this->pos_x;
    }
    int Robot::get_pos_y() {
        return this->pos_y;
    }
    

    void Robot::deplacer(Environment& map, int dir) {
        if (dir == 0) {
            //d�placement vers le haut 
            if (this->pos_y >= 1 && map.map_etat[this->pos_y - 1][this->pos_x] == Etat::libre) {
                map.map_etat[this->pos_y - 1][this->pos_x] = Etat::robot;
                map.map_etat[this->pos_y][this->pos_x] = Etat::libre;
                this->pos_y = this->pos_y - 1;
            }
            else {
                std::cout << "d�placement impossible" << std::endl;
            }
        }
        else if (dir == 1) {
            //d�placement vers la droite
            if (this->pos_x <= map.size_x - 2 && map.map_etat[this->pos_y][this->pos_x + 1] == Etat::libre) {
                map.map_etat[this->pos_y][this->pos_x + 1] = Etat::robot;
                map.map_etat[this->pos_y][this->pos_x] = Etat::libre;
                this->pos_x = this->pos_x + 1;
            }
            else {
                std::cout << "d�placement impossible" << std::endl;
            }
        }
        else if (dir == 2) {
            //d�placement vers le bas
            if (this->pos_y <= map.size_y - 2 && map.map_etat[this->pos_y + 1][this->pos_x] == Etat::libre) {
                map.map_etat[this->pos_y + 1][this->pos_x] = Etat::robot;
                map.map_etat[this->pos_y][this->pos_x] = Etat::libre;
                this->pos_y = this->pos_y + 1;
            }
            else {
                std::cout << "d�placement impossible" << std::endl;
            }
        }
        else if (dir == 3) {
            //d�placement vers la gauche
            if (this->pos_x >= 1 && map.map_etat[this->pos_y][this->pos_x - 1] == Etat::libre) {
                map.map_etat[this->pos_y][this->pos_x - 1] = Etat::robot;
                map.map_etat[this->pos_y][this->pos_x] = Etat::libre;
                this->pos_x = this->pos_x - 1;
            }
            else {
                std::cout << "d�placement impossible" << std::endl;
            }
        }
        else {
            std::cout << "d�placement non reconnu" << std::endl;
        }

    }



