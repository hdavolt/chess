#include "chess_pieces.hpp"

using namespace Chess;

const std::list<int> & Piece::calc_avail_moves()
{
    // Calculate relative moves based on current location, trim out of bounds
    nl_act_moves.clear();
    for (auto n_rel : nl_rel_moves) {
        int n_move = n_location + n_rel;
        if (n_move >= 0 && n_move < 64) {
            nl_act_moves.push_back(n_move);
        }
    }
    delete_blocked_moves();
    return nl_act_moves;
}

bool Piece::add_move(const int in_location)
{
    // Because a .contains() function would be too easy
    if (std::find(nl_act_moves.begin(), nl_act_moves.end(), in_location) != nl_act_moves.end()) {
        nl_move_history.push_back(n_location);
        n_location = in_location;
        n_move_count++;
        return true;
    }
    else {
        return false;
    }
}
/*
void Piece::DeleteColHigh(const int inValue)
{
    for (auto n_move : nl_act_moves) {
        // mod 8 will tell us if it's in the column
        if (n_move > inValue && (n_move - inValue) % 8 == 0) {
            nl_act_moves.remove(n_move);
        }
    }
}
void Piece::DeleteColLow(const int inValue)
{
    for (auto n_move : nl_act_moves) {
        // mod 8 will tell us if it's in the column
        if (n_move < inValue && (n_move - inValue) % 8 == 0) {
            nl_act_moves.remove(n_move);
        }
    }
}
void Piece::DeleteRowHigh(const int inValue)
{
    for (auto n_move : nl_act_moves) {
        // if they are in the same row the truncated quotient will be the same
        if (n_move > inValue && (n_move / 8 == inValue / 8)) {
            nl_act_moves.remove(n_move);
        }
    }
}
void Piece::DeleteRowLow(const int inValue)
{
    for (auto n_move : nl_act_moves) {
        // if they are in the same row the truncated quotient will be the same
        if (n_move < inValue && (n_move / 8 == inValue / 8)) {
            nl_act_moves.remove(n_move);
        }
    }
}
void Piece::DeleteDiagHighHigh(const int inValue)
{
    for (auto n_move : nl_act_moves) {
        // mod 9 will give us the high slope, check columns with mod 8 to prevent wraparound
        if ((n_move - inValue) % 9 == 0 && n_move > inValue && n_move % 8 > inValue % 8 ) {
            nl_act_moves.remove(n_move);
        }
    }
}
void Piece::DeleteDiagHighLow(const int inValue)
{
    for (auto n_move : nl_act_moves) {
        // mod 7 will give us the low slope, check columns with mod 8 to prevent wraparound
        if ((n_move - inValue) % 7 == 0 && n_move < inValue && n_move % 8 > inValue % 8 ) {
            nl_act_moves.remove(n_move);
        }
    }
}
void Piece::DeleteDiagLowLow(const int inValue)
{
    for (auto n_move : nl_act_moves) {
        // mod 9 will give us the high slope, check columns with mod 8 to prevent wraparound
        if ((n_move - inValue) % 9 == 0 && n_move < inValue && n_move % 8 < inValue % 8 ) {
            nl_act_moves.remove(n_move);
        }
    }
}
void Piece::DeleteDiagLowHigh(const int inValue)
{
    for (auto n_move : nl_act_moves) {
        // mod 7 will give us the low slope, check columns with mod 8 to prevent wraparound
        if ((n_move - inValue) % 7 == 0 && n_move > inValue && n_move % 8 < inValue % 8 ) {
            nl_act_moves.remove(n_move);
        }
    }
}
*/
Pawn::Pawn(const int in_player, const int in_location) : Piece(in_player, in_location)
{
    n_value = 1;
    c_type = 'p';

    if (n_player == 1) {
        nl_rel_moves = { 7, 8, 9, 16 };
    }
    else if (n_player == 2) {
        nl_rel_moves = { -7, -8, -9, -16 };
    }
}

bool Pawn::add_move(const int in_location)
{
    bool n_return = add_move(in_location);
    if (n_return == 0 && n_move_count == 1) {
        nl_rel_moves.clear();
        if (n_player == 1) {
            nl_rel_moves = { 7, 8, 9 };
        }
        else if (n_player == 2) {
            nl_rel_moves = { -7, -8, -9 };
        }
    }
    return n_return;
}

void Pawn::delete_blocked_moves()
{
    std::list<int> nl_move_list = nl_act_moves;
    for (auto n_move : nl_move_list) {
        if (p_arr_board[n_move]) {
            if (!((n_location - n_move) % 8 != 0 && p_arr_board[n_move]->get_player() != n_player)) {
                nl_act_moves.remove(n_move);
            }
        }
        else {
            if ((n_location - n_move) % 8 != 0) {
                nl_act_moves.remove(n_move);
            }
        }
    }
}

Rook::Rook(const int in_player, const int in_location) : Piece(in_player, in_location)
{
    n_value = 5;
    c_type = 'r';
    
    for (int n = 1; n < 8; n++) {
        nl_rel_moves.push_back(n);
        nl_rel_moves.push_back(n * -1);
        nl_rel_moves.push_back(n * 8);
        nl_rel_moves.push_back(n * (8 * -1));
    }
}

