#ifndef __COORDS_HPP__
#define __COORDS_HPP__
#define CONSOLE

#ifdef CONSOLE
#include <iostream>
#endif

class Coord 
{
    public:
    // Default bounds
    static int x_min;
    static int x_max;
    static int y_min;
    static int y_max;
    Coord() { x_val = x_min, y_val = y_min; bounded = true; };
    // Regular constructor, passing false for third value will ignore bounds
    Coord(int x, int y, bool bd = true);
    const int & get_x() const { return x_val; };
    const int & get_y() const { return y_val; };
    bool operator==(const Coord &c) const { return c.get_x() == x_val && c.get_y() == y_val; };
    void operator=(const Coord &c);
    bool set(int x, int y);
    // Relative set
    bool move(int x, int y);
    // relation comparisons to OTHER coordinates
    int comp_x(const Coord &c) const { return c.get_x() - x_val; };
    int comp_y(const Coord &c) const { return c.get_y() - y_val; };
    Coord comp(const Coord &c) const;
    int distance(const Coord &c);
    #ifdef CONSOLE
    friend std::istream& operator>> (std::istream& in, Coord &c);
    friend std::ostream& operator<< (std::ostream& out, const Coord &c);
    #endif
    
    private:
    int x_val;
    int y_val;
    bool bounded;
    bool in_bounds(int x, int y);
};

#endif