#include <iostream>
#include <vector>


enum class Etat {
    libre, robot, arbre, mur
};

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
    case Etat::mur:
        s << "mur";
        break;
    };
    return s;
}

class Environment {
public:
    int longueur;
    int largeur;
    std::vector<std::vector<Etat>> map_etat;

    Environment(int longueur, int largeur) {
        this->longueur = longueur;
        this->largeur = largeur;

        for (int y = 0; y < largeur; y++) {
            this->map_etat.push_back({});
            for (int x = 0; x < longueur; x++) {
                this->map_etat[y].push_back(Etat::libre);
            }
        }
    }
};

std::ostream& operator<<(std::ostream& s, Environment& map) {
    for (int y = 0; y < map.largeur; y++) {
        for (int x = 0; x < map.longueur; x++) {
            if(map.map_etat[y][x]==Etat::libre)
                s << " " << "  ";
            else if(map.map_etat[y][x]==Etat::robot)
                s << "x" << "  ";
            else if(map.map_etat[y][x]==Etat::arbre)
                s << "#" << "  ";
            else 
                s << "|" << "  ";

        }
        s << std::endl;
    };
    return s;
}

int main(int argc, char** argv) {
    Environment* map = new Environment(5, 5);
    map->map_etat[0][0]=Etat::robot;
    map->map_etat[1][1]=Etat::mur;
    map->map_etat[2][1]=Etat::mur;
    map->map_etat[3][1]=Etat::mur;
    map->map_etat[3][4]=Etat::mur;
    map->map_etat[2][4]=Etat::mur;
    map->map_etat[2][3]=Etat::arbre;

    std::cout << *map << std::endl;
}
