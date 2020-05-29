#include "chess_pieces.hpp"
#include <iostream>

using namespace Chess;

// Reference a chess board by location coordinate
const std::unique_ptr<Piece> & get_piece(const coord_t& c)
{
    return p_arr_board[get_row(c)][get_col(c)];
}

// Functors for location comparisons
struct b_Col_High
{
    b_Col_High(const coord_t & in_location) : n_location(in_location) {}
    coord_t n_location;
    bool operator()(const coord_t & in_move) {
        return (   get_col(in_move)  == get_col(n_location)
                && get_row(in_move)  >  get_row(n_location) );
    }
};
struct b_Col_Low
{
    b_Col_Low(const coord_t & in_location) : n_location(in_location) {}
    coord_t n_location;
    bool operator()(const coord_t & in_move) {
        return (   get_col(in_move)  == get_col(n_location) 
                && get_row(in_move)  <  get_row(n_location) );
    }
};
struct b_Row_High
{
    b_Row_High(const coord_t & in_location) : n_location(in_location) {}
    coord_t n_location;
    bool operator()(const coord_t & in_move) {
        return (   get_col(in_move)  >  get_col(n_location)
                && get_row(in_move)  == get_row(n_location) );
    }
};
struct b_Row_Low
{
    b_Row_Low(const coord_t & in_location) : n_location(in_location) {}
    coord_t n_location;
    bool operator()(const coord_t & in_move) {
        return (   get_col(in_move)  <  get_col(n_location)
                && get_row(in_move)  == get_row(n_location) );
    }
};
struct b_Pos_Slope_High
{
    b_Pos_Slope_High(const coord_t & in_location) : n_location(in_location) {}
    coord_t n_location;
    bool operator()(const coord_t & in_move) {
        coord_t offset( get_col(in_move) - get_col(n_location), 
                        get_row(in_move) - get_row(n_location) );
        return (   get_col(offset) == get_row(offset)
                && get_col(offset) > 0 
                && get_row(offset) > 0 );
    }
};
struct b_Pos_Slope_Low
{
    b_Pos_Slope_Low(const coord_t & in_location) : n_location(in_location) {}
    coord_t n_location;
    bool operator()(const coord_t & in_move) {
        coord_t offset( get_col(in_move) - get_col(n_location), 
                        get_row(in_move) - get_row(n_location) );
        return (   get_col(offset) == get_row(offset)
                && get_col(offset) < 0 
                && get_row(offset) < 0 );
    }
};
struct b_Neg_Slope_High
{
    b_Neg_Slope_High(const coord_t & in_location) : n_location(in_location) {}
    coord_t n_location;
    bool operator()(const coord_t & in_move) {
        coord_t offset( get_col(in_move) - get_col(n_location), 
                        get_row(in_move) - get_row(n_location) );
        return (   std::abs(get_col(offset) == get_row(offset))
                && get_col(offset) < 0 
                && get_row(offset) > 0 );
    }
};
struct b_Neg_Slope_Low
{
    b_Neg_Slope_Low(const coord_t & in_location) : n_location(in_location) {}
    coord_t n_location;
    bool operator()(const coord_t & in_move) {
        coord_t offset( get_col(in_move) - get_col(n_location), 
                        get_row(in_move) - get_row(n_location) );
        return (   get_col(offset) == std::abs(get_row(offset))
                && get_col(offset) > 0 
                && get_row(offset) < 0 );
    }
};

bool Piece::move_to(const coord_t & in_location)
{
    bool b_retval = false;
    calc_relative_moves();
    remove_blocked_moves();
    // Because a .contains() function would be too easy
    if (std::find(nl_act_moves.begin(), nl_act_moves.end(), in_location) != nl_act_moves.end()) {
        nl_move_history.push_front(n_location);
        n_location = in_location;
        n_move_count++;
        b_retval = true;
        calc_relative_moves();
        remove_blocked_moves();
    }
    return b_retval;
}

