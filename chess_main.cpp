#include <array>
#include <list>
#include <memory>
#include <iostream>

#include "chess_pieces.hpp"

namespace Chess
{
    board_t p_arr_board;
    void init_new_game();
    bool move_piece(const coord_t & in_from, const coord_t & in_to);
}

int main()
{
    Chess::init_new_game();

    Chess::list_t move_test = Chess::p_arr_board[3][6]->get_move_list();
    bool b_move_success = Chess::move_piece({3, 6}, {3, 4});

    std::cout << (b_move_success ? "Move successful" : "Move failed") << std::endl;

    if (b_move_success) { move_test = Chess::p_arr_board[3][4]->get_move_list(); }
    std::cout << Chess::p_arr_board[3][4]->get_move_count() << std::endl;

    for (int col = 0; col < 8; col++) {
        for (int row = 0; row < 8; row++) {
            std::cout << "|";
            Chess::coord_t test_pair{ col, row };
            if (std::find(move_test.begin(), move_test.end(), test_pair) != move_test.end() ) {
                std::cout << "*";
            }
            else {
                std::cout << " ";
            }
            if (Chess::p_arr_board[row][col]) {
                std::cout << Chess::p_arr_board[row][col]->get_type();
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    return 0;
}

void Chess::init_new_game()
{   
    //Erase all pieces
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            p_arr_board[i][j] = nullptr;
        }
    }
    // Set up new game pieces
    p_arr_board[0][0] = std::make_unique<Rook  > (1, coord_t{0, 0} );
    p_arr_board[1][0] = std::make_unique<Knight> (1, coord_t{1, 0} );
    p_arr_board[2][0] = std::make_unique<Bishop> (1, coord_t{2, 0} );
    p_arr_board[3][0] = std::make_unique<Queen > (1, coord_t{3, 0} );
    p_arr_board[4][0] = std::make_unique<King  > (1, coord_t{4, 0} );
    p_arr_board[5][0] = std::make_unique<Bishop> (1, coord_t{5, 0} );
    p_arr_board[6][0] = std::make_unique<Knight> (1, coord_t{6, 0} );
    p_arr_board[7][0] = std::make_unique<Rook  > (1, coord_t{7, 0} );
    p_arr_board[0][1] = std::make_unique<Pawn  > (1, coord_t{0, 1} );
    p_arr_board[1][1] = std::make_unique<Pawn  > (1, coord_t{1, 1} );
    p_arr_board[2][1] = std::make_unique<Pawn  > (1, coord_t{2, 1} );
    p_arr_board[3][1] = std::make_unique<Pawn  > (1, coord_t{3, 1} );
    p_arr_board[4][1] = std::make_unique<Pawn  > (1, coord_t{4, 1} );
    p_arr_board[5][1] = std::make_unique<Pawn  > (1, coord_t{5, 1} );
    p_arr_board[6][1] = std::make_unique<Pawn  > (1, coord_t{6, 1} );
    p_arr_board[7][1] = std::make_unique<Pawn  > (1, coord_t{7, 1} );
    p_arr_board[0][6] = std::make_unique<Pawn  > (2, coord_t{0, 6} );
    p_arr_board[1][6] = std::make_unique<Pawn  > (2, coord_t{1, 6} );
    p_arr_board[2][6] = std::make_unique<Pawn  > (2, coord_t{2, 6} );
    p_arr_board[3][6] = std::make_unique<Pawn  > (2, coord_t{3, 6} );
    p_arr_board[4][6] = std::make_unique<Pawn  > (2, coord_t{4, 6} );
    p_arr_board[5][6] = std::make_unique<Pawn  > (2, coord_t{5, 6} );
    p_arr_board[6][6] = std::make_unique<Pawn  > (2, coord_t{6, 6} );
    p_arr_board[7][6] = std::make_unique<Pawn  > (2, coord_t{7, 6} );
    p_arr_board[0][7] = std::make_unique<Rook  > (2, coord_t{0, 7} );
    p_arr_board[1][7] = std::make_unique<Knight> (2, coord_t{1, 7} );
    p_arr_board[2][7] = std::make_unique<Bishop> (2, coord_t{2, 7} );
    p_arr_board[3][7] = std::make_unique<Queen > (2, coord_t{3, 7} );
    p_arr_board[4][7] = std::make_unique<King  > (2, coord_t{4, 7} );
    p_arr_board[5][7] = std::make_unique<Bishop> (2, coord_t{5, 7} );
    p_arr_board[6][7] = std::make_unique<Knight> (2, coord_t{6, 7} );
    p_arr_board[7][7] = std::make_unique<Rook  > (2, coord_t{7, 7} );
}

bool Chess::move_piece(const coord_t & in_from, const coord_t & in_to)
{
    bool b_retval = false;
    if (p_arr_board[in_from.first][in_from.second]) {
        if (p_arr_board[in_from.first][in_from.second]->move_to(in_to)) {
            p_arr_board[in_to.first][in_to.second] = std::move(p_arr_board[in_from.first][in_from.second]);
            p_arr_board[in_from.first][in_from.second] = nullptr;
            b_retval = true;
        }
    }
    return b_retval;
}