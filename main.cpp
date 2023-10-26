#include <iostream>
#include <vector>

#include "Environment.h"

int main() {
    Environment env(6, 6);
    env.initMap(10,2);
    env.printMap();

    // Permet de faire l'interruption de la fonction


    while (env.getRunning()) // tant que l'environnement n'est pas stable
    {
        env.updateMap();
        env.printMap();
    }

    return 0;
}

