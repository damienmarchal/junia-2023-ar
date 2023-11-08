#pragma once
#include "Robot.h"
#include "Environment.h"
#include <iostream>
#include <vector>
class RobotPlanteur :public Robot {
public:
	RobotPlanteur(int id, Environment& map, int case_x, int case_y);
	void planter(Environment& map);
};
