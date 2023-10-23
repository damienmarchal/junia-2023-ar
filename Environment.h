#pragma once

#include<vector>
#include"Etat.h>"

class Environment {
public:
    int size_x;
    int size_y;
    std::vector<std::vector<Etat>> map_etat;

    Environment(int size_x, int size_y);
};


