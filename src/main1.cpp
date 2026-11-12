
#include <iostream>
using namespace std;

// Classe Noeud
class Noeud {
public:
    int valeur;
    Noeud* suivant;

    Noeud(int v) {
        valeur = v;
        suivant = nullptr;
    }
};

// Classe ListeChainee
class ListeChainee {
private:
    Noeud* tete;
    int nbElements;

public:

    // Constructeur
    ListeChainee() {
        tete = nullptr;
        nbElements = 0;
    }

    // Ajouter au debut
    void ajouterDebut(int valeur) {
        Noeud* nouveau = new Noeud(valeur);

        nouveau->suivant = tete;
        tete = nouveau;

        nbElements++;
    }

    // Ajouter a la fin
    void ajouterFin(int valeur) {
        Noeud* nouveau = new Noeud(valeur);

        if (tete == nullptr) {
            tete = nouveau;
        } else {
            Noeud* courant = tete;

            while (courant->suivant != nullptr) {
                courant = courant->suivant;
            }

            courant->suivant = nouveau;
        }

        nbElements++;
    }

    // Supprimer une valeur
    bool supprimer(int valeur) {
        if (tete == nullptr) {
            return false;
        }

        // Si la valeur est au debut
        if (tete->valeur == valeur) {
            Noeud* temp = tete;
            tete = tete->suivant;
            delete temp;
            nbElements--;
            return true;
        }

        Noeud* courant = tete;

        while (courant->suivant != nullptr &&
               courant->suivant->valeur != valeur) {
            courant = courant->suivant;
        }

        if (courant->suivant == nullptr) {
            return false;
        }

        Noeud* temp = courant->suivant;
        courant->suivant = temp->suivant;

        delete temp;
        nbElements--;

        return true;
    }

    // Afficher la liste
    void afficher() const {
        Noeud* courant = tete;

        while (courant != nullptr) {
            cout << courant->valeur << " -> ";
            courant = courant->suivant;
        }

        cout << "NULL" << endl;
    }

    // Retourner la taille
    int taille() const {
        return nbElements;
    }

    // Iterateur personnalise
    class Iterator {
    private:
        Noeud* courant;

    public:
        Iterator(Noeud* n) {
            courant = n;
        }

        int& operator*() {
            return courant->valeur;
        }

        Iterator& operator++() {
            courant = courant->suivant;
            return *this;
        }

        bool operator!=(const Iterator& autre) const {
            return courant != autre.courant;
        }
    };

    // Debut et fin de la liste
    Iterator begin() {
        return Iterator(tete);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    // Destructeur
    ~ListeChainee() {
        Noeud* courant = tete;

        while (courant != nullptr) {
            Noeud* temp = courant;
            courant = courant->suivant;
            delete temp;
        }

        tete = nullptr;
    }
};

// Programme principal
int main() {

    ListeChainee liste;

    // Ajouter des elements
    liste.ajouterDebut(20);
    liste.ajouterDebut(10);
    liste.ajouterFin(30);
    liste.ajouterFin(40);

    cout << "Liste initiale :" << endl;
    liste.afficher();

    // Afficher la taille
    cout << "Taille de la liste : " << liste.taille() << endl;

    // Supprimer un element
    liste.supprimer(20);

    cout << "\nApres suppression de 20 :" << endl;
    liste.afficher();

    cout << "Nouvelle taille : " << liste.taille() << endl;

    // Parcourir avec l'iterateur personnalise
    cout << "\nParcours avec l'iterateur :" << endl;

    for (int valeur : liste) {
        cout << valeur << " ";
    }

    cout << endl;

    return 0;
}
