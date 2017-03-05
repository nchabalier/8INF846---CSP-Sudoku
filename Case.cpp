//
// Created by Aburam on 04/02/17.
//

#include "Case.h"

Case::Case(int x, int y) {
    m_x = x;
    m_y = y;
}

Case::Case(int x, int y, int value) {
    m_x = x;
    m_y = y;
    m_value = value;
    m_constraint.push_back(value);
}

Case::~Case() {
}

/*Case::Case(const Case &copyCase) {
    //cout << "Case copy constructor" << endl;
    m_x = copyCase.m_x;
    m_y = copyCase.m_y;
}*/

int Case::getPositionX() const {
    return m_x;
}

int Case::getPositionY() const {
    return m_y;
}

int Case::getValue() const {
    return m_value;
}

void Case::addConstraint(int value) {
    if(value != 0) {
        if(std::find(m_constraint.begin(), m_constraint.end(), value) == m_constraint.end()) {
            m_constraint.push_back(value);
        }
    }
}

void Case::setValue(int value) {
    m_value = value;
}

int Case::getNumberOfPossiblities() const {
    return 9-m_constraint.size();
}

bool Case::isValuePossible(int value) const {
    return std::find(m_constraint.begin(), m_constraint.end(), value) == m_constraint.end();
}

std::vector<int> Case::getConstraints() const {
    return m_constraint;
}