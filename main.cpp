#include <cmath>
#include <iostream>
#include <vector>

#include "Environment.h"
#include <iostream>
#include <cmath>

int main() {
    Environment env(7, 7);
    env.initMap(10,0,1,0);
    env.printMap();

    env.runSimulation(); // Lance la simulation

    return 0;
}


