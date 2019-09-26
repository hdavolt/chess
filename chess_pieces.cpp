#include "chess_pieces.hpp"
#include <iostream>

using namespace Chess;

bool Piece::move_to(const coord_t & in_location)
{
    bool b_retval = false;
    calc_relative_moves();
    // Because a .contains() function would be too easy
    if (std::find(nl_act_moves.begin(), nl_act_moves.end(), in_location) != nl_act_moves.end()) {
        nl_move_history.push_front(n_location);
        n_location = in_location;
        n_move_count++;
        b_retval = true;
        calc_relative_moves();
    }
    return b_retval;
}

void Piece::calc_relative_moves()
{
    // Calculate relative moves based on current location, trim out of bounds
    nl_act_moves.clear();
    for (coord_t n_rel : nl_rel_moves) {
        coord_t n_move = n_location + n_rel;
        if (   n_move.first  >= 0 && n_move.first  < 8
            && n_move.second >= 0 && n_move.second < 8 ) {
            nl_act_moves.push_front(n_move);
        }
    }
    remove_blocked_moves();
}

Pawn::Pawn(const int in_player, const coord_t in_location) : Piece(in_player, in_location)
{
    n_value = 1;
    c_type = 'p';

    if (n_player == 1) {
        nl_rel_moves = { { 1, -1}, { 1,  0}, { 1,  1}, { 2,  0} };
    }
    else if (n_player == 2) {
        nl_rel_moves = { {-1, -1}, {-1,  0}, {-1,  1}, {-2,  0} };
    }
}

void Pawn::remove_blocked_moves()
{
    list_t nl_move_list = nl_act_moves;
    for (coord_t n_move : nl_move_list) {
        if (p_arr_board[n_move.first][n_move.second]) {
            if (   n_location.second == n_move.second 
                || p_arr_board[n_move.first][n_move.second]->get_player() == n_player) {
                nl_act_moves.remove(n_move);
            }
        }
        else if (n_location.second != n_move.second) {
            nl_act_moves.remove(n_move);
        }
        if (n_move_count == 1 && std::abs(n_move.first) == 2) {
            nl_act_moves.remove(n_move);
        }
    }
}

Rook::Rook(const int in_player, const coord_t in_location) : Piece(in_player, in_location)
{
    n_value = 5;
    c_type = 'r';
    
    for (int n = 1; n < 8; n++) {
        nl_rel_moves.push_front( { 0,  n} );
        nl_rel_moves.push_front( { 0, -n} );
        nl_rel_moves.push_front( { n,  0} );
        nl_rel_moves.push_front( {-n,  0} );
    }
}

void Rook::remove_blocked_moves()
{
    list_t nl_move_list = nl_act_moves;
    for (coord_t n_move : nl_move_list) {
        if (p_arr_board[n_move.first][n_move.second]) {
            b_Col_High test_col_high(n_location);
            b_Row_High test_row_high(n_location);
            b_Col_Low   test_col_low(n_location);
            b_Row_Low   test_row_low(n_location);

                 if (test_col_high(n_move)) { nl_act_moves.remove_if(b_Col_High(n_move)); }
            else if (test_row_high(n_move)) { nl_act_moves.remove_if(b_Row_High(n_move)); }
            else if ( test_col_low(n_move)) { nl_act_moves.remove_if( b_Col_Low(n_move)); }
            else if ( test_row_low(n_move)) { nl_act_moves.remove_if( b_Row_Low(n_move)); }

            if (p_arr_board[n_move.first][n_move.second]->get_player() == n_player) { nl_act_moves.remove(n_move); }
        }
    }
}

Knight::Knight(const int in_player, const coord_t in_location) : Piece(in_player, in_location)
{
    n_value = 3;
    c_type = 'n';

    nl_rel_moves = { {-1, -2}, {-2, -1}, {-2,  1}, {-1,  2},
                     { 1, -2}, { 2, -1}, { 2,  1}, { 1,  2} };
}

void Knight::remove_blocked_moves()
{
    list_t nl_move_list = nl_act_moves;
    for (coord_t n_move : nl_move_list) {
        if (p_arr_board[n_move.first][n_move.second]) {
            if (p_arr_board[n_move.first][n_move.second]->get_player() == n_player) {
                nl_act_moves.remove(n_move);
            }
        }
    }
}

