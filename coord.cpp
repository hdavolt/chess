#include "coord.hpp"
#include "chess_exceptions.hpp"
#include <algorithm> // For std::max

Coord::Coord(int x, int y, bool bd) 
{
    if (bd) {
        if (in_bounds(x, y)) {
            x_val = x;
            y_val = y;
        }
        else {
            throw Out_of_bounds();
        }
    }
    else {
        x_val = x;
        y_val = y;
    }
    bounded = bd;
}

void Coord::operator=(const Coord &c)
{
    if (bounded) {
        if (in_bounds(c.get_x(), c.get_y())) {
            x_val = c.get_x();
            y_val = c.get_y();
        }
    }
    else {
        x_val = c.x_val;
        y_val = c.y_val;
    }
}

bool Coord::set(int x, int y)
{
    bool res = false;
    if (bounded) {
        if (in_bounds(x, y)) {
            x_val = x;
            y_val = y;
            res = true;
        }
    }
    else {
        x_val = x;
        y_val = y;
        res = true;
    }
    return res;
}

bool Coord::move(int x, int y)
{
    bool res = false;
    if (bounded) {
        if (in_bounds(x_val + x, y_val + y)) {
            x_val += x;
            y_val += y;
            res = true;
        }
    }
    else {
        x_val += x;
        y_val += y;
        res = true;
    }
    return res;
}

Coord Coord::comp(const Coord &c) const
{
    Coord res(comp_x(c), comp_y(c), false);
    return res;
}

int Coord::distance(const Coord &c)
{
    return std::max(std::abs(c.x_val - x_val), std::abs(c.y_val - y_val));
}

std::istream& operator>>(std::istream& in, Coord &c)
{
    in >> c.x_val;
    in.ignore();
    in >> c.y_val;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Coord &c)
{
    out << c.x_val << " " << c.y_val;
    return out;
}

bool Coord::in_bounds(int x, int y)
{
    if (x >= std::abs(x_min) && x <= std::abs(x_max) &&
        y >= std::abs(y_min) && y <= std::abs(y_max))
        return true;
    else
        return false;
}