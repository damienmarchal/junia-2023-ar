#include <cmath>
#include <iostream>
#include <vector>

#include "Environment.h"


int main() {
    Environment env(6, 6);
    env.initMap(20,2);
    env.printMap();

    env.runSimulation(); // Lance la simulation

    return 0;
}