Bishop::Bishop(const int in_player, const coord_t in_location) : Piece(in_player, in_location)
{
    n_value = 3;
    c_type = 'b';
    
    for (int n = 1; n < 8; n++) {
        nl_rel_moves.push_front( { n,  n} );
        nl_rel_moves.push_front( {-n, -n} );
        nl_rel_moves.push_front( { n, -n} );
        nl_rel_moves.push_front( {-n,  n} );
    }
}

void Bishop::remove_blocked_moves()
{
    list_t nl_move_list = nl_act_moves;
    for (coord_t n_move : nl_move_list) {
        if (p_arr_board[n_move.first][n_move.second]) {
            b_Pos_Slope_High test_pos_slope_high(n_location);
            b_Pos_Slope_Low   test_pos_slope_low(n_location);
            b_Neg_Slope_High test_neg_slope_high(n_location);
            b_Neg_Slope_Low   test_neg_slope_low(n_location);

                 if (test_pos_slope_high(n_move)) { nl_act_moves.remove_if(b_Pos_Slope_High(n_move)); }
            else if ( test_pos_slope_low(n_move)) { nl_act_moves.remove_if( b_Pos_Slope_Low(n_move)); }
            else if (test_neg_slope_high(n_move)) { nl_act_moves.remove_if(b_Neg_Slope_High(n_move)); }
            else if ( test_neg_slope_low(n_move)) { nl_act_moves.remove_if( b_Neg_Slope_Low(n_move)); }

            if (p_arr_board[n_move.first][n_move.second]->get_player() == n_player) { nl_act_moves.remove(n_move); }
        }
    }
}

Queen::Queen(const int in_player, const coord_t in_location) : Piece(in_player, in_location)
{
    n_value = 9;
    c_type = 'q';
    
    for (int n = 1; n < 8; n++) {
        nl_rel_moves.push_front( { 0,  n} );
        nl_rel_moves.push_front( { 0, -n} );
        nl_rel_moves.push_front( { n,  0} );
        nl_rel_moves.push_front( {-n,  0} );
        nl_rel_moves.push_front( { n,  n} );
        nl_rel_moves.push_front( {-n, -n} );
        nl_rel_moves.push_front( { n, -n} );
        nl_rel_moves.push_front( {-n,  n} );
    }
}

void Queen::remove_blocked_moves()
{
    list_t nl_move_list = nl_act_moves;
    for (auto n_move : nl_move_list) {
        if (p_arr_board[n_move.first][n_move.second]) {
            b_Col_High             test_col_high(n_location);
            b_Row_High             test_row_high(n_location);
            b_Col_Low               test_col_low(n_location);
            b_Row_Low               test_row_low(n_location);
            b_Pos_Slope_High test_pos_slope_high(n_location);
            b_Pos_Slope_Low   test_pos_slope_low(n_location);
            b_Neg_Slope_High test_neg_slope_high(n_location);
            b_Neg_Slope_Low   test_neg_slope_low(n_location);
            
                 if (      test_col_high(n_move)) { nl_act_moves.remove_if(      b_Col_High(n_move)); }
            else if (      test_row_high(n_move)) { nl_act_moves.remove_if(      b_Row_High(n_move)); }
            else if (       test_col_low(n_move)) { nl_act_moves.remove_if(       b_Col_Low(n_move)); }
            else if (       test_row_low(n_move)) { nl_act_moves.remove_if(       b_Row_Low(n_move)); }
            else if (test_pos_slope_high(n_move)) { nl_act_moves.remove_if(b_Pos_Slope_High(n_move)); }
            else if ( test_pos_slope_low(n_move)) { nl_act_moves.remove_if( b_Pos_Slope_Low(n_move)); }
            else if (test_neg_slope_high(n_move)) { nl_act_moves.remove_if(b_Neg_Slope_High(n_move)); }
            else if ( test_neg_slope_low(n_move)) { nl_act_moves.remove_if( b_Neg_Slope_Low(n_move)); }

            if (p_arr_board[n_move.first][n_move.second]->get_player() == n_player) { nl_act_moves.remove(n_move); }

        }
    }
}

King::King(const int in_player, const coord_t in_location) : Piece(in_player, in_location)
{
    n_value = 100;
    c_type = 'k';
    
    nl_rel_moves = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
}

void King::remove_blocked_moves()
{
    list_t nl_move_list = nl_act_moves;
    for (auto n_move : nl_move_list) {
        if (p_arr_board[n_move.first][n_move.second]) {
            if (p_arr_board[n_move.first][n_move.second]->get_player() == n_player) {
                nl_act_moves.remove(n_move);
            }
        }
    }
}