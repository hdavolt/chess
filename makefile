CXX = g++
CXXFLAGS = -Wall -g

chess: coord.hpp rules.hpp chess_exceptions.hpp
	$(CXX) $(CXXFLAGS) -o chess main.cpp coord.cpp rules.cpp