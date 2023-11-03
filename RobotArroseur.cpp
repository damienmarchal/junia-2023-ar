#include "RobotArroseur.h"
RobotArroseur::RobotArroseur(int id, Environment& map, int case_x, int case_y,int VolumeEau) : Robot(id, map, case_x, case_y) {
	this->VolumeEau = VolumeEau;
	this->VolumeMax = VolumeEau;
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
void RobotArroseur::remplirEau(int volumeEau) {
	if (VolumeEau > 0 && VolumeEau <= this->VolumeMax) {
		this->VolumeEau = volumeEau;
	}
	else {
		std::cout << "remplissage impossible" << std::endl;
	}
}