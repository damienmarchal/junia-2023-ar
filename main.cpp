#include <iostream>
#include <vector>

#include "Environment.h"

int main() {
    Environment env(6, 6);
    env.initMap(20,2);
    env.printMap();

    // Permet de faire l'interruption de la fonction

    env.runSimulation();

    return 0;
}

