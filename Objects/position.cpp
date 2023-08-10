#include "position.h"
#include "string"

Position::Position(int x, int y, int z)
{
    m_X = x;
    m_Y = y;
    m_Z = z;
}

int Position::X()
{
    return m_X;
}

int Position::Y()
{
    return m_Y;
}

int Position::Z()
{
    return m_Z;
}

void Position::X(int value)
{
    m_X = value;
}

void Position::Y(int value)
{
    m_Y = value;
}

void Position::Z(int value)
{
    m_Z = value;
}

std::string Position::ToString()
{
    return "X: " + std::to_string(X()) + " Y: " + std::to_string(Y()) + " Z: " + std::to_string(Z());
}

bool Position::operator==(const Position& other) const
{
    return (m_X == other.m_X) && (m_Y == other.m_Y) && (m_Z == other.m_Z);
}

bool Position::operator!=(const Position& other) const
{
    return (m_X != other.m_X) || (m_Y != other.m_Y) || (m_Z != other.m_Z);
}

bool Position::operator<(const Position &other) const
{
    if (m_X < other.m_X)
        return true;
    if (m_X > other.m_X)
        return false;

    if (m_Y < other.m_Y)
        return true;
    if (m_Y > other.m_Y)
        return false;

    return (m_Z < other.m_Z);
}
