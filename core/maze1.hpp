#ifndef MAZE1_HPP
#define MAZE1_HPP

#include "Maze.hpp"
#include "MazeGenerator.hpp"
#include <vector>
#include "Direction.hpp"

class maze1 : public MazeGenerator
{
private:

public:
	bool done;	//bool flag to indicate if maze generation is finished
	maze1();	//maze1 Constructor

	/*
	* This function takes in cell coordinates, a vector that stores if cells have been visited or not,
	* a vector that stores all the cells that have been visited, and a maze object.
	* This function will remove walls randomly with the conditions of a perfect maze taken into consideration.
	* It will return false if the generator is still working, and true if the generation has finished.
	*/
	bool createMaze(int x,int y, std::vector<std::vector<int>>& isVisited, std::vector<std::pair<int,int>>& visitedCells, Maze& maze);
	virtual void generateMaze(Maze& maze);

	//This vector stores the possible moves that can be taken at a particular (x,y) cell
	std::vector<Direction> nextMove(int x,int y, std::vector<std::vector<int>>& isVisited, Maze& maze);
};

#endif