#ifndef MSOLVER_HPP
#define MSOLVER_HPP

#include "MazeSolver.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"

class mSolver : public MazeSolver
{


private:




public:

	mSolver(); //constructor
	virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
	/*
	* This function takes in a Maze and a MazeSolution object, and a vector that stores 
	* vectors of boolean values.
	* This function will use depth-first search to solve a given maze using recursion
	*/
	void solve(const Maze& maze, MazeSolution& mazeSolution, std::vector<std::vector<bool>> isVisited);

	//This vector stores the possible Direction to take once at a particular (x,y) coordinate.
	std::vector<Direction> nextMove(int x, int y, std::vector<std::vector<bool>>& isVisited, const Maze& maze);

};

#endif
