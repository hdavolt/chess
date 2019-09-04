#ifndef __CHESS_PIECES_HPP__
#define __CHESS_PIECES_HPP__

#include <list>
#include <algorithm>
#include <array>
#include <memory>

namespace Chess
{
    class Piece
    {
    public:
        Piece();
        Piece(const int in_player, const int in_location) : 
            n_player(in_player), n_location(in_location) {};

        const int get_player() const   { return n_player; };
        const int get_location() const { return n_location; };

        const int get_value() { return n_value; };
        const char get_type() { return c_type; };

        bool add_move(const int in_location);
        const std::list<int> & calc_avail_moves();

    protected:
        int n_player;
        int n_location;
        int n_move_count = 0;

        int  n_value = 0;
        char c_type = '$';

        std::list<int>  nl_rel_moves;
        std::list<int>  nl_act_moves;
        std::list<int>  nl_move_history;
        virtual void delete_blocked_moves() = 0;

        /*
        void DeleteColHigh       (const int inValue);
        void DeleteColLow        (const int inValue);
        void DeleteRowHigh       (const int inValue);
        void DeleteRowLow        (const int inValue);
        void DeleteDiagHighHigh  (const int inValue);
        void DeleteDiagHighLow   (const int inValue);
        void DeleteDiagLowLow    (const int inValue);
        void DeleteDiagLowHigh   (const int inValue);
        */
    };

    class Pawn : public Piece
    {
    public:
        Pawn() : Piece() {};
        Pawn(const int in_player, const int in_location);
        bool add_move(const int in_location);
        void delete_blocked_moves();
    };

    class Rook : public Piece
    {
    public:
        Rook() : Piece() {};
        Rook(const int in_player, const int in_location);
        void delete_blocked_moves();
    };

    class Knight : public Piece
    {
    public:
        Knight() : Piece() {};
        Knight(const int in_player, const int in_location);
        void delete_blocked_moves();
    };

    class Bishop : public Piece
    {
    public:
        Bishop() : Piece() {};
        Bishop(const int in_player, const int in_location);
        void delete_blocked_moves();
    };

    class Queen : public Piece
    {
    public:
        Queen() : Piece() {};
        Queen(const int in_player, const int in_location);
        void delete_blocked_moves();
    };

    class King : public Piece
    {
    public:
        King() : Piece() {};
        King(const int in_player, const int in_location);
        void delete_blocked_moves();
    };

    // Functors for location comparisons
    struct b_Col_High
    {
        b_Col_High(const int & in_location) : n_location(in_location) {}
        int n_location;
        bool operator()(const int & in_move) {
            // mod 8 will tell us if it's in the same column
            return (   (in_move > n_location) 
                    && ((in_move - n_location) % 8 == 0) );
        }
    };

    struct b_Col_Low
    {
        b_Col_Low(const int & in_location) : n_location(in_location) {}
        int n_location;
        bool operator()(const int & in_move) {
            // mod 8 will tell us if it's in the same column
            return (   (in_move < n_location) 
                    && ((in_move - n_location) % 8 == 0) );
        }
    };

    struct b_Row_High
    {
        b_Row_High(const int & in_location) : n_location(in_location) {}
        int n_location;
        bool operator()(const int & in_move) {
            // if the quotient and the mod are equal it's in the same roe
            return (   (in_move > n_location) 
                    && ((in_move / 8 == n_location / 8)) );
        }
    };

    struct b_Row_Low
    {
        b_Row_Low(const int & in_location) : n_location(in_location) {}
        int n_location;
        bool operator()(const int & in_move) {
            // if the quotient and the mod are equal it's in the same roe
            return (   (in_move < n_location) 
                    && (in_move / 8 == n_location / 8) );
        }
    };

    struct b_Pos_Slope_High
    {
        b_Pos_Slope_High(const int & in_location) : n_location(in_location) {}
        int n_location;
        bool operator()(const int & in_move) {
            // mod 9 gives us positive slope, mod 8 eliminates wraparound
            return (   ((in_move - n_location) % 9 == 0) 
                    && (in_move > n_location) 
                    && (in_move % 8 > n_location % 8) );
        }
    };

    struct b_Pos_Slope_Low
    {
        b_Pos_Slope_Low(const int & in_location) : n_location(in_location) {}
        int n_location;
        bool operator()(const int & in_move) {
            // mod 9 gives us positive slope, mod 8 eliminates wraparound
            return (   ((in_move - n_location) % 9 == 0) 
                    && (in_move < n_location) 
                    && (in_move % 8 < n_location % 8) );
        }
    };

    struct b_Neg_Slope_High
    {
        b_Neg_Slope_High(const int & in_location) : n_location(in_location) {}
        int n_location;
        bool operator()(const int & in_move) {
            // mod 7 gives us negative slope, mod 8 eliminates wraparound
            return (   ((in_move - n_location) % 7 == 0) 
                    && (in_move > n_location) 
                    && (in_move % 8 < n_location % 8) );
        }
    };

    struct b_Neg_Slope_Low
    {
        b_Neg_Slope_Low(const int & in_location) : n_location(in_location) {}
        int n_location;
        bool operator()(const int & in_move) {
            // mod 7 gives us negative slope, mod 8 eliminates wraparound
            return (   ((in_move - n_location) % 7 == 0) 
                    && (in_move < n_location) 
                    && (in_move % 8 > n_location % 8) );
        }
    };

    extern std::array<std::unique_ptr<Piece>, 64> p_arr_board;
}

#endif