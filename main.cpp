#include <iostream>
#include "jeudelavieclassique.hpp"
#include "jeudelavieextension.hpp"
#include "gestionnairefichiers.hpp"
#include "interface.hpp"

using namespace std;

int main() {
    string cheminFichier;
    cout << "Entrez le chemin du fichier contenant la grille initiale: ";
    cin >> cheminFichier;

    // Choix du type de jeu
    int choix;
    cout << "Choisissez le type de simulation :\n";
    cout << "1. Jeu de la Vie Classique\n";
    cout << "2. Jeu de la Vie avec extension\n";
    cout << "Votre choix (1 ou 2) : ";
    cin >> choix;

    // Validation du choix
    while (choix != 1 && choix != 2) {
        cout << "Choix invalide. Veuillez entrer 1 ou 2 : ";
        cin >> choix;
    }

    // Création de l'objet de jeu en fonction du choix
    JeuDeLaVieBase* jeu = nullptr;
    if (choix == 1) {
        jeu = new JeuDeLaVieClassique(0, 0);
    } else {
        jeu = new JeuDeLaVieExtension(0, 0);
    }

    // Charger l'état initial de la grille
    jeu->chargerEtatDepuisFichier(cheminFichier);

    // Demander l'intervalle de temps entre deux générations
    int intervalleTemps;
    cout << "Entrez l'intervalle de temps entre deux générations (en millisecondes) : ";
    cin >> intervalleTemps;

    // Création de l'interface et lancement de la simulation
    Interface interface(jeu, intervalleTemps, cheminFichier);
    interface.afficherGraphique();

    // Libération de la mémoire
    delete jeu;
    return 0;
}
