#include <iostream>
#include <fstream>
#include "Carte.h"

int main() {

    Carte carte = Carte("../data/grid2.txt");
    cout << carte << endl;
    vector<pair<Case, vector<int>>> csp;

    for(Case& cases : carte.getCases()){
        csp.push_back((make_pair(cases, cases.getConstraints())));
    }

    carte.ac3(csp);



    /*while(carte.ac3()) {
        cout << "NOUVEAU TOUR : " << endl;
        cout << carte << endl;
    }*/

    return 0;
}