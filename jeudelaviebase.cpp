#include "jeudelaviebase.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>

JeuDeLaVieBase::JeuDeLaVieBase(int lignes, int colonnes) : lignes(lignes), colonnes(colonnes) {
    grille.resize(lignes, std::vector<int>(colonnes, 0));
}

void JeuDeLaVieBase::chargerEtatDepuisFichier(const std::string& cheminFichier) {
    std::ifstream fichier(cheminFichier);
    if (!fichier.is_open()) {
        std::cout << "Erreur : Impossible d'ouvrir le fichier " << cheminFichier << std::endl;
        exit(1);
    }
    fichier >> lignes >> colonnes;
    grille.resize(lignes, std::vector<int>(colonnes));
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            fichier >> grille[i][j];
            if (grille[i][j] != 0 && grille[i][j] != 1) {
                std::cout << "Erreur : Valeurs invalides dans le fichier (seules 0 ou 1 sont autorisées)." << std::endl;
                exit(1);
            }
        }
    }
    fichier.close();
}

void JeuDeLaVieBase::afficherGrilleConsole() const {
    for (const auto& ligne : grille) {
        for (int cellule : ligne) {
            std::cout << cellule << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::string(colonnes * 2, '-') << std::endl;
}

const std::vector<std::vector<int>>& JeuDeLaVieBase::getGrille() const {
    return grille;
}

int JeuDeLaVieBase::compterVoisinsVivants(int ligne, int colonne) {
    int voisinsVivants = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int voisinLigne = ligne + i;
            int voisinColonne = colonne + j;
            if (voisinLigne >= 0 && voisinLigne < lignes && voisinColonne >= 0 && voisinColonne < colonnes) {
                voisinsVivants += grille[voisinLigne][voisinColonne];
            }
        }
    }
    return voisinsVivants;
}
