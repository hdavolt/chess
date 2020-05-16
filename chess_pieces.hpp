#ifndef __CHESS_PIECES_HPP__
#define __CHESS_PIECES_HPP__

#include <forward_list>
#include <algorithm>
#include <array>
#include <memory>

namespace Chess
{
    // Piece coordinates and lists of coordinates
    typedef std::pair<int, int> coord_t;
    typedef std::forward_list<coord_t> list_t;
    
    // Adding coordintes
    inline
    const coord_t operator+(const coord_t & left, const coord_t & right) {   
        return {left.first + right.first, left.second + right.second};                                    
    }

    class Piece
    {
    public:
        Piece();
        Piece(const int in_player, const coord_t in_location) : 
            n_player(in_player), n_location(in_location) {};

        const int        get_player() const      { return n_player; };
        const coord_t &  get_location() const    { return n_location; };
        const int        get_value() const       { return n_value; };
        const char       get_type() const        { return c_type; };
        const int        get_move_count() const  { return n_move_count; };
        const list_t &   get_move_list() const   { return nl_act_moves; };

        bool            move_to(const coord_t & in_location);

    protected:
        int             n_player;
        int             n_move_count = 0;
        coord_t         n_location;
        int             n_value = 0;
        char            c_type = '$';

        list_t          nl_rel_moves;
        list_t          nl_act_moves;
        list_t          nl_move_history;

        void            calc_relative_moves();
        virtual void    remove_blocked_moves() = 0;
    };

    class Pawn : public Piece
    {
    public:
        Pawn() : Piece() {};
        Pawn(const int in_player, const coord_t in_location);
        void remove_blocked_moves();
    };

    class Rook : public Piece
    {
    public:
        Rook() : Piece() {};
        Rook(const int in_player, const coord_t in_location);
        void remove_blocked_moves();
    };

    class Knight : public Piece
    {
    public:
        Knight() : Piece() {};
        Knight(const int in_player, const coord_t in_location);
        void remove_blocked_moves();
    };

    class Bishop : public Piece
    {
    public:
        Bishop() : Piece() {};
        Bishop(const int in_player, const coord_t in_location);
        void remove_blocked_moves();
    };

    class Queen : public Piece
    {
    public:
        Queen() : Piece() {};
        Queen(const int in_player, const coord_t in_location);
        void remove_blocked_moves();
    };

    class King : public Piece
    {
    public:
        King() : Piece() {};
        King(const int in_player, const coord_t in_location);
        void remove_blocked_moves();
    };

    // Expect a chess board
    typedef std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board_t;
    extern board_t p_arr_board;
}

#endif