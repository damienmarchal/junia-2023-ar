
#include "Robot.h"


    Robot::Robot(int id, Environment& map, int case_x, int case_y) {
        this->id = id;
        this->case_x = case_x;
        this->case_y = case_y;
        this->pos_x = 1.0*case_x;
        this->pos_y = 1.0*case_y;
        this->pos_w = 0;
        map.map_etat[pos_y][pos_x] = Etat::robot;
    }

    int Robot::get_id() {
        return this->id;
    }
    double Robot::get_pos_x() {
        return this->pos_x;
    }
    double Robot::get_pos_y() {
        return this->pos_y;
    }
    int Robot::get_case_x() {
        return this->case_x;
    }
    int Robot::get_case_y() {
        return this->case_y;
    }
    

    void Robot::set_wheel_speed(Environment& map, double left_speed, double right_speed) {
        std::vector<double> point = map.Deplacement(this->pos_x, this->pos_y, this->pos_w, left_speed, right_speed, 0.1);
        map.map_etat[this->case_y][this->case_x] = Etat::libre;
        this->pos_x = point[0];
        this->pos_y = point[1];
        this->pos_w = point[2];
        this->case_x = (int) point[0];
        this->case_y = (int)point[1];
        map.map_etat[this->case_y][this->case_x] = Etat::robot;

    }



