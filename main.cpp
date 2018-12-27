#include "coord.hpp"
#include "rules.hpp"
#include <iostream>

int Coord::x_min = 1;
int Coord::x_max = 8;
int Coord::y_min = 1;
int Coord::y_max = 8;

struct Board
{
    
};


int main()
{
    Coord c1(-1, -1);
    std::cout << c1 << std::endl;

    std::vector<Coord> test = get_queen_rules();
    for (auto i : test)
        std::cout << i << std::endl;
    return 0;
}