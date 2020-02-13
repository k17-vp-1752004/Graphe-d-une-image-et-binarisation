#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include "fordfulkerson.h"

using namespace std;

class Image {
private:
    string type;
    int largeur, hauteur;
    int intensiteMaximale;
    vector<int> tableau;

    bool valider(int i, int j);
    int calculerIndice(int i, int j);
    double prendreVariance();
    void creerGraphe(FordFulkerson& ff, int s, int t, double alpha);
public:
    Image();
    void supprimer();
    bool modifier(int i, int j, int valeur);
    int prendreValeur(int i, int j);
    int prendreEst(int i, int j);
    int prendreOuest(int i, int j);
    int prendreSud(int i, int j);
    int prendreNord(int i, int j);
    void affichage();
    void binariserImage(double alpha);
    void sauvegarder(string filename);
    void chargerDonneesDuFichier(string filename);
    ~Image();
};

#endif
