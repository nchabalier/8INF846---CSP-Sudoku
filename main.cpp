#include <iostream>
#include <fstream>
#include "Carte.h"

int main() {

    Carte carte = Carte("../data/grid.txt");
    cout << carte << endl;

    /*std::ifstream is;
    is.open("../data/grid.txt");

    char c;
    while (is.get(c))
        std::cout << c;*/

    return 0;
}