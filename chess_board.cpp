#include "chess_board.hpp"

Board::Board() 
{   
    board_map[Coord(0,0)] = std::unique_ptr<Piece>(new Rook(1));
    board_map[Coord(1,0)] = std::unique_ptr<Piece>(new Knight(1));
    board_map[Coord(2,0)] = std::unique_ptr<Piece>(new Bishop(1));
    board_map[Coord(3,0)] = std::unique_ptr<Piece>(new Queen(1));
    board_map[Coord(4,0)] = std::unique_ptr<Piece>(new King(1));
    board_map[Coord(5,0)] = std::unique_ptr<Piece>(new Bishop(1));
    board_map[Coord(6,0)] = std::unique_ptr<Piece>(new Knight(1));
    board_map[Coord(7,0)] = std::unique_ptr<Piece>(new Rook(1));
    board_map[Coord(0,1)] = std::unique_ptr<Piece>(new Pawn(1));
    board_map[Coord(1,1)] = std::unique_ptr<Piece>(new Pawn(1));
    board_map[Coord(2,1)] = std::unique_ptr<Piece>(new Pawn(1));
    board_map[Coord(3,1)] = std::unique_ptr<Piece>(new Pawn(1));
    board_map[Coord(4,1)] = std::unique_ptr<Piece>(new Pawn(1));
    board_map[Coord(5,1)] = std::unique_ptr<Piece>(new Pawn(1));
    board_map[Coord(6,1)] = std::unique_ptr<Piece>(new Pawn(1));
    board_map[Coord(7,1)] = std::unique_ptr<Piece>(new Pawn(1));
    board_map[Coord(0,6)] = std::unique_ptr<Piece>(new Pawn(2));
    board_map[Coord(1,6)] = std::unique_ptr<Piece>(new Pawn(2));
    board_map[Coord(2,6)] = std::unique_ptr<Piece>(new Pawn(2));
    board_map[Coord(3,6)] = std::unique_ptr<Piece>(new Pawn(2));
    board_map[Coord(4,6)] = std::unique_ptr<Piece>(new Pawn(2));
    board_map[Coord(5,6)] = std::unique_ptr<Piece>(new Pawn(2));
    board_map[Coord(6,6)] = std::unique_ptr<Piece>(new Pawn(2));
    board_map[Coord(7,6)] = std::unique_ptr<Piece>(new Pawn(2));
    board_map[Coord(0,7)] = std::unique_ptr<Piece>(new Rook(2));
    board_map[Coord(1,7)] = std::unique_ptr<Piece>(new Knight(2));
    board_map[Coord(2,7)] = std::unique_ptr<Piece>(new Bishop(2));
    board_map[Coord(3,7)] = std::unique_ptr<Piece>(new Queen(2));
    board_map[Coord(4,7)] = std::unique_ptr<Piece>(new King(2));
    board_map[Coord(5,7)] = std::unique_ptr<Piece>(new Bishop(2));
    board_map[Coord(6,7)] = std::unique_ptr<Piece>(new Knight(2));
    board_map[Coord(7,7)] = std::unique_ptr<Piece>(new Rook(2));
}

void Board::move_piece(const Coord &c1, const Coord &c2)
{
    bool res = false;
    if (board_map.at(c1)) {
        board_map.at(c1)->calc_moves(c1);
        std::list<std::pair<Coord, int>> blockers_found;
        for (auto m : board_map.at(c1)->get_moves()) {
            if (board_map.at(m))
                blockers_found.emplace_back(std::make_pair(m, board_map.at(m)->get_player()));
        }
        board_map.at(c1)->remove_blocked(blockers_found);
        for (auto m : board_map.at(c1)->get_moves())
            if (c2 == m)
                res = true;
    }
    
    if (res) {
        
    }
    else {
        throw Invalid_move();
    }
}