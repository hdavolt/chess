#include "coord.hpp"
#include "chess_exceptions.hpp"
#include <cmath>
#include <algorithm>

Coord::Coord(int x, int y, bool in) 
{
    switch(in)
    {
        case true:
            if (in_bounds(x, y)) {
                x_val = x;
                y_val = y;
                bounds = true;
            }
            else {
                throw Out_of_bounds();
            }
        default:
            x_val = x;
            y_val = y;
            bounds = false;
    }
}

Coord Coord::operator+(const Coord &c)
{
    Coord temp(x_val + c.x_val, y_val + c.y_val, c.bounds);
    
    return temp;
}

Coord Coord::operator-(const Coord &c)
{
    Coord temp(x_val - c.x_val, y_val - c.y_val, c.bounds);
    return temp;
}

void Coord::set_coord(int x, int y)
{
    if (in_bounds(x, y)) {
        x_val = x;
        y_val = y;
    }
    else {
        throw Out_of_bounds();
    }
}

Coord Coord::operator+(int a)
{
    Coord temp(x_val + a, y_val + a);
    return temp;
}

Coord Coord::operator-(int a)
{
    Coord temp(x_val - a, y_val - a);
    return temp;
}

Coord Coord::add_x(int a)
{
    Coord temp(x_val + a, y_val);
    return temp;
}

Coord Coord::add_y(int a)
{
    Coord temp(x_val, y_val + a);
    return temp;
}

Coord Coord::inverse_slope(int a)
{
    Coord temp(x_val + a, y_val - a);
    return temp;
}

bool Coord::operator<(const Coord &c)
{
    if (c.x_val < x_val || c.y_val < y_val)
        return true;
    else
        return false;
}
bool Coord::operator>(const Coord &c)
{
    if (c.x_val > x_val || c.y_val > y_val)
        return true;
    else
        return false;
}

bool Coord::in_bounds(int x, int y)
{
    if (x >= std::abs(x_min) && x <= std::abs(x_max) &&
        y >= std::abs(y_min) && y <= std::abs(y_max))
        return true;
    else
        return false;
}

bool Coord::in_x(const Coord &c)
{
    if (c.x_val == x_val)
        return true;
    else
        return false;
}

bool Coord::in_y(const Coord &c)
{
    if (c.y_val == y_val)
        return true;
    else
        return false;
}

bool Coord::in_neg_slope_high(const Coord &c)
{
    if (c.x_val < x_val && c.y_val > y_val)
        return true;
    else
        return false;
}
bool Coord::in_neg_slope_low(const Coord &c)
{
    if (c.x_val > x_val && c.y_val < y_val)
        return true;
    else
        return false;
}

int Coord::distance_from(const Coord &c)
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