void Rook::delete_blocked_moves()
{
    for (auto n_move : nl_act_moves) {
        if (p_arr_board[n_move]) {
            bool b_high = (n_location - n_move) < 0;
            bool b_col = (n_location - n_move % 8) == 0;

                 if ( b_high &&  b_col) { nl_act_moves.remove_if(b_Col_High(n_location)); }
            else if ( b_high && !b_col) { nl_act_moves.remove_if(b_Row_High(n_location)); }
            else if (!b_high &&  b_col) { nl_act_moves.remove_if( b_Col_Low(n_location)); }
            else if (!b_high && !b_col) { nl_act_moves.remove_if( b_Row_Low(n_location)); }

            if (p_arr_board[n_move]->get_player() == n_player) { nl_act_moves.remove(n_move); }
        }
    }
}

Knight::Knight(const int in_player, const int in_location) : Piece(in_player, in_location)
{
    n_value = 3;
    c_type = 'n';
    
    nl_rel_moves = { -17, -19, -10, -6, 6, 10, 17, 19 };
}

void Knight::delete_blocked_moves()
{
    for (auto n_move : nl_act_moves) {
        if (p_arr_board[n_move]->get_player() == n_player) {
            nl_act_moves.remove(n_move);
        }
    }
}

Bishop::Bishop(const int in_player, const int in_location) : Piece(in_player, in_location)
{
    n_value = 3;
    c_type = 'b';
    
    for (int n = 1; n < 8; n++) {
        nl_rel_moves.push_back((n *  8) + n);
        nl_rel_moves.push_back((n * -8) - n);
        nl_rel_moves.push_back((n * -8) + n);
        nl_rel_moves.push_back((n *  8) - n);
    }
}

void Bishop::delete_blocked_moves()
{
    for (auto n_move : nl_act_moves) {
        if (p_arr_board[n_move]) {
            bool b_pos_slope = (n_move - n_location) % 9 == 0;
            bool b_high = (n_move - n_location) > 0;

                 if ( b_pos_slope &&  b_high) { nl_act_moves.remove_if(b_Pos_Slope_High(n_location)); }
            else if ( b_pos_slope && !b_high) { nl_act_moves.remove_if( b_Pos_Slope_Low(n_location)); }
            else if (!b_pos_slope &&  b_high) { nl_act_moves.remove_if(b_Neg_Slope_High(n_location)); }
            else if (!b_pos_slope && !b_high) { nl_act_moves.remove_if( b_Neg_Slope_Low(n_location)); }

            if (p_arr_board[n_move]->get_player() == n_player) { nl_act_moves.remove(n_move); }
        }
    }
}

Queen::Queen(const int in_player, const int in_location) : Piece(in_player, in_location)
{
    n_value = 9;
    c_type = 'q';
    
    for (int n = 1; n < 8; n++) {
        nl_rel_moves.push_back(n);
        nl_rel_moves.push_back(n * -1);
        nl_rel_moves.push_back(n * 8);
        nl_rel_moves.push_back(n * (8 * -1));
        nl_rel_moves.push_back((n *  8) + n);
        nl_rel_moves.push_back((n * -8) - n);
        nl_rel_moves.push_back((n * -8) + n);
        nl_rel_moves.push_back((n *  8) - n);
    }
}

void Queen::delete_blocked_moves()
{
    for (auto n_move : nl_act_moves) {
        if (p_arr_board[n_move]) {
            bool b_high = (n_location - n_move) < 0;
            bool b_col = (n_location - n_move % 8) == 0;
            bool b_row = (n_location / 8) == (n_move / 8);
            bool b_pos_slope = (n_move - n_location) % 9 == 0;
            
                 if ( b_high &&  b_col && !b_row && !b_pos_slope) 
                    { nl_act_moves.remove_if(b_Col_High(n_location)); }
            else if (!b_high &&  b_col && !b_row && !b_pos_slope) 
                    { nl_act_moves.remove_if(b_Col_Low(n_location)); }
            else if ( b_high && !b_col &&  b_row && !b_pos_slope) 
                    { nl_act_moves.remove_if(b_Row_High(n_location)); }
            else if (!b_high && !b_col &&  b_row && !b_pos_slope) 
                    { nl_act_moves.remove_if(b_Row_Low(n_location)); }
            else if ( b_high && !b_col && !b_row &&  b_pos_slope) 
                    { nl_act_moves.remove_if(b_Pos_Slope_High(n_location)); }
            else if (!b_high && !b_col && !b_row &&  b_pos_slope) 
                    { nl_act_moves.remove_if(b_Pos_Slope_Low(n_location)); }
            else if ( b_high && !b_col && !b_row && !b_pos_slope) 
                    { nl_act_moves.remove_if(b_Neg_Slope_High(n_location)); }
            else if (!b_high && !b_col && !b_row && !b_pos_slope) 
                    { nl_act_moves.remove_if(b_Neg_Slope_Low(n_location)); }
        }
    }
}

King::King(const int in_player, const int in_location) : Piece(in_player, in_location)
{
    n_value = 100;
    c_type = 'k';
    
    nl_rel_moves = { -9, -8, -7, -1, 1, 7, 8, 9 };
}

void King::delete_blocked_moves()
{
    for (auto n_move : nl_act_moves) {
        if (p_arr_board[n_move]->get_player() == n_player) {
            nl_act_moves.remove(n_move);
        }
    }
}