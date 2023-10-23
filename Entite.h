//
// Created by cload on 16/10/2023.
//

#ifndef COURSC_ENTITE_H
#define COURSC_ENTITE_H

#include <iostream>

class Entite {
public:
    // attributs
    int position[2];
    std::string nom;

    // Constructor
    Entite(int x, int y);

    // Destructor
    virtual ~Entite() = default;

    // Getters
    std::string getNom() ;
    int* getPosition();

    // Setters
    void set_Position(int x, int y);

};


#endif //COURSC_ENTITE_H
