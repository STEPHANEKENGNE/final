#include "interface.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include <vector>

using namespace std;

#include "jeudelavieextension.hpp"


Interface::Interface(JeuDeLaVieBase* jeu, int intervalleTemps, const std::string& cheminFichierEntree)
    : jeu(jeu), intervalleTemps(intervalleTemps), borderSize(1), gestionnaireFichiers(cheminFichierEntree) {

    // Taille de la grille
    int lignes = jeu->getGrille().size();
    int colonnes = jeu->getGrille()[0].size();

    // Taille des cellules
    cellSize = 20; // Taille fixe pour chaque cellule en pixels

    // Taille totale de la fenêtre
    int windowWidth = colonnes * cellSize;
    int windowHeight = lignes * cellSize;

    // Limiter la taille de la fenêtre pour qu'elle ne dépasse pas la résolution de l'écran
    sf::VideoMode screenResolution = sf::VideoMode::getDesktopMode();
    if (windowWidth > screenResolution.width || windowHeight > screenResolution.height) {
        float scaleFactor = std::min(
            static_cast<float>(screenResolution.width) / windowWidth,
            static_cast<float>(screenResolution.height) / windowHeight
        );
        cellSize = static_cast<int>(cellSize * scaleFactor);
        windowWidth = colonnes * cellSize;
        windowHeight = lignes * cellSize;
    }

    window.create(sf::VideoMode(windowWidth, windowHeight), "Jeu de la Vie", sf::Style::Titlebar | sf::Style::Close);
}

void Interface::afficherGraphique() {
    sf::RectangleShape cellule(sf::Vector2f(cellSize - borderSize, cellSize - borderSize));
    vector<vector<int>> grillePrecedente = jeu->getGrille();
    bool simulationStable = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Add) {
                    intervalleTemps = intervalleTemps - 1; // Réduit l'intervalle mais pas en dessous de 50 ms
                } else if (event.key.code == sf::Keyboard::Subtract) {
                    intervalleTemps = intervalleTemps + 1; // Augmente l'intervalle mais pas au-delà de 2000 ms
                }

                if (dynamic_cast<JeuDeLaVieExtension*>(jeu)) {
                    JeuDeLaVieExtension* extension = static_cast<JeuDeLaVieExtension*>(jeu);
                    sf::Vector2i souris = sf::Mouse::getPosition(window);

                    // Convertir position souris en coordonnées de grille
                    int grilleX = souris.y / cellSize;
                    int grilleY = souris.x / cellSize;

                    if (event.key.code == sf::Keyboard::G) {
                        extension->placerMotif(extension->getMotif('G'), grilleX, grilleY);
                    } else if (event.key.code == sf::Keyboard::B) {
                        extension->placerMotif(extension->getMotif('B'), grilleX, grilleY);
                    } else if (event.key.code == sf::Keyboard::S) {
                        extension->placerMotif(extension->getMotif('S'), grilleX, grilleY);
                    }
                }
            }
        }

        if (!simulationStable) {
            // Affichage console
            jeu->afficherGrilleConsole();

            // Sauvegarde de la grille actuelle pour comparaison 
            vector<vector<int>> grilleActuelle = jeu->getGrille();

            // Calcul de la prochaine génération
            jeu->prochaineGeneration();

            // Enregistrer la génération actuelle
            gestionnaireFichiers.enregistrerGrille(grilleActuelle);

            // Si la grille n'a pas changé, marquer la simulation comme stable
            if (grilleActuelle == jeu->getGrille()) {
                std::cout << "La grille a atteint un état stable. Simulation arrêtée.\n";
                simulationStable = true;
            }
        }

        // Effacer la fenêtre
        window.clear(sf::Color::White);

        // Afficher les cellules
        const auto& grille = jeu->getGrille();
        for (size_t i = 0; i < grille.size(); ++i) {
            for (size_t j = 0; j < grille[i].size(); ++j) {
                cellule.setPosition(j * cellSize, i * cellSize);
                cellule.setFillColor(grille[i][j] == 1 ? sf::Color::Black : sf::Color::White);
                cellule.setOutlineThickness(borderSize);
                cellule.setOutlineColor(sf::Color::Red);
                window.draw(cellule);
            }
        }

        window.display();

        // Pause selon l'intervalle de temps choisi par l'utilisateur
        sf::sleep(sf::milliseconds(intervalleTemps));
    }
}
