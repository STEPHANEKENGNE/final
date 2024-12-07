#include "gestionnairefichiers.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

GestionnaireFichiers::GestionnaireFichiers(const std::string& cheminFichierEntree) : compteurGeneration(0) {
    std::filesystem::path chemin(cheminFichierEntree);
    dossierSortie = chemin.stem().string() + "_out";
    if (!std::filesystem::exists(dossierSortie)) {
        std::filesystem::create_directory(dossierSortie);
    }
}

void GestionnaireFichiers::enregistrerGrille(const std::vector<std::vector<int>>& grille) {
    std::string cheminFichier = dossierSortie + "/generation_" + std::to_string(compteurGeneration) + ".txt";
    std::ofstream fichier(cheminFichier);
    if (!fichier.is_open()) {
        std::cerr << "Erreur : Impossible de créer le fichier " << cheminFichier << std::endl;
        return;
    }
    for (const auto& ligne : grille) {
        for (int cellule : ligne) {
            fichier << cellule << " ";
        }
        fichier << std::endl;
    }
    fichier.close();
    compteurGeneration++;
}
