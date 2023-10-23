#pragma once
#include "Robot.h"
#include "Environment.h"
#include <iostream>
#include <vector>
class RobotPlanteur :Robot {
public:
	RobotPlanteur(int id, Environment& map, int pos_x, int pos_y);
	void planter(Environment& map);
};
