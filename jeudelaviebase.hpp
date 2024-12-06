#ifndef JEU_DE_LA_VIE_BASE_HPP
#define JEU_DE_LA_VIE_BASE_HPP

#include <vector>
#include <string>

class JeuDeLaVieBase {
protected:
    std::vector<std::vector<int>> grille;
    int lignes, colonnes;

public:
    JeuDeLaVieBase(int lignes, int colonnes);
    virtual ~JeuDeLaVieBase();
    virtual void prochaineGeneration() = 0;
    void chargerEtatDepuisFichier(const std::string& cheminFichier);
    void afficherGrilleConsole() const;
    const std::vector<std::vector<int>>& getGrille() const;

protected:
    int compterVoisinsVivants(int ligne, int colonne);
};

#endif // JEU_DE_LA_VIE_BASE_HPP
