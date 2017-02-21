#ifndef INC_8INF846_TP1_CASE_H
#define INC_8INF846_TP1_CASE_H

#include "iostream"

using namespace std;


class Case {
    public :
    Case(int x, int y);
    Case(int x, int y, int value);
    //Case(const Case &copyCase);
    ~Case();

    int getPositionX() const;
    int getPositionY() const;





    friend ostream& operator<<(ostream& os, Case& c);
    friend bool operator==( const Case& lhs, const Case& rhs );
    friend bool operator!=( const Case& lhs, const Case& rhs );
    friend bool operator<( const Case& lhs, const Case& rhs );

private :
        int m_x;
        int m_y;
        int m_value;
};

inline ostream &operator<<( ostream &out, Case &c )
{
    out<< c.m_value;
    return out;
}

inline bool operator==( const Case& lhs, const Case& rhs )
{
if (lhs.getPositionX() == rhs.getPositionX() && lhs.getPositionY() == rhs.getPositionY() && lhs.m_value == rhs.m_value)
    return true;
return false;
}

inline bool operator!=( const Case& lhs, const Case& rhs )
{
    return !(lhs==rhs);
}

// This operator is used by the function find() of map
inline bool operator<( const Case& lhs, const Case& rhs )
{
    if(lhs.m_x < rhs.m_x) {
        return true;
    } else {
        if(lhs.m_x == rhs.m_x && lhs.m_y < rhs.m_y) {
            return true;
        }
    }
    return false;
}




#endif //INC_8INF846_TP1_CASE_H
