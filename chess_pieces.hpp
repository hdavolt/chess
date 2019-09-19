#ifndef __CHESS_PIECES_HPP__
#define __CHESS_PIECES_HPP__

#include <list>
#include <algorithm>
#include <array>
#include <memory>

namespace Chess
{
    typedef std::pair<int, int> pair_t;
    typedef std::list<pair_t> list_t;
    
    inline
    pair_t operator+(const pair_t & left, const pair_t & right) {   
        return {left.first + right.first, left.second + right.second};                                    
    }

    class Piece
    {
    public:
        Piece();
        Piece(const int in_player, const pair_t in_location) : 
            n_player(in_player), n_location(in_location) {};

        const int get_player() const   { return n_player; };
        const pair_t get_location() const { return n_location; };

        const int get_value() { return n_value; };
        const char get_type() { return c_type; };

        bool add_move(const pair_t & in_location);
        const list_t & calc_avail_moves();

    protected:
        int n_player;
        int n_move_count = 0;

        pair_t n_location;

        int  n_value = 0;
        char c_type = '$';

        list_t  nl_rel_moves;
        list_t  nl_act_moves;
        list_t  nl_move_history;
        virtual void delete_blocked_moves() = 0;
    };

    class Pawn : public Piece
    {
    public:
        Pawn() : Piece() {};
        Pawn(const int in_player, const pair_t in_location);
        bool add_move(const pair_t & in_location);
        void delete_blocked_moves();
    };

    class Rook : public Piece
    {
    public:
        Rook() : Piece() {};
        Rook(const int in_player, const pair_t in_location);
        void delete_blocked_moves();
    };

    class Knight : public Piece
    {
    public:
        Knight() : Piece() {};
        Knight(const int in_player, const pair_t in_location);
        void delete_blocked_moves();
    };

    class Bishop : public Piece
    {
    public:
        Bishop() : Piece() {};
        Bishop(const int in_player, const pair_t in_location);
        void delete_blocked_moves();
    };

    class Queen : public Piece
    {
    public:
        Queen() : Piece() {};
        Queen(const int in_player, const pair_t in_location);
        void delete_blocked_moves();
    };

    class King : public Piece
    {
    public:
        King() : Piece() {};
        King(const int in_player, const pair_t in_location);
        void delete_blocked_moves();
    };

    // Functors for location comparisons
    struct b_Col_High
    {
        b_Col_High(const pair_t & in_location) : n_location(in_location) {}
        pair_t n_location;
        bool operator()(const pair_t & in_move) {
            return (   in_move.first  >  n_location.first 
                    && in_move.second == n_location.second );
        }
    };

    struct b_Col_Low
    {
        b_Col_Low(const pair_t & in_location) : n_location(in_location) {}
        pair_t n_location;
        bool operator()(const pair_t & in_move) {
            return (   in_move.first  <  n_location.first 
                    && in_move.second == n_location.second );
        }
    };

    struct b_Row_High
    {
        b_Row_High(const pair_t & in_location) : n_location(in_location) {}
        pair_t n_location;
        bool operator()(const pair_t & in_move) {
            return (   in_move.first  == n_location.first 
                    && in_move.second >  n_location.second );
        }
    };

    struct b_Row_Low
    {
        b_Row_Low(const pair_t & in_location) : n_location(in_location) {}
        pair_t n_location;
        bool operator()(const pair_t & in_move) {
            return (   in_move.first  == n_location.first 
                    && in_move.second <  n_location.second );
        }
    };

    struct b_Pos_Slope_High
    {
        b_Pos_Slope_High(const pair_t & in_location) : n_location(in_location) {}
        pair_t n_location;
        bool operator()(const pair_t & in_move) {
            pair_t offset( in_move.first  - n_location.first, 
                           in_move.second - n_location.second );
            return (   offset.first  == offset.second
                    && offset.first  > 0 
                    && offset.second > 0 );
        }
    };

    struct b_Pos_Slope_Low
    {
        b_Pos_Slope_Low(const pair_t & in_location) : n_location(in_location) {}
        pair_t n_location;
        bool operator()(const pair_t & in_move) {
            pair_t offset( in_move.first  - n_location.first, 
                           in_move.second - n_location.second );
            return (   offset.first  == offset.second
                    && offset.first  < 0 
                    && offset.second < 0 );
        }
    };

    struct b_Neg_Slope_High
    {
        b_Neg_Slope_High(const pair_t & in_location) : n_location(in_location) {}
        pair_t n_location;
        bool operator()(const pair_t & in_move) {
            pair_t offset( in_move.first  - n_location.first, 
                           in_move.second - n_location.second );
            return (   offset.first  == std::abs(offset.second)
                    && offset.first  > 0 
                    && offset.second < 0 );
        }
    };

    struct b_Neg_Slope_Low
    {
        b_Neg_Slope_Low(const pair_t & in_location) : n_location(in_location) {}
        pair_t n_location;
        bool operator()(const pair_t & in_move) {
            pair_t offset( in_move.first  - n_location.first, 
                           in_move.second - n_location.second );
            return (   std::abs(offset.first)  == offset.second
                    && offset.first  < 0 
                    && offset.second > 0 );
        }
    };

    extern std::array<std::array<std::unique_ptr<Piece>, 8>, 8> p_arr_board;
}

#endif