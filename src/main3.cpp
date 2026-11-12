
#include <iostream>
#include <string>
using namespace std;

// Classe Noeud
class Noeud {
public:
    int cle;
    string valeur;
    Noeud* suivant;

    Noeud(int c, string v) {
        cle = c;
        valeur = v;
        suivant = nullptr;
    }
};

// Classe TableHachage
class TableHachage {
private:
    Noeud** table;
    int tailleTable;

    // Fonction de hachage
    int hachage(int cle) const {
        return ((cle % tailleTable) + tailleTable) % tailleTable;
    }

public:

    // Constructeur
    TableHachage(int taille) {
        tailleTable = taille;
        table = new Noeud*[tailleTable];

        for (int i = 0; i < tailleTable; i++) {
            table[i] = nullptr;
        }
    }

    // Inserer une paire cle/valeur
    void inserer(int cle, string valeur) {
        int indice = hachage(cle);

        Noeud* courant = table[indice];

        // Si la cle existe deja, modifier sa valeur
        while (courant != nullptr) {
            if (courant->cle == cle) {
                courant->valeur = valeur;
                cout << "Valeur mise a jour !" << endl;
                return;
            }

            courant = courant->suivant;
        }

        // Ajouter un nouveau noeud
        Noeud* nouveau = new Noeud(cle, valeur);
        nouveau->suivant = table[indice];
        table[indice] = nouveau;

        cout << "Element insere avec succes !" << endl;
    }

    // Rechercher une cle
    bool rechercher(int cle) const {
        int indice = hachage(cle);
        Noeud* courant = table[indice];

        while (courant != nullptr) {
            if (courant->cle == cle) {
                cout << "Cle trouvee : " << cle
                     << " | Valeur : " << courant->valeur << endl;
                return true;
            }

            courant = courant->suivant;
        }

        cout << "Cle introuvable !" << endl;
        return false;
    }

    // Supprimer une cle
    bool supprimer(int cle) {
        int indice = hachage(cle);
        Noeud* courant = table[indice];
        Noeud* precedent = nullptr;

        while (courant != nullptr) {
            if (courant->cle == cle) {

                if (precedent == nullptr) {
                    table[indice] = courant->suivant;
                } else {
                    precedent->suivant = courant->suivant;
                }

                delete courant;

                cout << "Element supprime !" << endl;
                return true;
            }

            precedent = courant;
            courant = courant->suivant;
        }

        cout << "Cle introuvable !" << endl;
        return false;
    }

    // Afficher toute la table
    void afficher() const {
        cout << "\n===== CONTENU DE LA TABLE =====" << endl;

        for (int i = 0; i < tailleTable; i++) {
            cout << "Case " << i << " : ";

            Noeud* courant = table[i];

            while (courant != nullptr) {
                cout << "[" << courant->cle << " : "
                     << courant->valeur << "] -> ";

                courant = courant->suivant;
            }

            cout << "NULL" << endl;
        }
    }

    // Destructeur
    ~TableHachage() {
        for (int i = 0; i < tailleTable; i++) {
            Noeud* courant = table[i];

            while (courant != nullptr) {
                Noeud* temp = courant;
                courant = courant->suivant;
                delete temp;
            }
        }

        delete[] table;
    }
};

// Programme principal
int main() {

    TableHachage th(5);

    // Insertion
    th.inserer(10, "Ali");
    th.inserer(15, "Sara");
    th.inserer(20, "Amine");
    th.inserer(7, "Youssef");

    // Afficher la table
    th.afficher();

    // Rechercher
    cout << "\n===== RECHERCHE =====" << endl;
    th.rechercher(15);
    th.rechercher(30);

    // Supprimer
    cout << "\n===== SUPPRESSION =====" << endl;
    th.supprimer(15);

    // Afficher apres suppression
    th.afficher();

    return 0;
}
