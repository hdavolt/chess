#define CONSOLE
//#define DEBUG

#include "chess_pieces.hpp"
#include "chess_exceptions.hpp"

void Piece::calc_moves(const Coord &c)
{
    moves.clear();
    for (Coord r : rules) {
        try {
            moves.push_back(Coord(c.get_x() + r.get_x(),
                                  c.get_y() + r.get_y()));
        }
        catch(Out_of_bounds &out) {
            // An out of bounds coordinate won't be created
            #ifdef DEBUG
            std::cout << "Out of bounds!" << std::endl;
            #endif
        }
    }
}

Pawn::Pawn(int pl, Coord l) : Piece(pl, l)
{
    if (player == 1) {
        rules.push_back(Coord( 0,  2, false));
        rules.push_back(Coord( 0,  1, false));
        rules.push_back(Coord(-1,  1, false));
        rules.push_back(Coord( 1,  1, false));
    }
    else if (player == 2) {
        rules.push_back(Coord( 0, -2, false));
        rules.push_back(Coord( 0, -1, false));
        rules.push_back(Coord(-1, -1, false));
        rules.push_back(Coord( 1, -1, false));
    }
}

void Pawn::remove_blocked(const std::list<std::pair<Coord, int>> &blocks)
{
    for (auto bl : blocks) {
        if (!(bl.first.comp_x(loc) != 0 && bl.second != player));
            moves.remove(bl.first);
    }
}

void Pawn::add_move()
{
    add_move();
    if (move_count == 1)
        pawn_update_rules();
}

void Pawn::pawn_update_rules()
{
    rules.clear();
    if (player == 1) {
        rules.push_back(Coord( 0,  1, false));
        rules.push_back(Coord(-1,  1, false));
        rules.push_back(Coord( 1,  1, false));
    }
    else if (player == 2) {
        rules.push_back(Coord( 0, -1, false));
        rules.push_back(Coord(-1, -1, false));
        rules.push_back(Coord( 1, -1, false));
    }
}

Rook::Rook(int pl, Coord l) : Piece(pl, l)
{
    for (int i = 1; i < 8; i++) {
        rules.push_back(Coord( 0     , i     , false));
        rules.push_back(Coord( 0     , i / -1, false));
        rules.push_back(Coord( i     , 0     , false));
        rules.push_back(Coord( i / -1, 0     , false));
    }
}

void Rook::remove_blocked(const std::list<std::pair<Coord, int>> &blocks)
{
    Coord x_max = loc;
    Coord x_min = loc;
    Coord y_max = loc;
    Coord y_min = loc;
    for (auto bl : blocks) {
        Coord comp = bl.first.comp(loc);
        if (comp.get_x() > 0) {
            if (bl.first.comp_x(x_max) < 0) {
                x_max = bl.first;
                if (bl.second == player)
                    x_max.move(-1, 0);
            }
        }
        else if (comp.get_x() < 0) {
            if (bl.first.comp_x(x_min) > 0) {
                x_min = bl.first;
                if (bl.second == player)
                    x_min.move(1, 0);
            }
        }
        else if (comp.get_y() > 0) {
            if (bl.first.comp_y(y_max) < 0) {
                y_max = bl.first;
                if (bl.second == player)
                    y_max.move(0, -1);
            }
        }
        else if (comp.get_y() < 0) {
            if (bl.first.comp_y(y_min) > 0) {
                y_min = bl.first;
                if (bl.second == player)
                    y_min.move(0, 1);
            }
        }
    }
    for (Coord m : moves) {
        if (   m.comp_x(x_max) > 0
            || m.comp_x(x_min) < 0
            || m.comp_y(y_max) > 0
            || m.comp_y(y_min) < 0)
            moves.remove(m);
    }
}

Knight::Knight(int pl, Coord l) : Piece(pl, l)
{
    rules.push_back(Coord( 1,  2, false));
    rules.push_back(Coord( 1, -2, false));
    rules.push_back(Coord( 2,  1, false));
    rules.push_back(Coord( 2, -1, false));
    rules.push_back(Coord(-1,  2, false));
    rules.push_back(Coord(-1, -2, false));
    rules.push_back(Coord(-2,  1, false));
    rules.push_back(Coord(-2, -1, false));
}

void Knight::remove_blocked(const std::list<std::pair<Coord, int>> &blocks)
{
    for (auto bl : blocks) {
        if (bl.second == player);
            moves.remove(bl.first);
    }
}

Bishop::Bishop(int pl, Coord l) : Piece(pl, l)
{
    for (int i = 1; i < 8; i++) {
        rules.push_back(Coord( i     , i     , false));
        rules.push_back(Coord( i / -1, i / -1, false));
        rules.push_back(Coord( i     , i / -1, false));
        rules.push_back(Coord( i / -1, i     , false));
    }
}

