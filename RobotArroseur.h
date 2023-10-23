#pragma once
#include "Robot.h"
#include "Environment.h"
#include <iostream>
#include <vector>

class RobotArroseur :Robot {
public:
	int VolumeEau;
	RobotArroseur(int id, Environment& map, int pos_x, int pos_y, int VolumeEau);
	void arroser();
	int get_VolumeEau();
};