void Piece::calc_relative_moves()
{
    // Calculate relative moves based on current location, trim out of bounds
    nl_act_moves.clear();
    for (coord_t n_rel : nl_rel_moves) {
        coord_t n_move = n_location + n_rel;
        if (   get_col(n_move) >= 0 && get_col(n_move) < 8
            && get_row(n_move) >= 0 && get_row(n_move) < 8 ) {
            nl_act_moves.push_front(n_move);
        }
    }
}

Pawn::Pawn(const int in_player, const coord_t in_location) : Piece(in_player, in_location)
{
    n_value = 1;
    c_type = 'p';

    if (n_player == 1) {
        nl_rel_moves = { {-1,  1}, { 0,  1}, { 1,  1}, { 0,  2} };
    }
    else if (n_player == 2) {
        nl_rel_moves = { {-1, -1}, { 0, -1}, { 1, -1}, { 0, -2} };
    }
}

void Pawn::remove_blocked_moves()
{
    list_t nl_move_list = nl_act_moves;
    for (coord_t n_move : nl_move_list) {
        if (get_piece(n_move)) {
            if (   n_location.second == get_col(n_move) 
                || get_piece(n_move)->get_player() == n_player) {
                nl_act_moves.remove(n_move);
            }
        }
        else if (get_col(n_location) != get_col(n_move)) {
            nl_act_moves.remove(n_move);
        }
        if (n_move_count == 1 && std::abs(get_row(n_move)) == 2) {
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
        if (get_piece(n_move)) {
                 if (b_Col_High(n_location)(n_move)) nl_act_moves.remove_if(b_Col_High(n_move));
            else if (b_Row_High(n_location)(n_move)) nl_act_moves.remove_if(b_Row_High(n_move));
            else if (b_Col_Low (n_location)(n_move)) nl_act_moves.remove_if(b_Col_Low (n_move));
            else if (b_Row_Low (n_location)(n_move)) nl_act_moves.remove_if(b_Row_Low (n_move));

            if (get_piece(n_move)->get_player() == n_player) { nl_act_moves.remove(n_move); }
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
        if (get_piece(n_move)) {
            if (get_piece(n_move)->get_player() == n_player) {
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
        if (get_piece(n_move)) {
                 if (b_Pos_Slope_High(n_location)(n_move)) nl_act_moves.remove_if(b_Pos_Slope_High(n_move));
            else if (b_Pos_Slope_Low (n_location)(n_move)) nl_act_moves.remove_if(b_Pos_Slope_Low (n_move));
            else if (b_Neg_Slope_High(n_location)(n_move)) nl_act_moves.remove_if(b_Neg_Slope_High(n_move));
            else if (b_Neg_Slope_Low (n_location)(n_move)) nl_act_moves.remove_if(b_Neg_Slope_Low (n_move));

            if (get_piece(n_move)->get_player() == n_player) { nl_act_moves.remove(n_move); }
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
    for (coord_t n_move : nl_move_list) {
        if (get_piece(n_move)) {
                 if (b_Col_High      (n_location)(n_move)) nl_act_moves.remove_if(b_Col_High      (n_move));
            else if (b_Row_High      (n_location)(n_move)) nl_act_moves.remove_if(b_Row_High      (n_move));
            else if (b_Col_Low       (n_location)(n_move)) nl_act_moves.remove_if(b_Col_Low       (n_move));
            else if (b_Row_Low       (n_location)(n_move)) nl_act_moves.remove_if(b_Row_Low       (n_move));
            else if (b_Pos_Slope_High(n_location)(n_move)) nl_act_moves.remove_if(b_Pos_Slope_High(n_move));
            else if (b_Pos_Slope_Low (n_location)(n_move)) nl_act_moves.remove_if(b_Pos_Slope_Low (n_move));
            else if (b_Neg_Slope_High(n_location)(n_move)) nl_act_moves.remove_if(b_Neg_Slope_High(n_move));
            else if (b_Neg_Slope_Low (n_location)(n_move)) nl_act_moves.remove_if(b_Neg_Slope_Low (n_move));

            if (get_piece(n_move)->get_player() == n_player) { nl_act_moves.remove(n_move); }
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
    for (coord_t n_move : nl_move_list) {
        if (get_piece(n_move)) {
            if (get_piece(n_move)->get_player() == n_player) {
                nl_act_moves.remove(n_move);
            }
        }
    }
}