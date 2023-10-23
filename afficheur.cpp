
#include"Etat.h"

std::ostream& operator<<(std::ostream& s, Etat& e) {
    switch (e) {
    case Etat::libre:
        s << "libre";
        break;
    case Etat::robot:
        s << "robot";
        break;
    case Etat::arbre:
        s << "arbre";
        break;
    case Etat::obstacle:
        s << " mur ";
        break;
    };
    return s;
}

std::ostream& operator<<(std::ostream& s, Environment& map) {
    for (int y = 0; y < map.size_y; y++) {
        for (int x = 0; x < map.size_x; x++) {
            s << map.map_etat[y][x] << " | ";

        }
        s << std::endl;
    };
    return s;
}

