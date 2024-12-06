#include "jeudelavieclassique.hpp"

JeuDeLaVieClassique::JeuDeLaVieClassique(int lignes, int colonnes) : JeuDeLaVieBase(lignes, colonnes) {}

void JeuDeLaVieClassique::prochaineGeneration() {
    std::vector<std::vector<int>> nouvelleGrille = grille;
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            int voisinsVivants = compterVoisinsVivants(i, j);
            if (grille[i][j] == 1) {
                if (voisinsVivants < 2 || voisinsVivants > 3) {
                    nouvelleGrille[i][j] = 0;
                }
            } else {
                if (voisinsVivants == 3) {
                    nouvelleGrille[i][j] = 1;
                }
            }
        }
    }
    grille = nouvelleGrille;
}
