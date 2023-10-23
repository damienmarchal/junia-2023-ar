//
// Created by cload on 16/10/2023.
//

#ifndef COURSC_ROBOT_H
#define COURSC_ROBOT_H

#include <iostream>
#include <vector>

#include "../Entite.h"
#include "../Environement.h"

class Robot : public Entite {
public:
    enum class Direction { Nord,Est,Sud,Ouest };
    Direction orientation;
    float battery, batteryMax;
    float capacity, capacityMax ;
    float speed, speedMax;

    // constructeur
    Robot(int x, int y);

    // Destructuer
    ~Robot();

    // Getters
    float getBattery();
    float getCapacity();
    float getSpeed();

    // Setters
    virtual void setBattery(float battery);
    virtual void setCapacity(float capacity);
    virtual void setSpeed(float speed);

    // Methods
    void move(Direction direction);
    std::vector<std::vector<Entite*>> getScannerData(Environement env, int range);

};


#endif //COURSC_ROBOT_H
