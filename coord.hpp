#ifndef __COORDS_HPP__
#define __COORDS_HPP__

#include <iostream>


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
        int get_x_val() { return x_val; };
        int get_y_val() { return y_val; };
        Coord operator+(const Coord &c);
        Coord operator-(const Coord &c);
        void set_coord(int x, int y);
        // math operators are AND for both elements
        Coord operator+(int a);
        Coord operator-(int a);        
        // math operators for one element
        Coord add_x(int a);
        Coord add_y(int a);
        // math operator for diagonals
        Coord inverse_slope(int a);
        // relational operators are OR for either x or y
        bool operator<(const Coord &c);
        bool operator>(const Coord &c);
        // relation comparisons with input data
        bool in_bounds(int x, int y);
        // relation comparisons to OTHER coordinates
        bool in_x(const Coord &c);
        bool in_y(const Coord &c);
        bool in_neg_slope_high(const Coord &c);
        bool in_neg_slope_low(const Coord &c);
        int distance_from(const Coord &c);
        
        friend std::istream& operator>> (std::istream& in, Coord &c);
        friend std::ostream& operator<< (std::ostream& out, const Coord &c);

    private:
        int x_val;
        int y_val;
        bool bounded;
};

#endif