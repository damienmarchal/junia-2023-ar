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
}

// destructors
Robot::~Robot() = default;

// getters
float *Robot::getDesiredPose() { return new float[3]{static_cast<float>(this->getPosition()[0]), static_cast<float>(this->getPosition()[1]), this->getOrientation()}; }
float Robot::getOrientation() { return this->orientation; }
float Robot::getBattery() { return this->battery; }
float Robot::getCapacity() { return this->capacity; }
float Robot::getSpeed() { return this->speed; }
std::vector<std::vector<Entite *>> Robot::getLocalMap() { return this->localMap; }
Robot::Direction Robot::getDirection() { return this->direction; }
Robot::ActualManeuver Robot::getActualManeuver() { return this->actualManeuver; }

// setters
void Robot::setActualManeuver(Robot::ActualManeuver actualManeuver) { this->actualManeuver = actualManeuver; }
void Robot::setOrientation(float orientation) { this->orientation = orientation; }
void Robot::setBattery(float battery) { this->battery = battery; }
void Robot::setCapacity(float capacity) { this->capacity = capacity; }
void Robot::setSpeed(float speed) { this->speed = speed; }
void Robot::setDesiredPose(float x, float y, float orientation) {
    this->diseriedPose[0] = x;
    this->diseriedPose[1] = y;
    this->diseriedPose[2] = orientation;
}

// methods
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
                    if(x-2+1<0||y-2+j<0){ // Si on est sur les bords de la carte
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

void Robot::turn() {
    this->direction = (Direction) ((int) this->direction + 1);
}
void Robot::priseDecision(Environment &env) {
    return;
}

void Robot::Update(Environment &env) {
    /*
     * Permet de mettre à jour les données du robot
     */
    // TODO : mettre à jour les données du robot
    // Nouvelle carte
    this->localMap = this->getScannerData(env, 1);
    // Nouvelle position
    // Nouvelle orientation
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


void Robot::cinematicMove() {
    // TODO : faire bouger le robot en se basant sur la cinématique inverse
    /*
     * Permet de faire bouger le robot en se basant sur la cinématique inverse
     */

    // on récupère la position du robot
    int x = this->getPosition()[0];
    int y = this->getPosition()[1];

    // on récupère la position désirée du robot
    int xD = this->getDesiredPose()[0];
    int yD = this->getDesiredPose()[1];

    // on récupère l'orientation du robot
    float orientation = this->getOrientation();



}


