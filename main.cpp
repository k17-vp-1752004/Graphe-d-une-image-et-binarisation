#include "image.h"

int main() {
    Image img;

    img.chargerDonneesDuFichier("coins.ascii.pgm");
    // img.affichage();
    img.binariserImage(0.5);
    img.sauvegarder("coins.ascii_0.0005.pgm");

    return 0;
}