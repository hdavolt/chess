#ifndef __CHESS_PIECES_HPP__
#define __CHESS_PIECES_HPP__
#define CONSOLE

#include <list>
#include "coord.hpp"

class Piece
{
public:
    Piece();
    Piece(int pl, Coord l) : player(pl), loc(l) {};
    const int & get_val() const { return value; };
    const int & get_player() const { return player; };
    const Coord & get_loc() const { return loc; };
    void set_loc(const Coord &l) { loc = l; };
    const std::list<Coord> & get_moves() const { return moves; };
    void calc_moves(const Coord &c);
    virtual void add_move() { move_count++; };
    virtual void remove_blocked(const std::list<std::pair<Coord, int>> &blocks) = 0;

protected:
    const int value = 0;
    int player;
    int move_count = 0;
    Coord loc;
    std::list<Coord> rules;
    std::list<Coord> moves;
};

class Pawn : public Piece
{
public:
    Pawn() : Piece() {};
    Pawn(int pl, Coord l);
    void add_move();
    void remove_blocked(const std::list<std::pair<Coord, int>> &blocks);

private:
    const int value = 1;
    void pawn_update_rules();
};

class Rook : public Piece
{
public:
    Rook() : Piece() {};
    Rook(int pl, Coord l);
    void remove_blocked(const std::list<std::pair<Coord, int>> &blocks);

private:
    const int value = 5;
};

class Knight : public Piece
{
public:
    Knight() : Piece() {};
    Knight(int pl, Coord l);
    void remove_blocked(const std::list<std::pair<Coord, int>> &blocks);

private:
    const int value = 3;
};

class Bishop : public Piece
{
public:
    Bishop() : Piece() {};
    Bishop(int pl, Coord l);
    void remove_blocked(const std::list<std::pair<Coord, int>> &blocks);

private:
    const int value = 3;
};

class Queen : public Piece
{
public:
    Queen() : Piece() {};
    Queen(int pl, Coord l);
    void remove_blocked(const std::list<std::pair<Coord, int>> &blocks);

private:
    const int value = 9;
};

class King : public Piece
{
public:
    King() : Piece() {};
    King(int pl, Coord l);
    void remove_blocked(const std::list<std::pair<Coord, int>> &blocks);

private:
    const int value = 100;
};

#endif