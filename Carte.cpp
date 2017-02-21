//
// Created by Aburam on 04/02/17.
//

#include <fstream>
#include "Carte.h"

Carte::Carte(string file) {
    string line;
    ifstream is(file);

    //std::getline(is, line );
    int posX = 0;
    while (getline( is, line )) {
        int posY=0;
        for(char c : line) {
            m_cases.push_back(Case(posX, posY, int(c)-48));
            posY++;
        }
        posX++;
    }
    m_sizeX = posX;
    m_sizeY = posX;


}

Carte::Carte(int sizeX, int sizeY) {
    m_sizeX = sizeX;
    m_sizeY = sizeY;
    for(int positionX=0; positionX<m_sizeX; ++positionX){
        for (int positionY=0; positionY<m_sizeY; ++positionY ) {
            m_cases.push_back(Case(positionX, positionY));
        }
    }
}

Carte::~Carte() {

}

int Carte::getSize() const{
    return m_sizeX*m_sizeY;
}

int Carte::getSizeX() const{
    return m_sizeX;
}

int Carte::getSizeY() const{
    return m_sizeY;
}

vector<Case>& Carte::getCases(){
    return m_cases;
}

Case& Carte::getCase(int position){
    if(position < m_cases.size()){
        return m_cases.at(position); ;
    }
    throw logic_error("La position demandee n'existe pas");

}


int Carte::findIndex(Case &searchCase) const {
    for( int i = 0; i < m_cases.size(); i++ ) {
        if(m_cases[i] == searchCase) {
            return i;
        }
    }
    return -1;
}

int Carte::getIndexPosition(Case& position) {
    return findIndex(position);
}