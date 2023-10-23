#include "RobotArroseur.h"
RobotArroseur::RobotArroseur(int id, Environment& map, int pos_x, int pos_y,int VolumeEau) : Robot(id, map, pos_x, pos_y) {
	this->VolumeEau = VolumeEau;
}
void RobotArroseur::arroser() {
	if (this->VolumeEau > 0) {
		this->VolumeEau--;
	}
	else {
		std::cout << "reserve d'eau vide" << std::endl;
	}

}
int RobotArroseur::get_VolumeEau() {
	return this->VolumeEau;
}