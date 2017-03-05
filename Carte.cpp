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
        int posY = 0;
        for (char c : line) {
            Case &currentCase = m_cases.at(posX * m_sizeX + posY);
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

    //Update 3x3 constraint
    int topLeftCaseX = (int)(lineX / 3) * 3;
    int topLeftCaseY = (int)(lineY / 3) * 3;
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            Case& currentCase = m_cases.at((topLeftCaseX+i)*m_sizeX + (topLeftCaseY+j));
            currentCase.addConstraint(value);
        }
    }

}

Case* Carte::getMinimalRemainingValue() {
    int minimalRemaining = INT8_MAX;
    Case* minimalRemaningValue = nullptr;

    for(Case& currentCase : m_cases) {
        if(currentCase.getValue()==0) {
            int remainingPossibilities = currentCase.getNumberOfPossiblities();
            if(remainingPossibilities<minimalRemaining) {
                minimalRemaining = remainingPossibilities;
                minimalRemaningValue = &currentCase;
            }
        }

    }

    return minimalRemaningValue;
}

//Arc consistency algorithm
bool Carte::ac3() {
    Case* currentCase = getMinimalRemainingValue();
    if(currentCase != nullptr) {
        bool valueFound = false;

        int value=1;
        while(!valueFound && value < 10) {
            if(currentCase->isValuePossible(value)) {
                //TODO: Add the constraint and see if one of the neighbors cases have 0 possible value

                currentCase->setValue(value);
                updateConstraint(*currentCase);
                valueFound = true;
            }
            value++;
        }
        return true;
    }

    return false;
}

vector<pair<Case, vector<int>>> Carte::ac3(vector<pair<Case, vector<int>>> csp){
    Case* currentCase = getMinimalRemainingValue();

    while(currentCase!= nullptr){

        if(removeInconsistentValues(*currentCase)){
            for(pair<Case, vector<int>>& caseCSP : csp){
                if(caseCSP.first == *currentCase){
                    caseCSP.second = currentCase->getConstraints();
                }
            }
        }
        currentCase = getMinimalRemainingValue();

    }
    return csp;
}

bool Carte::removeInconsistentValues(Case & currentCase) {
    if(&currentCase != nullptr) {
        bool valueFound = false;
        int value=1;
        while(!valueFound && value < 10) {
            if(currentCase.isValuePossible(value)) {
                //TODO: Add the constraint and see if one of the neighbors cases have 0 possible value

                currentCase.setValue(value);
                updateConstraint(currentCase);
                //cout << "PositionX :" << currentCase.getPositionX() << ", PositionY : " << currentCase.getPositionY() << ", Valeur :" << currentCase.getValue() << endl;
                return true;
            }
            value++;
        }
    }

    return false;

}