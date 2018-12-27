#ifndef __RULES_HPP__
#define __RULES_HPP__

#include "coord.hpp"
#include <vector>

std::vector<Coord> get_pawn_rules(int move);
std::vector<Coord> get_rook_rules();
std::vector<Coord> get_knight_rules();
std::vector<Coord> get_bishop_rules();
std::vector<Coord> get_queen_rules();
std::vector<Coord> get_king_rules();

#endif