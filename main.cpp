#include <cmath>
#include <iostream>
#include <vector>

#include "Environment.h"


int main() {
    Environment env(6, 6);
    env.initMap(10,1,0,0);
    env.printMap();

    env.runSimulation(); // Lance la simulation

    return 0;
}


