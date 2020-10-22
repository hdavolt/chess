#include "chess_game.hpp"

using namespace Chess;

const move_set Pawn::available_moves = {
    {1, std::make_unique<list>({{-1,  1}, { 0,  1}, { 1,  1}, { 0,  2}})}
}