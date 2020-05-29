CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic-errors -g

chess: chess_pieces.hpp
	$(CXX) $(CXXFLAGS) -o chess chess_main.cpp chess_pieces.cpp