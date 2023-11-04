//
// Created by cload on 16/10/2023.
//

#include <utility>

#include "Robot.h"
#include "../Arbre.h"

// constructors
Robot::Robot(int x, int y) : Entite(x, y) {
    this->nom = "R";
    this->position[0] = x;
    this->position[1] = y;
    this->direction = Direction::Nord;
    this->orientation = 0;
    this->actualManeuver = ActualManeuver::Idle;
    this->battery = 100;
    this->batteryMax = 100;
    this->capacity = 10;
    this->capacityMax = 10;
    this->speed = 10;
    this->speedMax = 10;
    this->speedWeelRight = 0;
    this->speedWeelLeft = 0;
    this->diseriedPose[0] = this->diseriedPose[1] =this->diseriedPose[2] = 0;
    this->pose[0] =(float)x;
    this->pose[1] =(float)y;
    this->pose[2] =0;
    this->positionObjectifEnLocal[0] = 0;
    this->positionObjectifEnLocal[1] = 0;
}

// destructors
Robot::~Robot() = default;

// getters
float * Robot::getPose() { return this->pose; }
float *Robot::getDesiredPose() { return new float[3]{static_cast<float>(this->diseriedPose[0]), static_cast<float>(this->diseriedPose[1]), this->diseriedPose[2]}; }
float Robot::getOrientation() { return this->orientation; }
float Robot::getBattery() { return this->battery; }
float Robot::getCapacity() { return this->capacity; }
float Robot::getSpeed() { return this->speed; }
std::vector<std::vector<Entite *>> Robot::getLocalMap() { return this->localMap; }
Robot::Direction Robot::getDirection() { return this->direction; }
Robot::ActualManeuver Robot::getActualManeuver() { return this->actualManeuver; }
float Robot::getSpeedWeelRight() { return this->speedWeelRight; }
float Robot::getSpeedWeelLeft() { return this->speedWeelLeft; }
int *Robot::getPositionObjectifEnLocal() { return this->positionObjectifEnLocal; }

// setters
void Robot::setActualManeuver(Robot::ActualManeuver actualManeuver) { this->actualManeuver = actualManeuver; }
void Robot::setOrientation(float orientation) { this->orientation = orientation; }
void Robot::setBattery(float battery) { this->battery = battery; }
void Robot::setCapacity(float capacity) { this->capacity = capacity; }
void Robot::setSpeed(float speed) { this->speed = speed; }
void Robot::setSpeedWeelRight(float speedWeelRight) { this->speedWeelRight = speedWeelRight; }
void Robot::setSpeedWeelLeft(float speedWeelLeft) { this->speedWeelLeft = speedWeelLeft; }
void Robot::setDesiredPose(float x, float y, float orientation) {
    this->diseriedPose[0] = x;
    this->diseriedPose[1] = y;
    this->diseriedPose[2] = orientation;
}
void Robot::setPositionObjectifEnLocal(int x, int y) {
    this->positionObjectifEnLocal[0] = x;
    this->positionObjectifEnLocal[1] = y;
}

void Robot::setPose(float x, float y, float theta) {
    this->pose[0] = x;
    this->pose[1] = y;
    this->pose[2] = theta;
}

// methods
void Robot::move(float speed) {
    /*
     * Permet de faire bouger le robot avec une vitesse donnée
     */
    this->setSpeedWeelLeft(speed);
    this->setSpeedWeelRight(speed);
}
void Robot::move() {
    /*
     * Permet de faire bouger le robot avec une vitesse donnée pour chaque roue
     */
    this->setSpeedWeelLeft(this->getSpeed());
    this->setSpeedWeelRight(this->getSpeed());
}
void Robot::move(Direction direction) {
    switch (direction) {
        case Direction::Nord:
            position[1]++;
            break;
        case Direction::Est:
            position[0]++;
            break;
        case Direction::Sud:
            position[1]--;
            break;
        case Direction::Ouest:
            position[0]--;
            break;
    }
}

void Robot::scan(Environment &env, int range) {
    /*
     * Permet de scanner l'environnement
     * @param env: environnement à scanner
     * @param range: rayon de vision du robot (en nombre de cases) (carré de neuf cases)
     */
    this->localMap = this->getScannerData(env, range);
}

