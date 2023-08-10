#ifndef POSITION_H
#define POSITION_H

#include "string"
#include <map>
#include <vector>

class Position
{
public:
    Position(int x = 0, int y = 0, int z = 0);
    int X();
    int Y();
    int Z();
    void X(int value);
    void Y(int value);
    void Z(int value);
    std::string ToString();
    bool operator==(const Position &other) const;
    bool operator!=(const Position &other) const;
    bool operator<(const Position& other) const; // Declaração do operador <

    uint32_t getDistance(Position p)
    {
        int distX = (X()) - (p.X());
        int distY = (Y()) - (p.Y());

        double result = sqrt(pow(distX, 2) + pow(distY, 2));
        return (int)result;
    }
private:
    int m_X;
    int m_Y;
    int m_Z;
};

#endif // POSITION_H
