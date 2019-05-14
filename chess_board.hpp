#ifndef __CHESS_BOARD_HPP__
#define __CHESS_BOARD_HPP__
#define CONSOLE
#define DEBUG

#include <map>
#include <memory>
#include "coord.hpp"
#include "chess_pieces.hpp"
#include "chess_exceptions.hpp"

class Board
{
public:
    Board();

    void move_piece(const Coord &c1, const Coord &c2);
private:
    std::map<Coord, std::unique_ptr<Piece>> board_map;
};


#endif