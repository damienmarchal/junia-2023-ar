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
    while (robot1->pos_x<2){
        robot1->set_wheel_speed(*map, 1.0, 1.0);
    }

    while (robot1->pos_w < 3.14) {
        robot1->set_wheel_speed(*map, 1.0, -1.0);
    }
        while (robot1->pos_x<2){
        robot1->set_wheel_speed(*map, 1.0, 1.0);
    }

    std::cout << *map << std::endl;
    std::cout << robot1->pos_w << std::endl;


}