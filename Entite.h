//
// Created by cload on 16/10/2023.
//

#ifndef COURSC_ENTITE_H
#define COURSC_ENTITE_H

#include <iostream>

class Entite {
public:
    int position[2];
    std::string nom;
    Entite(int x, int y);
    virtual ~Entite() = default;
    void set_Position(int x, int y);
    std::string getNom() ;
    int* getPosition();
};


#endif //COURSC_ENTITE_H
