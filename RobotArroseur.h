#pragma once
#include "Robot.h"
#include "Environment.h"
#include <iostream>
#include <vector>

class RobotArroseur :public Robot {
public:
	int VolumeEau;
	int VolumeMax;
	RobotArroseur(int id, Environment& map, int case_x, int case_y, int VolumeEau);
	void arroser();
	int get_VolumeEau();
	void remplirEau(int volumeEau);
};
