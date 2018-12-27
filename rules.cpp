#include "rules.hpp"

std::vector<Coord> get_pawn_rules(int move)
{
    std::vector<Coord> rules;
    switch(move)
    {
        case 0:
            rules.push_back(Coord(0, 2));
            rules.push_back(Coord(0,-2));
        default:
            rules.push_back(Coord(0, 1));
            rules.push_back(Coord(0, -1));
            rules.push_back(Coord(-1, 1));
            rules.push_back(Coord(-1, -1));
            rules.push_back(Coord(1, 1));
            rules.push_back(Coord(1, -1));
    }
    return rules;
}

std::vector<Coord> get_rook_rules()
{
    std::vector<Coord> rules;
    for (int i = 1; i < 8; i++)
    {
        rules.push_back(Coord(0, i));
        rules.push_back(Coord(0, i / -1));
        rules.push_back(Coord(i, 0));
        rules.push_back(Coord(i / -1, 0));
    }
    return rules;
}

std::vector<Coord> get_knight_rules()
{
    std::vector<Coord> rules;
    rules.push_back(Coord(1, 2));
    rules.push_back(Coord(1, -2));
    rules.push_back(Coord(2, 1));
    rules.push_back(Coord(2, -1));
    rules.push_back(Coord(-1, 2));
    rules.push_back(Coord(-1, -2));
    rules.push_back(Coord(-2, 1));
    rules.push_back(Coord(-2, -1));
    return rules;
}

std::vector<Coord> get_bishop_rules()
{
    std::vector<Coord> rules;
    for (int i = 1; i < 8; i++)
    {
        rules.push_back(Coord(i, i));
        rules.push_back(Coord(i / -1, i / -1));
        rules.push_back(Coord(i, i / -1));
        rules.push_back(Coord(i / -1, i));
    }
    return rules;
}

std::vector<Coord> get_queen_rules()
{
    std::vector<Coord> rules;
    for (int i = 1; i < 8; i++)
    {
        rules.push_back(Coord(0, i));
        rules.push_back(Coord(0, i / -1));
        rules.push_back(Coord(i, 0));
        rules.push_back(Coord(i / -1, 0));
        rules.push_back(Coord(i, i));
        rules.push_back(Coord(i / -1, i / -1));
        rules.push_back(Coord(i, i / -1));
        rules.push_back(Coord(i / -1, i));
    }
    return rules;
}

std::vector<Coord> get_king_rules()
{
    std::vector<Coord> rules;
    rules.push_back(Coord(1, 1));
    rules.push_back(Coord(1, 0));
    rules.push_back(Coord(1, -1));
    rules.push_back(Coord(0, 1));
    rules.push_back(Coord(0, -1));
    rules.push_back(Coord(-1, 1));
    rules.push_back(Coord(-1, 0));
    rules.push_back(Coord(-1, -1));
    return rules;
}