void Bishop::remove_blocked(const std::list<std::pair<Coord, int>> &blocks)
{
    Coord x_max = loc;
    Coord x_min = loc;
    Coord y_max = loc;
    Coord y_min = loc;
    Coord pos_max = loc;
    Coord pos_min = loc;
    Coord neg_max = loc;
    Coord neg_min = loc;
    for (auto bl : blocks) {
        Coord comp = bl.first.comp(loc);
        if (comp.get_x() > 0 && comp.get_y() == 0) {
            if (bl.first.comp_x(x_max) < 0) {
                x_max = bl.first;
                if (bl.second == player)
                    x_max.move(-1, 0);
            }
        }
        else if (comp.get_x() < 0 && comp.get_y() == 0) {
            if (bl.first.comp_x(x_min) > 0) {
                x_min = bl.first;
                if (bl.second == player)
                    x_min.move(1, 0);
            }
        }
        else if (comp.get_y() > 0 && comp.get_x() == 0) {
            if (bl.first.comp_y(y_max) < 0) {
                y_max = bl.first;
                if (bl.second == player)
                    y_max.move(0, -1);
            }
        }
        else if (comp.get_y() < 0 && comp.get_x() == 0) {
            if (bl.first.comp_y(y_min) > 0) {
                y_min = bl.first;
                if (bl.second == player)
                    y_min.move(0, 1);
            }
        }
        else if (comp.get_x() > 0 && comp.get_y() > 0) {
            if (bl.first.comp_x(pos_max) < 0 && bl.first.comp_y(pos_max) < 0) {
                pos_max = bl.first;
                if (bl.second == player)
                    pos_max.move(-1, -1);
            }
        }
        else if (comp.get_x() < 0 && comp.get_y() < 0) {
            if (bl.first.comp_x(pos_min) > 0 && bl.first.comp_y(pos_min) > 0) {
                pos_min = bl.first;
                if (bl.second == player)
                    pos_min.move(1, 1);
            }
        }
        else if (comp.get_x() < 0 && comp.get_y() > 0) {
            if (bl.first.comp_x(neg_max) > 0 && bl.first.comp_y(neg_max) < 0) {
                neg_max = bl.first;
                if (bl.second == player)
                    neg_max.move(1, -1);
            }
        }
        else if (comp.get_x() > 0 && comp.get_y() < 0) {
            if (bl.first.comp_x(neg_min) < 0 && bl.first.comp_y(neg_min) > 0) {
                neg_min = bl.first;
                if (bl.second == player)
                    neg_min.move(-1, 1);
            }
        }
    }
    for (Coord m : moves) {
        if (   (m.comp_x(x_max) > 0 && m.comp_y(x_max) == 0)
            || (m.comp_x(x_min) < 0 && m.comp_y(x_min) == 0)
            || (m.comp_y(y_max) > 0 && m.comp_x(y_max) == 0)
            || (m.comp_y(y_min) < 0 && m.comp_x(y_min) == 0)
            || (m.comp_x(pos_max) > 0 && m.comp_y(pos_max) > 0)
            || (m.comp_x(pos_min) < 0 && m.comp_y(pos_min) < 0)
            || (m.comp_x(neg_max) < 0 && m.comp_y(neg_max) > 0)
            || (m.comp_x(neg_min) > 0 && m.comp_y(neg_min) < 0))
            moves.remove(m);
    }
}

Queen::Queen(int pl, Coord l) : Piece(pl, l)
{
    for (int i = 1; i < 8; i++) {
        rules.push_back(Coord( 0     , i     , false));
        rules.push_back(Coord( 0     , i / -1, false));
        rules.push_back(Coord( i     , 0     , false));
        rules.push_back(Coord( i / -1, 0     , false));
        rules.push_back(Coord( i     , i     , false));
        rules.push_back(Coord( i / -1, i / -1, false));
        rules.push_back(Coord( i     , i / -1, false));
        rules.push_back(Coord( i / -1, i     , false));
    }
}

void Queen::remove_blocked(const std::list<std::pair<Coord, int>> &blocks)
{
    Coord pos_max = loc;
    Coord pos_min = loc;
    Coord neg_max = loc;
    Coord neg_min = loc;
    for (auto bl : blocks) {
        Coord comp = bl.first.comp(loc);
        if (comp.get_x() > 0 && comp.get_y() > 0) {
            if (bl.first.comp_x(pos_max) < 0 && bl.first.comp_y(pos_max) < 0) {
                pos_max = bl.first;
                if (bl.second == player)
                    pos_max.move(-1, -1);
            }
        }
        else if (comp.get_x() < 0 && comp.get_y() < 0) {
            if (bl.first.comp_x(pos_min) > 0 && bl.first.comp_y(pos_min) > 0) {
                pos_min = bl.first;
                if (bl.second == player)
                    pos_min.move(1, 1);
            }
        }
        else if (comp.get_x() < 0 && comp.get_y() > 0) {
            if (bl.first.comp_x(neg_max) > 0 && bl.first.comp_y(neg_max) < 0) {
                neg_max = bl.first;
                if (bl.second == player)
                    neg_max.move(1, -1);
            }
        }
        else if (comp.get_x() > 0 && comp.get_y() < 0) {
            if (bl.first.comp_x(neg_min) < 0 && bl.first.comp_y(neg_min) > 0) {
                neg_min = bl.first;
                if (bl.second == player)
                    neg_min.move(-1, 1);
            }
        }
    }
    for (Coord m : moves) {
        if (   (m.comp_x(pos_max) > 0 && m.comp_y(pos_max) > 0)
            || (m.comp_x(pos_min) < 0 && m.comp_y(pos_min) < 0)
            || (m.comp_x(neg_max) < 0 && m.comp_y(neg_max) > 0)
            || (m.comp_x(neg_min) > 0 && m.comp_y(neg_min) < 0))
            moves.remove(m);
    }
}

King::King(int pl, Coord l) : Piece(pl, l)
{
    rules.push_back(Coord( 1,  1, false));
    rules.push_back(Coord( 1,  0, false));
    rules.push_back(Coord( 1, -1, false));
    rules.push_back(Coord( 0,  1, false));
    rules.push_back(Coord( 0, -1, false));
    rules.push_back(Coord(-1,  1, false));
    rules.push_back(Coord(-1,  0, false));
    rules.push_back(Coord(-1, -1, false));
}