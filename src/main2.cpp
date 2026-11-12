
#include <iostream>
#include <stdexcept>
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

// Exception personnalisee
class FileVideException : public exception {
public:
    const char* what() const noexcept override {
        return "Erreur : la file est vide !";
    }
};

// Classe File
class File {
private:
    Noeud* debut;
    Noeud* fin;

public:

    // Constructeur
    File() {
        debut = nullptr;
        fin = nullptr;
    }

    // Verifier si la file est vide
    bool estVide() const {
        return debut == nullptr;
    }

    // Une file dynamique n'a pas de capacite maximale
    bool estPleine() const {
        return false;
    }

    // Ajouter un element
    void enfiler(int valeur) {
        Noeud* nouveau = new Noeud(valeur);

        if (estVide()) {
            debut = nouveau;
            fin = nouveau;
        } else {
            fin->suivant = nouveau;
            fin = nouveau;
        }

        cout << valeur << " ajoute a la file." << endl;
    }

    // Retirer un element
    int defiler() {
        if (estVide()) {
            throw FileVideException();
        }

        Noeud* temp = debut;
        int valeur = temp->valeur;

        debut = debut->suivant;

        if (debut == nullptr) {
            fin = nullptr;
        }

        delete temp;

        return valeur;
    }

    // Afficher la file
    void afficher() const {
        Noeud* courant = debut;

        cout << "File : ";

        while (courant != nullptr) {
            cout << courant->valeur << " ";
            courant = courant->suivant;
        }

        cout << endl;
    }

    // Destructeur
    ~File() {
        while (!estVide()) {
            Noeud* temp = debut;
            debut = debut->suivant;
            delete temp;
        }

        fin = nullptr;
    }
};

// Programme principal
int main() {
    File file;
    int choix;
    int valeur;

    do {
        cout << "\n===== MENU FILE D'ATTENTE =====" << endl;
        cout << "1. Enfiler un element" << endl;
        cout << "2. Defiler un element" << endl;
        cout << "3. Afficher la file" << endl;
        cout << "4. Verifier si la file est vide" << endl;
        cout << "5. Verifier si la file est pleine" << endl;
        cout << "0. Quitter" << endl;

        cout << "Votre choix : ";
        cin >> choix;

        switch (choix) {

        case 1:
            cout << "Donner une valeur : ";
            cin >> valeur;
            file.enfiler(valeur);
            break;

        case 2:
            try {
                cout << "Element retire : " << file.defiler() << endl;
            }
            catch (const FileVideException& e) {
                cout << e.what() << endl;
            }
            break;

        case 3:
            file.afficher();
            break;

        case 4:
            if (file.estVide()) {
                cout << "La file est vide." << endl;
            } else {
                cout << "La file n'est pas vide." << endl;
            }
            break;

        case 5:
            if (file.estPleine()) {
                cout << "La file est pleine." << endl;
            } else {
                cout << "La file n'est pas pleine." << endl;
            }
            break;

        case 0:
            cout << "Fin du programme." << endl;
            break;

        default:
            cout << "Choix invalide !" << endl;
        }

    } while (choix != 0);

    return 0;
}
