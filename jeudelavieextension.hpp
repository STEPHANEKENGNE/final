#ifndef JEUDELAVIEEXTENSION_HPP
#define JEUDELAVIEEXTENSION_HPP

#include "jeudelaviebase.hpp"

class JeuDeLaVieExtension : public JeuDeLaVieBase {
public:
    JeuDeLaVieExtension(int lignes, int colonnes);

    void prochaineGeneration() override;
    void placerMotif(const std::vector<std::vector<int>>& motif, int posX, int posY);
    const std::vector<std::vector<int>>& getMotif(char type) const;

private:
    static const std::vector<std::vector<int>> GLIDER;
    static const std::vector<std::vector<int>> BLOCK;
    static const std::vector<std::vector<int>> SPACESHIP;

    int compterVoisinsVivantsTorique(int ligne, int colonne);
};

#endif // JEUDELAVIEEXTENSION_HPP
