CXX = g++
CXXFLAGS = -Wall -g

chess: coord.hpp chess_pieces.hpp chess_exceptions.hpp
	$(CXX) $(CXXFLAGS) -o chess main.cpp coord.cpp chess_pieces.cpp