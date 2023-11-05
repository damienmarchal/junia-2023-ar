#include <cmath>
#include <iostream>
#include <vector>

#include "Environment.h"
#include <iostream>
#include <cmath>


/*
 * Etat actuel du projet:
 * - Le robot planteur se déplace sur la carte et plantes des arbres
 *      cependant parfois il a des bugs d'affichages et parfois (lorsqu'il est collé à un mur ?) il fait tout PT
 * - Le robot arroseur a du mal à se déplacer mais arrose bien les arbres
 * - Le robot récolteur ne fait rien
 * - Les arbres grandissent sans aucun problème le cycle est parfais
 * - La simulation et l'affichage fonctionne (si on enlève les bugs du au robot planteur)
 * - La visualisation via UNITY n'a pas encore été mise en place
 *          mais la partie UNITY à déjà commencé à être développé
 *          elle comporte tout son HUD et ses template
 *    La liasion entre le C++ et l'Unity n'a pas encore été mise en place
 *          Mais la technique à utiliser est déjà connu il s'agit de faire du webSocket
 *
 *   Conclusion j'ai essayé le max mais j'ai pas eu assez de temps pour tout faire
 *      Je finirai tout de meme ce projet dans les semaines à venir
 */
int main() {
    Environment env(7, 7);
    env.initMap(10,0,1,0);
    env.printMap();

    env.runSimulation(); // Lance la simulation

    return 0;
}


