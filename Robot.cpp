
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
    void Robot::planter(Environment& map) {
        //par défaut après avoir planter le robot se décale sur la droite
        if (this->pos_x <= map.size_x - 2 && map.map_etat[this->pos_y][this->pos_x + 1] == Etat::libre) {
            map.map_etat[this->pos_y][this->pos_x] = Etat::arbre;
            map.map_etat[this->pos_y][this->pos_x + 1] = Etat::robot;
            this->pos_x = this->pos_x + 1;
        }
        //si ce c'est pas possible, il monte
        else if (this->pos_y >= 1 && map.map_etat[this->pos_y - 1][this->pos_x] == Etat::libre) {
            map.map_etat[this->pos_y][this->pos_x] = Etat::arbre;
            map.map_etat[this->pos_y - 1][this->pos_x] = Etat::robot;
            this->pos_y = this->pos_y - 1;
        }
        //si ce n'est pas possible, il va vers la gauche
        else if (this->pos_x >= 1 && map.map_etat[this->pos_y][this->pos_x - 1] == Etat::libre) {
            map.map_etat[this->pos_y][this->pos_x] = Etat::arbre;
            map.map_etat[this->pos_y][this->pos_x - 1] = Etat::robot;
            this->pos_x = this->pos_x - 1;
        }
        //si ce n'est pas possible, il descent
        else if (this->pos_y <= map.size_y - 2 && map.map_etat[this->pos_y + 1][this->pos_x] == Etat::libre) {
            map.map_etat[this->pos_y][this->pos_x] = Etat::arbre;
            map.map_etat[this->pos_y + 1][this->pos_x] = Etat::robot;
            this->pos_y = this->pos_y + 1;
        }
        //si aucun de ces mouvement n'est possible alors le robot ne peut pas planter
        else {
            std::cout << "impossible de planter ici" << std::endl;
        }

    }
    void Robot::deplacer(Environment& map, int dir) {
        if (dir == 0) {
            //déplacement vers le haut 
            if (this->pos_y >= 1 && map.map_etat[this->pos_y - 1][this->pos_x] == Etat::libre) {
                map.map_etat[this->pos_y - 1][this->pos_x] = Etat::robot;
                map.map_etat[this->pos_y][this->pos_x] = Etat::libre;
                this->pos_y = this->pos_y - 1;
            }
            else {
                std::cout << "déplacement impossible" << std::endl;
            }
        }
        else if (dir == 1) {
            //déplacement vers la droite
            if (this->pos_x <= map.size_x - 2 && map.map_etat[this->pos_y][this->pos_x + 1] == Etat::libre) {
                map.map_etat[this->pos_y][this->pos_x + 1] = Etat::robot;
                map.map_etat[this->pos_y][this->pos_x] = Etat::libre;
                this->pos_x = this->pos_x + 1;
            }
            else {
                std::cout << "déplacement impossible" << std::endl;
            }
        }
        else if (dir == 2) {
            //déplacement vers le bas
            if (this->pos_y <= map.size_y - 2 && map.map_etat[this->pos_y + 1][this->pos_x] == Etat::libre) {
                map.map_etat[this->pos_y + 1][this->pos_x] = Etat::robot;
                map.map_etat[this->pos_y][this->pos_x] = Etat::libre;
                this->pos_y = this->pos_y + 1;
            }
            else {
                std::cout << "déplacement impossible" << std::endl;
            }
        }
        else if (dir == 3) {
            //déplacement vers la gauche
            if (this->pos_x >= 1 && map.map_etat[this->pos_y][this->pos_x - 1] == Etat::libre) {
                map.map_etat[this->pos_y][this->pos_x - 1] = Etat::robot;
                map.map_etat[this->pos_y][this->pos_x] = Etat::libre;
                this->pos_x = this->pos_x - 1;
            }
            else {
                std::cout << "déplacement impossible" << std::endl;
            }
        }
        else {
            std::cout << "déplacement non reconnu" << std::endl;
        }

    }



