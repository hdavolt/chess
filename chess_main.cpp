#include <array>
#include <list>
#include <memory>
#include <iostream>

#include "chess_pieces.hpp"

namespace Chess
{
    class Piece; //Forward declaration: Pieces are defined in chess_pieces
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> p_arr_board;
    void init_new_game();
    bool move_piece(const int in_from, const int in_to);
    //Functors for use in comparisons with other pieces
}

int main()
{
    //Chess::init_new_game();
    //Erase all pieces
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Chess::p_arr_board[i][j] = nullptr;
        }
    }

    Chess::p_arr_board[4][4] = std::make_unique<Chess::King>(2, Chess::pair_t{4, 4});
    //Chess::p_arr_board[2][3] = std::make_unique<Chess::Pawn>(2, Chess::pair_t{4, 2});

    Chess::list_t move_test = Chess::p_arr_board[4][4]->calc_avail_moves();

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            std::cout << "|";
            Chess::pair_t test_pair{ row, col };
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
    p_arr_board[0][0] = std::make_unique<Rook  > (1, pair_t{0, 0} );
    p_arr_board[0][1] = std::make_unique<Knight> (1, pair_t{0, 1} );
    p_arr_board[0][2] = std::make_unique<Bishop> (1, pair_t{0, 2} );
    p_arr_board[0][3] = std::make_unique<Queen > (1, pair_t{0, 3} );
    p_arr_board[0][4] = std::make_unique<King  > (1, pair_t{0, 4} );
    p_arr_board[0][5] = std::make_unique<Bishop> (1, pair_t{0, 5} );
    p_arr_board[0][6] = std::make_unique<Knight> (1, pair_t{0, 6} );
    p_arr_board[0][7] = std::make_unique<Rook  > (1, pair_t{0, 7} );
    p_arr_board[1][0] = std::make_unique<Pawn  > (1, pair_t{1, 0} );
    p_arr_board[1][1] = std::make_unique<Pawn  > (1, pair_t{1, 1} );
    p_arr_board[1][2] = std::make_unique<Pawn  > (1, pair_t{1, 2} );
    p_arr_board[1][3] = std::make_unique<Pawn  > (1, pair_t{1, 3} );
    p_arr_board[1][4] = std::make_unique<Pawn  > (1, pair_t{1, 4} );
    p_arr_board[1][5] = std::make_unique<Pawn  > (1, pair_t{1, 5} );
    p_arr_board[1][6] = std::make_unique<Pawn  > (1, pair_t{1, 6} );
    p_arr_board[1][7] = std::make_unique<Pawn  > (1, pair_t{1, 7} );
    p_arr_board[6][0] = std::make_unique<Pawn  > (2, pair_t{6, 0} );
    p_arr_board[6][1] = std::make_unique<Pawn  > (2, pair_t{6, 1} );
    p_arr_board[6][2] = std::make_unique<Pawn  > (2, pair_t{6, 2} );
    p_arr_board[6][3] = std::make_unique<Pawn  > (2, pair_t{6, 3} );
    p_arr_board[6][4] = std::make_unique<Pawn  > (2, pair_t{6, 4} );
    p_arr_board[6][5] = std::make_unique<Pawn  > (2, pair_t{6, 5} );
    p_arr_board[6][6] = std::make_unique<Pawn  > (2, pair_t{6, 6} );
    p_arr_board[6][7] = std::make_unique<Pawn  > (2, pair_t{6, 7} );
    p_arr_board[7][0] = std::make_unique<Rook  > (2, pair_t{7, 0} );
    p_arr_board[7][1] = std::make_unique<Knight> (2, pair_t{7, 1} );
    p_arr_board[7][2] = std::make_unique<Bishop> (2, pair_t{7, 2} );
    p_arr_board[7][3] = std::make_unique<Queen > (2, pair_t{7, 3} );
    p_arr_board[7][4] = std::make_unique<King  > (2, pair_t{7, 4} );
    p_arr_board[7][5] = std::make_unique<Bishop> (2, pair_t{7, 5} );
    p_arr_board[7][6] = std::make_unique<Knight> (2, pair_t{7, 6} );
    p_arr_board[7][7] = std::make_unique<Rook  > (2, pair_t{7, 7} );
}

bool Chess::move_piece(const int in_from, const int in_to)
{
    return true;
}