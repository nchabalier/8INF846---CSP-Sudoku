#include <iostream>
#include <fstream>
#include "Carte.h"

int main() {

    Carte carte = Carte("../data/grid.txt");
    cout << carte << endl;

    while(true) {
        carte.ac3();
        cout << carte << endl;
    }

    return 0;
}