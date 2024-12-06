#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include "jeudelaviebase.hpp"  // Assure-toi que ce fichier existe pour les classes JeuDeLaVieBase
#include "gestionnairefichiers.hpp"  // Assure-toi que ce fichier existe

class Interface {
private:
    sf::RenderWindow window;
    JeuDeLaVieBase* jeu;
    int cellSize;
    int borderSize;
    int intervalleTemps; // Intervalle de temps en millisecondes entre deux générations
    GestionnaireFichiers gestionnaireFichiers;

public:
    Interface(JeuDeLaVieBase* jeu, int intervalleTemps, const std::string& cheminFichierEntree);
    void afficherGraphique();
};

#endif // INTERFACE_HPP
