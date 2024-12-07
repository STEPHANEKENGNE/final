#ifndef GESTIONNAIRE_FICHIERS_HPP
#define GESTIONNAIRE_FICHIERS_HPP

#include <string>
#include <vector>

class GestionnaireFichiers {
private:
    std::string dossierSortie;
    int compteurGeneration;

public:
    GestionnaireFichiers(const std::string& cheminFichierEntree);
    void enregistrerGrille(const std::vector<std::vector<int>>& grille);
};

#endif // GESTIONNAIRE_FICHIERS_HPP
