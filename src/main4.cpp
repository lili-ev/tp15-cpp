
#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
using namespace std;

// Exception personnalisee
class PileVideException : public exception {
public:
    const char* what() const noexcept override {
        return "Erreur : impossible de depiler une pile vide !";
    }
};

// Classe Pile generique
template <typename T>
class Pile {
private:
    T* elements;
    int capacite;
    int nombre;

public:

    // Constructeur
    Pile(int c = 100) {
        capacite = c;
        nombre = 0;
        elements = new T[capacite];
    }

    // Empiler un element
    void empiler(T element) {
        if (nombre == capacite) {
            cout << "La pile est pleine !" << endl;
            return;
        }

        elements[nombre] = element;
        nombre++;

    }

    // Depiler un element
    T depiler() {
        if (estVide()) {
            throw PileVideException();
        }

        nombre--;
        return elements[nombre];
    }

    // Retourner le sommet
    T sommet() const {
        if (estVide()) {
            throw PileVideException();
        }

        return elements[nombre - 1];
    }

    // Verifier si la pile est vide
    bool estVide() const {
        return nombre == 0;
    }

    // Inverser la pile
    void inverser() {
        reverse(elements, elements + nombre);
    }

    // Afficher la pile
    void afficher() const {
        cout << "Pile : ";

        for (int i = nombre - 1; i >= 0; i--) {
            cout << elements[i] << " ";
        }

        cout << endl;
    }

    // Destructeur
    ~Pile() {
        delete[] elements;
    }
};

// Programme principal
int main() {

    // Test avec int
    cout << "===== PILE D'ENTIERS =====" << endl;

    Pile<int> p1;

    p1.empiler(10);
    p1.empiler(20);
    p1.empiler(30);

    p1.afficher();

    cout << "Sommet : " << p1.sommet() << endl;
    cout << "Element retire : " << p1.depiler() << endl;

    p1.afficher();

    p1.inverser();

    cout << "Apres inversion : ";
    p1.afficher();


    // Test avec string
    cout << "\n===== PILE DE CHAINES =====" << endl;

    Pile<string> p2;

    p2.empiler("Ali");
    p2.empiler("Sara");
    p2.empiler("Amine");

    p2.afficher();


    // Test avec double
    cout << "\n===== PILE DE REELS =====" << endl;

    Pile<double> p3;

    p3.empiler(10.5);
    p3.empiler(20.5);
    p3.empiler(30.5);

    p3.afficher();


    // Test de l'exception
    cout << "\n===== TEST EXCEPTION =====" << endl;

    Pile<int> p4;

    try {
        p4.depiler();
    }
    catch (const PileVideException& e) {
        cout << e.what() << endl;
    }

    return 0;
}
