#include <array>
#include <list>
#include <memory>
#include <iostream>

#include "chess_pieces.hpp"

namespace Chess
{
    class Piece; //Forward declaration: Pieces are defined in chess_pieces
    std::array<std::unique_ptr<Piece>, 64> p_arr_board;
    void init_new_game();
    bool move_piece(const int in_from, const int in_to);
    //Functors for use in comparisons with other pieces
}

int main()
{
    Chess::init_new_game();

    std::list<int> move_test = Chess::p_arr_board[10]->calc_avail_moves();

    for (int i = 0; i < 8; i++) {
        std::cout << "--";
    }
    std::cout << std::endl;
    for (int i = 0; i < 64; i++) {
        if (i > 0 && i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << "|";
        if (Chess::p_arr_board[i]) {
            std::cout << Chess::p_arr_board[i]->get_type();
        }
        else if (std::find(move_test.begin(), move_test.end(), i) != move_test.end()) {
            std::cout << "*";
        }
        else {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    for (int i = 0; i < 8; i++) {
        std::cout << "--";
    }
    std::cout << std::endl;
    return 0;
}

void Chess::init_new_game()
{    //Erase all pieces
    for (int p = 0; p < 64; p++) {
        p_arr_board[p] = nullptr;
    }
    // Set up new game pieces
    p_arr_board[ 0] = std::make_unique<Rook  > (1,  0);
    p_arr_board[ 1] = std::make_unique<Knight> (1,  1);
    p_arr_board[ 2] = std::make_unique<Bishop> (1,  2);
    p_arr_board[ 3] = std::make_unique<Queen > (1,  3);
    p_arr_board[ 4] = std::make_unique<King  > (1,  4);
    p_arr_board[ 5] = std::make_unique<Bishop> (1,  5);
    p_arr_board[ 6] = std::make_unique<Knight> (1,  6);
    p_arr_board[ 7] = std::make_unique<Rook  > (1,  7);
    p_arr_board[ 8] = std::make_unique<Pawn  > (1,  8);
    p_arr_board[ 9] = std::make_unique<Pawn  > (1,  9);
    p_arr_board[10] = std::make_unique<Pawn  > (1, 10);
    p_arr_board[11] = std::make_unique<Pawn  > (1, 11);
    p_arr_board[12] = std::make_unique<Pawn  > (1, 12);
    p_arr_board[13] = std::make_unique<Pawn  > (1, 13);
    p_arr_board[14] = std::make_unique<Pawn  > (1, 14);
    p_arr_board[15] = std::make_unique<Pawn  > (1, 15);
    p_arr_board[48] = std::make_unique<Pawn  > (2, 48);
    p_arr_board[49] = std::make_unique<Pawn  > (2, 49);
    p_arr_board[50] = std::make_unique<Pawn  > (2, 50);
    p_arr_board[51] = std::make_unique<Pawn  > (2, 51);
    p_arr_board[52] = std::make_unique<Pawn  > (2, 52);
    p_arr_board[53] = std::make_unique<Pawn  > (2, 53);
    p_arr_board[54] = std::make_unique<Pawn  > (2, 54);
    p_arr_board[55] = std::make_unique<Pawn  > (2, 55);
    p_arr_board[56] = std::make_unique<Rook  > (2, 56);
    p_arr_board[57] = std::make_unique<Knight> (2, 57);
    p_arr_board[58] = std::make_unique<Bishop> (2, 58);
    p_arr_board[59] = std::make_unique<Queen > (2, 59);
    p_arr_board[60] = std::make_unique<King  > (2, 60);
    p_arr_board[61] = std::make_unique<Bishop> (2, 61);
    p_arr_board[62] = std::make_unique<Knight> (2, 62);
    p_arr_board[63] = std::make_unique<Rook  > (2, 63);
}

bool Chess::move_piece(const int in_from, const int in_to)
{
    return true;
}