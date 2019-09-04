CXX = g++
CXXFLAGS = -Wall -g

chess: chess_pieces.hpp
	$(CXX) $(CXXFLAGS) -o chess chess_main.cpp chess_pieces.cpp