std::vector<std::vector<Entite*>> Robot::getScannerData(Environment &env, int range) {
    /*
     * Permet de regarder autour du robot dans un rayon donné
     * @param range: rayon de vision du robot (en nombre de cases) (carré de neuf cases)
     */

    //récupère la carte de l'environement
    std::vector<std::vector<Entite*>> map = env.getMap();
    std::vector<std::vector<Entite*>> data; // tableau de données
    // on récupère la position du robot
    int x = this-> getPosition()[0];
    int y = this-> getPosition()[1];

    // on parcours les cases autour du robot
    switch (range) {
        case 1:
            // Génère une zone de 3x3 autour du robot
            for (int i = 0; i < 3; ++i) {
                data.push_back(std::vector<Entite *>());
                for (int j = 0; j < 3; ++j) {
                    data.at(i).push_back(map[x-1+i][y-1+j]);
                }
            }
            break;
        case 2:
            // Génère une zone de 5x5 autour du robot
            for (int i = 0; i < 5; ++i) {
                data.push_back(std::vector<Entite *>());
                for (int j = 0; j < 5; ++j) {
                    if(x-2+1<0||y-2+j<0||x+2+i>map.size()||y+2+j>map.size()){ // Si on est hors map
                        data.at(i).push_back(new Entite(x-2+i,y-2+j));
                    }
                    else // Si on est dans la carte
                    data.at(i).push_back(map[x-2+i][y-2+j]); // On ajoute la case à la carte
                }
            }
            break;
        default:
            std::cout << "Erreur: range invalide" << std::endl;
            break;
    }
    return data;
}

void Robot::action(Environment &env) {
    /*
     * Permet de faire agir le robot
     * @param env: environement dans lequel le robot se trouve
     */

    // récupère les données du scanner
    std::vector<std::vector<Entite*>> data = this->getScannerData(env, 1);

    // on parcours les cases autour du robot
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[i].size(); ++j) {
            // on regarde si la case est un arbre
            if (data[i][j]->getNom() == "A") {
                // on caste la case en arbre
                Arbre *arbre = dynamic_cast<Arbre *>(data[i][j]);
                // on regarde si l'arbre est planté
                if (arbre->getStatutArbre() == Arbre::Etat::planted) {
                    // on regarde si le robot a de l'eau
                    if (this->getCapacity() > 0) {
                        // on arrose l'arbre
                        arbre->arroser();
                        // on enlève de l'eau au robot
                        this->setCapacity(this->getCapacity() - 1);
                    }
                }
            }
        }
    }
}

void Robot::turn() { this->direction = (Direction) ((int) this->direction + 1); }

void Robot::turn(float angle) {
    /*
     * Permet de faire tourner le robot
     * @param angle: angle de rotation en degré
     */
    float margin = 0.1; // marge d'erreur

    // Vérifie si l'angle est bon avec une marge d'erreur
    if (angle < margin && angle > -margin) { // Si l'angle est bon
        this->setActualManeuver(Robot::ActualManeuver::Mouvement); // On met le robot en mode Idle
    }
    else{
        float precision= 4; // précision de la rotation plus elle est grande plus la rotation est rapide mais moins précise
        // On fait tourner le robot
        if (angle > 0) { // Si l'angle est positif
            this->setSpeedWeelRight(precision);
            this->setSpeedWeelLeft(-precision);
        } else { // Si l'angle est négatif
            this->setSpeedWeelRight(-precision);
            this->setSpeedWeelLeft(precision);
        }
    }
}
void Robot::priseDecision(Environment &env) {
    /*
     * Permet de mettre en place la stratégie de déplacement
     */
    std::cerr << "C'est la méthode de la classe mère" << std::endl;
    return;
}

void Robot::calculNewPose() {
    /*
     * Permet de calculer la nouvelle pose du robot de manière cinématique
     */
/*    // TODO : Trouver un moyen de mettre en place des intégrales
    float rayonRoue =0.03; // rayon de la roue
    float distanceEntraxe = 0.25; // distance entre les deux roues

    float termeG = (rayonRoue / 2) * (this->getSpeedWeelLeft() + this->getSpeedWeelRight());

    float termeD = (rayonRoue / distanceEntraxe) * (this->getSpeedWeelRight() - this->getSpeedWeelLeft());

    float newX = this->getPose()[0] + (termeG * std::cos(termeD)); // les deux termes de la multiplication doivent être intégrés
    float newY = this->getPose()[1] + (termeG * std::sin(termeD)); // les deux termes de la multiplication doivent être intégrés
    float newOrientation = this->getPose()[2] + (termeD); // le terme de la multiplication doit être intégré
*/

    float delta_t = 0.1; // C'est le temps entre chaque calcul de pose

    float v_left = this->getSpeedWeelLeft();
    float v_right = this->getSpeedWeelRight();

    float newX = this->getPose()[0];
    float newY = this->getPose()[1];
    float newTheta = this->getPose()[2];

    // Calculate linear and angular velocity of the robot
    float v = (v_left + v_right) / 2.0;
    float omega = (v_right - v_left) / this->entraxe;

    // Update the pose of the robot
    newX += v * std::cos(newTheta) * delta_t;
    newY += v * std::sin(newTheta) * delta_t;
    newTheta += omega * delta_t;

    this->setPose(newX, newY, newTheta);

}


void Robot::Update(Environment &env) {
    /*
     * Permet de mettre à jour les données du robot
     */
    // TODO : mettre à jour les données du robot
    // Nouvelle carte
    this->localMap = this->getScannerData(env, 1);
    // Nouvelle pose
    this->calculNewPose();
    // Nouvelle direction
    // Nouvelle batterie
    // Nouvelle capacité
    // Nouvelle vitesse
    return;
}

