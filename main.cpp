#include "Environment.h"
#include "afficheur.h"
#include "Etat.h"
#include "Robot.h"
#include "RobotPlanteur.h"
#include "RobotArroseur.h"

int main(int argc, char** argv) {
    int n = 5;
    Environment* map = new Environment(n, n);
    RobotPlanteur* robot1 = new RobotPlanteur(1, *map, 0, 0);
    RobotArroseur* robot2 = new RobotArroseur(1, *map, 0, 1, 10);
    //std::cout << robot2->get_VolumeEau() << std::endl;
    std::cout << robot2->get_index_x() << std::endl;
    //std::cout << *map << std::endl;
    //for (int i = 0; i < (n * n) - 1; i++) {
    //    robot1->planter(*map);
    //}
    std::cout << *map << std::endl;

}