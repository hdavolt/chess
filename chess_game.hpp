#ifndef __CHESS_GAME_HPP__
#define __CHESS_GAME_HPP__

#include <forward_list>
#include <algorithm>
#include <array>
#include <map>
#include <memory>

namespace Chess
{
    // Piece coordinates and lists of coordinates
    using coord = std::pair<const short, const short>;
    using list = std::forward_list<const coord>;
    using player = unsigned short;
    using player_coord = std::pair<const player, const coord>;
    using player_list = std::forward_list<const player_coord>;
    using move_set = std::map<const unsigned short, const list>;

    // First member is column (file), second is row (rank)
    inline const short col(const coord & c) { return c.first; };
    inline const short row(const coord & c) { return c.second; };

    //Adding coordinates
    inline coord operator+(const coord & left, const coord & right) {   
        return {col(left) + col(right), row(left) + row(right)};                                    
    }

    class Piece
    {
    public:
        Piece(const short in_player) : 
            player(in_player) {};

        const unsigned short            player;
        unsigned short                  move_count = 0;
        list                            move_history;

        virtual const list              current_moves(const player_list & in_player_list) = 0;
    };

    class Pawn : public Piece
    {
    public:
        Pawn(const short in_player) : Piece(in_player) {};

        static const unsigned short     value = 1;
        static const char               type = 'p';
        static const move_set           available_moves;

        const list                      current_moves(const player_list & in_player_list);
    };
}

#endif