bool Robot::isFree() {
    switch (this->getDirection()) {
        case Direction::Nord:
            return this->getLocalMap()[this->getPosition()[0] - 1][this->getPosition()[1]]->getNom() == "_";
        case Direction::Est:
            return this->getLocalMap()[this->getPosition()[0]][this->getPosition()[1] + 1]->getNom() == "_";
        case Direction::Sud:
            return this->getLocalMap()[this->getPosition()[0] + 1][this->getPosition()[1]]->getNom() == "_";
        case Direction::Ouest:
            return this->getLocalMap()[this->getPosition()[0]][this->getPosition()[1] - 1]->getNom() == "_";
    }
    return false;
}


// calcul de l'angle entre un robot et un arbre
float Robot::angleRobotArbre(float xRobot, float yRobot, float xArbre, float yArbre, float orientationRobot) {
    float angleRobotArbre = Robot::angle(xRobot,yRobot,xArbre,yArbre);
    float angleRobotArbreRobot = angleRobotArbre - orientationRobot;
    return angleRobotArbreRobot;
}

void Robot::cinematicMove() {
    /*
     * Permet de faire bouger le robot en se basant avec une pseudo cinématique
     * TODO : faire une vraie cinématique inverse (dans une autre méthode)
     */

    // on récupère la pose du robot
    auto x = (float)this->getPosition()[0];
    auto y = (float)this->getPosition()[1];

    // on récupère la position désirée du robot
    float xD = this->getDesiredPose()[0];
    float yD = this->getDesiredPose()[1];

    float margin = 0.1; // marge d'erreur pour la pose
    /*
     * La méthode fonctionne de la manière suivante :
     * tourne jusqu'a être dans la bonne direction
     * avance jusqu'a être à la bonne distance
     */
    // On vérifie si on est dans la bonne direction
    if(Robot::angleRobotArbre(x,y,xD,yD,this->getOrientation())>margin&&this->getActualManeuver() == Robot::ActualManeuver::Mouvement)
        this->setActualManeuver(Robot::ActualManeuver::Turn); // On met le robot en mode Turn
    else
        this->setActualManeuver(Robot::ActualManeuver::Mouvement); // On met le robot en mode Mouvement
    // On applique la bonne vitesse au roue en fonction des cas
    switch (this->getActualManeuver()) {
        case ActualManeuver::Mouvement:
            if(this->distanceEntreRobotEtObjet(xD,yD) < margin) // Si on est sur la pose désirée
                this->setActualManeuver(Robot::ActualManeuver::Idle); // On met le robot en mode Idle
            else
                this->move(); // On se déplace dans la direction actuelle
            break;
        case ActualManeuver::Turn:
            this->turn(Robot::angleRobotArbre(x,y,xD,yD,this->getOrientation()));  // On détermine l'orientation désirée
            break;
        case ActualManeuver::SpecialAction:
            this->move(0); // On arrête le robot pour effectuer l'action spéciale
            break;
        case ActualManeuver::Idle:
            this->move(0); // On arrête le robot
            break;
    }
}

// Static methods
float Robot::distanceEntreRobotEtObjet( float xObjet, float yObjet) {
    /*
     * Permet de calculer la distance entre le robot et un objet
     * @param xObjet: position x de l'objet
     * @param yObjet: position y de l'objet
     */
    auto x = (float)this->getPosition()[0];
    auto y = (float)this->getPosition()[1];

    return (float) std::sqrt(pow(xObjet - x, 2) + pow(yObjet - y, 2));
}

float Robot::angle(float x1, float y1, float x2, float y2) {
    /*
     * Permet de calculer l'angle entre deux points
     */
    return atan2(y2-y1,x2-x1)*180/M_PI;
}



// Fonction pour déplacer le robot à une position donnée
void Robot::moveCinematique(double target_x, double target_y, double max_speed, double delta_t) {
    double delta_x = target_x - this->pose[0];
    double delta_y = target_y - this->pose[1];
    double distance_to_target = std::sqrt(delta_x * delta_x + delta_y * delta_y);

    if (distance_to_target < 0.01) {
        // Le robot est déjà proche de la cible, pas besoin de bouger
        return;
    }

    double target_theta = std::atan2(delta_y, delta_x);

    // Calculez la vitesse linéaire cible en limitant la vitesse à max_speed
    double target_v = std::min(max_speed, distance_to_target / delta_t);

    // Calculez la vitesse angulaire cible pour tourner vers la cible
    double delta_theta = target_theta - this->pose[2];
    double target_omega = delta_theta / delta_t;

    // Mettez à jour les vitesses des roues pour atteindre la cible
    double v_left = target_v - this->entraxe * target_omega / 2.0;
    double v_right = target_v + this->entraxe * target_omega / 2.0;
    this->setSpeedWeelLeft((float)v_left);
    this->setSpeedWeelRight((float)v_right);
}
