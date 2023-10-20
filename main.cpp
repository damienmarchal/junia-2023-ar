#include <iostream>
#include <vector>
#include "Environement.h"

int main() {
    Environement env(5, 5);
    env.initMap(10,2);
    env.printMap();
    return 0;
}
