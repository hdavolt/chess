#include "coord.hpp"
#include "chess_pieces.hpp"
#include "chess_exceptions.hpp"
#include <iostream>
#include <vector>

int Coord::x_min = 0;
int Coord::x_max = 7;
int Coord::y_min = 0;
int Coord::y_max = 7;


int main()
{
    Coord c1(5, 1);
    Coord c2(0, 4);
    std::cout << c1 << std::endl;

    int pl = 1;

    Queen q1(c1, pl);
    
    try {
        q1.move(c2);
    }
    catch (Invalid_move &move) {
        std::cerr << "Invalid move!" << std::endl;
    }
    
    for (int j = 7; j >= 0; j--) {
        std::cout << "------------------------" << std::endl;
        for (int i = 0; i < 8; i++) {
            Coord temp(i, j);
            bool found = false;
            std::cout << "|";
            for (Coord c : q1.get_moves()) {
                if (c == temp) {
                    std::cout << "* ";
                    found = true;
                }
            }
            if (q1.get_loc() == temp) {
                std::cout << "Q ";
                found = true;
            }
            if (!found)
                std::cout << "  ";
        }
        std::cout << std::endl;
    }

    return 0;
}