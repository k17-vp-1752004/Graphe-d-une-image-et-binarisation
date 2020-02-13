#include "image.h"

Image::Image() {

}

bool Image::valider(int i, int j) {
    return 0 <= i && i < hauteur && 0 <= j && j < largeur;
}

int Image::calculerIndice(int i, int j) {
    return i * largeur + j;
}

double Image::prendreVariance() {
    int n = tableau.size();
    double moyenne = 0;
    for (int x : tableau) {
        moyenne += x;
    }
    moyenne /= n;

    double variance = 0;
    for (int x : tableau) {
        variance += (x - moyenne) * (x - moyenne);
    }
    variance /= n;
    return variance;
}

void Image::supprimer() {
    type = "";
    largeur = hauteur = intensiteMaximale = 0;
    tableau.clear();
}

bool Image::modifier(int i, int j, int valeur) {
    if (!valider(i, j))
        return false;
    if (0 > valeur || valeur > 255)
        return false;
    tableau[calculerIndice(i, j)] = valeur;
    return true;
}

int Image::prendreValeur(int i, int j) {
    if (!valider(i, j))
        return -1;
    return tableau[calculerIndice(i, j)];
}

int Image::prendreEst(int i, int j) {
    return prendreValeur(i, j + 1);
}

int Image::prendreOuest(int i, int j) {
    return prendreValeur(i, j - 1);
}

int Image::prendreSud(int i, int j) {
    return prendreValeur(i + 1, j);
}

int Image::prendreNord(int i, int j) {
    return prendreValeur(i - 1, j);
}

void Image::creerGraphe(FordFulkerson &ff, int s, int t, double alpha) {
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    double variance = prendreVariance();
    double temp = 2 * variance;

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            int source = calculerIndice(i, j);
            int target, x, y;
            double cap;
            for (int d = 0; d < 4; d++) {
                x = i + dx[d];
                y = j + dy[d];
                if (valider(x, y)) {
                    target = calculerIndice(x, y);
                    cap = pow(tableau[source] - tableau[target], 2);
                    cap = exp(-cap / temp);
                    ff.ajouterArc(source, target, cap);
                }
            }
        }
    }

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            int noeud = calculerIndice(i, j);
            ff.ajouterArc(s, noeud, -alpha * log((255.0 - tableau[noeud]) / 255));
            ff.ajouterArc(noeud, t, -alpha * log(1.0 * tableau[noeud] / 255));
        }
    }
}

void Image::binariserImage(double alpha) {
    int n = largeur * hauteur;
    FordFulkerson ff(n + 2);
    creerGraphe(ff, n, n + 1, alpha);

    cout << ff.caculer(n, n + 1) << "\n";

    for (int i = 0; i < n; i++) {
        Arc arc = ff.prendreArc(n, i);
        if (abs(arc.capacite - arc.flot) <= EPS) {
            tableau[arc.target] = 255;
        }
        arc = ff.prendreArc(n + 1, i); // prendre arc arrière de t
        int index = arc.target;
        arc = ff.prendreArc(arc.target, arc.inverse);   // prendre arc avant pour t
        if (abs(arc.capacite - arc.flot) <= EPS) {
            tableau[index] = 0;
        }
    }
}

void Image::affichage() {
    cout << type << "\n";
    cout << largeur << " " << hauteur << "\n";
    cout << intensiteMaximale << "\n";
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            cout << tableau[i * largeur + j] << (j == largeur - 1 ? "\n" : " ");
        }
    }
}

void Image::sauvegarder(string filename) {
    ofstream os(filename.c_str());

    os << type << "\n";
    os << largeur << " " << hauteur << "\n";
    os << intensiteMaximale << "\n";
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            os << tableau[i * largeur + j] << (j == largeur - 1 ? "\n" : " ");
        }
    }

    os.close();
}

void Image::chargerDonneesDuFichier(string filename) {
    ifstream is(filename.c_str());

    is >> type;
    is >> largeur >> hauteur;
    is >> intensiteMaximale;
    tableau.resize(largeur * hauteur);
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            is >> tableau[i * largeur + j];
        }
    }

    is.close();
}

Image::~Image() {

}