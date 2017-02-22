//
// Created by Aburam on 04/02/17.
//

#include <fstream>
#include "Carte.h"

Carte::Carte(string file) {
    string line;
    ifstream is(file);


    m_sizeX = 9;
    m_sizeY = 9;

    for(int positionX=0; positionX<m_sizeX; ++positionX){
        for (int positionY=0; positionY<m_sizeY; ++positionY ) {
            m_cases.push_back(Case(positionX, positionY));
        }
    }

    //std::getline(is, line );
    int posX = 0;
    while (getline( is, line )) {
        int posY=0;
        for(char c : line) {
            Case& currentCase = m_cases.at(posX*m_sizeX+posY);
            currentCase.setValue((int) c - 48);
            updateConstraint(currentCase);
            posY++;
        }
        posX++;
    }



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

void Carte::updateConstraint(Case& position) {

    int value = position.getValue();

    //Update constraint horizontally
    int lineX = position.getPositionX();
    for(int i=0; i<m_sizeY; i++) {
        Case& currentCase = m_cases.at(lineX*m_sizeX+i);
        currentCase.addConstraint(value);
    }

    //Update constraint vertically
    int lineY = position.getPositionY();
    for(int i=0; i<m_sizeX; i++) {
        Case& currentCase = m_cases.at(i*m_sizeX+lineY);
        currentCase.addConstraint(value);
    }

    int topLeftCaseX = (int)(lineX / 3) * 3;
    int topLeftCaseY = (int)(lineY / 3) * 3;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            Case& currentCase = m_cases.at((topLeftCaseX+i)*m_sizeX + (topLeftCaseY+j));
            currentCase.addConstraint(value);
        }
    }

}

Case Carte::getMinimalRemainingValue() {
    int minimalRemaining = INT_MAX;
    Case minimalRemaningValue = m_cases.at(0);

    for(Case& currentCase : m_cases) {
        if(currentCase.getValue()==0) {
            int remainingPossibilities = currentCase.getNumberOfPossiblities();
            if(remainingPossibilities<minimalRemaining) {
                minimalRemaining = remainingPossibilities;
                minimalRemaningValue = currentCase;
            }
        }

    }

    return minimalRemaningValue;
}

//Arc consistency algorithm
void Carte::ac3() {
    Case currentCase = getMinimalRemainingValue();

    bool valueFound = false;

    int value=1;
    while(!valueFound && value < 10) {
        if(currentCase.isValuePossible(value)) {
            //TODO: Add the constraint and see if one of the neighbors cases have 0 possible value
            currentCase.setValue(value);
            currentCase.addConstraint(value);
            valueFound = true;
        }
        value++;
    }
}