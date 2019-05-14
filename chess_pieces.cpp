#define CONSOLE
//#define DEBUG

#include "chess_pieces.hpp"
#include "chess_exceptions.hpp"

void Piece::calc_moves(const Coord &c)
{
    moves.clear();
    for (Coord r : rules) {
        try {
            moves.push_back(Coord(c.get_x() + r.get_x(),
                                  c.get_y() + r.get_y()));
        }
        catch(Out_of_bounds &out) {
            // An out of bounds coordinate won't be created
            #ifdef DEBUG
            std::cout << "Out of bounds!" << std::endl;
            #endif
        }
    }
}

Pawn::Pawn(int pl, Coord l) : Piece(pl, l)
{
    if (player == 1) {
        rules.push_back(Coord( 0,  2, false));
        rules.push_back(Coord( 0,  1, false));
        rules.push_back(Coord(-1,  1, false));
        rules.push_back(Coord( 1,  1, false));
    }
    else if (player == 2) {
        rules.push_back(Coord( 0, -2, false));
        rules.push_back(Coord( 0, -1, false));
        rules.push_back(Coord(-1, -1, false));
        rules.push_back(Coord( 1, -1, false));
    }
}

void Pawn::remove_blocked(const std::list<std::pair<Coord, int>> &blocks)
{
    for (auto m : moves) {
        if (std::abs(m.comp_x(loc)) == 1)
    }
}

void Pawn::add_move()
{
    add_move();
    if (move_count == 1)
        pawn_update_rules();
}

void Pawn::pawn_update_rules()
{
    rules.clear();
    if (player == 1) {
        rules.push_back(Coord( 0,  1, false));
        rules.push_back(Coord(-1,  1, false));
        rules.push_back(Coord( 1,  1, false));
    }
    else if (player == 2) {
        rules.push_back(Coord( 0, -1, false));
        rules.push_back(Coord(-1, -1, false));
        rules.push_back(Coord( 1, -1, false));
    }
}

Rook::Rook(int pl, Coord l) : Piece(pl, l)
{
    for (int i = 1; i < 8; i++) {
        rules.push_back(Coord( 0     , i     , false));
        rules.push_back(Coord( 0     , i / -1, false));
        rules.push_back(Coord( i     , 0     , false));
        rules.push_back(Coord( i / -1, 0     , false));
    }
}

Knight::Knight(int pl, Coord l) : Piece(pl, l)
{
    rules.push_back(Coord( 1,  2, false));
    rules.push_back(Coord( 1, -2, false));
    rules.push_back(Coord( 2,  1, false));
    rules.push_back(Coord( 2, -1, false));
    rules.push_back(Coord(-1,  2, false));
    rules.push_back(Coord(-1, -2, false));
    rules.push_back(Coord(-2,  1, false));
    rules.push_back(Coord(-2, -1, false));
}

Bishop::Bishop(int pl, Coord l) : Piece(pl, l)
{
    for (int i = 1; i < 8; i++) {
        rules.push_back(Coord( i     , i     , false));
        rules.push_back(Coord( i / -1, i / -1, false));
        rules.push_back(Coord( i     , i / -1, false));
        rules.push_back(Coord( i / -1, i     , false));
    }
}

Queen::Queen(int pl, Coord l) : Piece(pl, l)
{
    for (int i = 1; i < 8; i++) {
        rules.push_back(Coord( 0     , i     , false));
        rules.push_back(Coord( 0     , i / -1, false));
        rules.push_back(Coord( i     , 0     , false));
        rules.push_back(Coord( i / -1, 0     , false));
        rules.push_back(Coord( i     , i     , false));
        rules.push_back(Coord( i / -1, i / -1, false));
        rules.push_back(Coord( i     , i / -1, false));
        rules.push_back(Coord( i / -1, i     , false));
    }
}

King::King(int pl, Coord l) : Piece(pl, l)
{
    rules.push_back(Coord( 1,  1, false));
    rules.push_back(Coord( 1,  0, false));
    rules.push_back(Coord( 1, -1, false));
    rules.push_back(Coord( 0,  1, false));
    rules.push_back(Coord( 0, -1, false));
    rules.push_back(Coord(-1,  1, false));
    rules.push_back(Coord(-1,  0, false));
    rules.push_back(Coord(-1, -1, false));
}