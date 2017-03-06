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
    while(currentCase!=0){

        if(removeInconsistentValues(*currentCase)){
            for(pair<Case, vector<int>>& caseCSP : csp){
                if(caseCSP.first == *currentCase){
                    caseCSP.second = currentCase->getConstraints();
                }

            }
        }
        else{
            //Si on ne réussit pas à rajouter de nouvelles valeurs on charge la carte où on devait choisir entre plusieurs possibilités
            while(m_saved_cases.back().second.size()<=1){
                //Si on ne peut pas tester de nouvelles valeurs, on revient plus en arrière
                m_saved_cases.pop_back();
            }
                //Une fois qu'on a trouvé une carte où il reste des valeurs à tester, on charge la carte
                m_saved_cases.back().second.erase(m_saved_cases.back().second.begin());
                m_cases = m_saved_cases.back().first;
        }
        cout << "NOUVEAU TOUR : CASE : " << currentCase->getPositionX() << ", " << currentCase->getPositionY() << " : " << *currentCase << endl;
        cout << *this << endl;
        currentCase = getMinimalRemainingValue();


    }

    return csp;
}

bool Carte::removeInconsistentValues(Case & currentCase) {
    if(&currentCase != nullptr) {
        vector<int> possibleValues;
        bool valueFound = false;
        int value=1;
        while(!valueFound && value < 10) {

            if(currentCase.isValuePossible(value)) {
                possibleValues.push_back(value);
            }

            value++;
        }
        //On verifie le nombre de possibilité
        if(possibleValues.size() > 1) {
            //Si il ya plusieurs possibilités, on choisis le cas suivant en cas de chargement réussi ou on sauvegarde la carte
            if (m_saved_cases.size() > 0 && m_saved_cases.back().first == this->getCases()) {
                currentCase.setValue(m_saved_cases.back().second.front());
                updateConstraint(currentCase);
            } else {
                //on sauvegarde la map
                m_saved_cases.push_back(make_pair(m_cases, possibleValues));

                currentCase.setValue(possibleValues.front());
                updateConstraint(currentCase);

            }

            return true;
        }
        else if(possibleValues.size() == 1){
            //Si il n'y a qu'une seule possibilité on met la valeur directement
            currentCase.setValue(possibleValues[0]);
            updateConstraint(currentCase);
            return true;
        }

    }
    return false;
}
