#include "jeudelavieextension.hpp"
#include <stdexcept>
#include <vector>
using namespace std;
// Constructeur de la classe
JeuDeLaVieExtension::JeuDeLaVieExtension(int lignes, int colonnes) : JeuDeLaVieBase(lignes, colonnes) {}

// Méthode pour calculer la prochaine génération avec gestion des cellules obstacles
void JeuDeLaVieExtension::prochaineGeneration() {
    // Gestion torique
    vector<vector<int>> nouvelleGrille = grille;
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            // Ignorer les cellules obstacles
            if (grille[i][j] == 2 || grille[i][j] == 3) {
                continue;
            }

            int voisinsVivants = compterVoisinsVivantsTorique(i, j);

            if (grille[i][j] == 1) {
                if (voisinsVivants < 2 || voisinsVivants > 3) {
                    nouvelleGrille[i][j] = 0;
                }
            } else if (grille[i][j] == 0) {
                if (voisinsVivants == 3) {
                    nouvelleGrille[i][j] = 1;
                }
            }
        }
    }
    grille = nouvelleGrille;
}

// Méthode pour insérer un motif dans la grille
void JeuDeLaVieExtension::placerMotif(const vector<vector<int>>& motif, int posX, int posY) {
    int lignesMotif = motif.size();
    int colonnesMotif = motif[0].size();

    for (int i = 0; i < lignesMotif; ++i) {
        for (int j = 0; j < colonnesMotif; ++j) {
            int x = posX + i;
            int y = posY + j;

            // Gestion des bords pour rester dans la grille
            if (x >= 0 && x < lignes && y >= 0 && y < colonnes) {
                grille[x][y] = motif[i][j];
            }
        }
    }
}

// Compteur torique avec gestion des limites
int JeuDeLaVieExtension::compterVoisinsVivantsTorique(int ligne, int colonne) {
    int voisinsVivants = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;

            int voisinLigne = (ligne + i + lignes) % lignes;
            int voisinColonne = (colonne + j + colonnes) % colonnes;

            if (grille[voisinLigne][voisinColonne] == 1 || grille[voisinLigne][voisinColonne] == 3) {
                voisinsVivants++;
            }
        }
    }
    return voisinsVivants;
}

// Motifs prédéfinis
const vector<vector<int>> JeuDeLaVieExtension::GLIDER = {
    {0, 1, 0},
    {0, 0, 1},
    {1, 1, 1}
};

const vector<vector<int>> JeuDeLaVieExtension::BLOCK = {
    {1, 1},
    {1, 1}
};

const vector<vector<int>> JeuDeLaVieExtension::SPACESHIP = {
    {0, 1, 1, 1, 0},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {0, 1, 1, 1, 0}
};

// Méthode pour récupérer un motif en fonction de son type
const vector<vector<int>>& JeuDeLaVieExtension::getMotif(char type) const {
    if (type == 'G') return GLIDER;
    if (type == 'B') return BLOCK;
    if (type == 'S') return SPACESHIP;
    throw std::invalid_argument("Motif inconnu !");
}
