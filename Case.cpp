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