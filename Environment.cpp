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


