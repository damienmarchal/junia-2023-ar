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
    enum class ActualManeuver { Mouvement,Turn, SpecialAction, Idle };
    ActualManeuver actualManeuver;
    enum class Direction { Nord,Est,Sud,Ouest };
    Direction direction;
    float orientation; // angle en degré
    float battery, batteryMax; // niveau de batterie
    float capacity, capacityMax ; // capacité de stockage
    float speed, speedMax; // vitesse de déplacement
    float speedWeelRight, speedWeelLeft; // vitesse des roues
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
    float getSpeedWeelRight();
    float getSpeedWeelLeft();


    // Setters
    void setSpeedWeelRight(float speedWeelRight);
    void setSpeedWeelLeft(float speedWeelLeft);
    void setDesiredPose(float x, float y, float orientation);
    void setOrientation(float orientation);
    virtual void setBattery(float battery);
    virtual void setCapacity(float capacity);
    virtual void setSpeed(float speed);
    void setActualManeuver(ActualManeuver actualManeuver);

    // Methods
    void move(Direction direction);
    void move(float speed);
    void move();
    void cinematicMove();
    void turn();
    void turn(float angle);
    std::vector<std::vector<Entite*>> getScannerData(Environment &env, int range);
    virtual void action(Environment &env);
    virtual void priseDecision(Environment &env);
    void Update(Environment &env);
    bool isFree();
    void scan(Environment &env, int range);
    float distanceEntreRobotEtObjet( float xObjet, float yObjet);

    // static methods
    static float angle(float x1, float y1, float x2, float y2);
    static float angleRobotArbre(float xRobot, float yRobot, float xArbre, float yArbre, float orientationRobot);
};


#endif //COURSC_ROBOT_H
