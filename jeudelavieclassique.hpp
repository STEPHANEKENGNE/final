#ifndef JEU_DE_LA_VIE_CLASSIQUE_HPP
#define JEU_DE_LA_VIE_CLASSIQUE_HPP

#include "jeudelaviebase.hpp"

class JeuDeLaVieClassique : public JeuDeLaVieBase {
public:
    JeuDeLaVieClassique(int lignes, int colonnes);
    void prochaineGeneration() override;
};

#endif // JEU_DE_LA_VIE_CLASSIQUE_HPP
