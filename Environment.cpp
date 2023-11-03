#include <iostream>
#include "Environment.h"
 Environment::Environment(int size_x, int size_y) {
        this->size_x = size_x;
        this->size_y = size_y;

        for (int y = 0; y < size_y; y++) {
            this->map_etat.push_back({});
            for (int x = 0; x < size_x; x++) {
                this->map_etat[y].push_back(Etat::libre);
            }
        }
    }
 std::vector<double> Environment::Deplacement(double pos_x, double pos_y, double pos_w, double left_speed, double right_speed, double temps) {
     std::vector<double> pos;
     double v = 0.0175 * (left_speed + right_speed);
     double w = 0.079 * (left_speed - right_speed);
     pos.push_back(pos_x+v*cos(pos_w)*temps);
     pos.push_back(pos_y+v*sin(pos_w)*temps);
     pos.push_back(pos_w+w*temps);
     return pos;
 }


