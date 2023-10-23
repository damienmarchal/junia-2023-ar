#include <iostream>
#include <vector>
#include "Environment.h"

int main() {
    Environment env(5, 5);
    env.initMap(10,2);
    env.printMap();

    return 0;
}
