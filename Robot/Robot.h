//
// Created by cload on 16/10/2023.
//

#ifndef COURSC_ROBOT_H
#define COURSC_ROBOT_H

#include <iostream>
#include <vector>

#include "../Entite.h"
#include "../Environment.h"

class Robot : public Entite {
public:
// Attributs
    enum class ActualManeuver { Mouvement, SpecialAction, Idle };
    ActualManeuver actualManeuver;
    enum class Direction { Nord,Est,Sud,Ouest };
    Direction direction;
    float orientation; // angle en degré
    float battery, batteryMax; // niveau de batterie
    float capacity, capacityMax ; // capacité de stockage
    float speed, speedMax; // vitesse de déplacement
    std::vector<std::vector<Entite*>> localMap; // carte locale du robot
    float diseriedPose[3]; // pose désirée du robot (x,y,orientation)


    // constructeur
    Robot(int x, int y);

    // Destructuer
    ~Robot();

    // Getters
    float* getDesiredPose();
    float getOrientation();
    float getBattery();
    float getCapacity();
    float getSpeed();
    ActualManeuver getActualManeuver();
    Direction getDirection();
    std::vector<std::vector<Entite*>> getLocalMap();


    // Setters
    void setDesiredPose(float x, float y, float orientation);
    void setOrientation(float orientation);
    virtual void setBattery(float battery);
    virtual void setCapacity(float capacity);
    virtual void setSpeed(float speed);
    void setActualManeuver(ActualManeuver actualManeuver);

    // Methods
    void move(Direction direction);
    void turn();
    std::vector<std::vector<Entite*>> getScannerData(Environment &env, int range);
    virtual void action(Environment &env);
    virtual void priseDecision(Environment &env);
    void Update(Environment &env);
    bool isFree();
};


#endif //COURSC_ROBOT_H
