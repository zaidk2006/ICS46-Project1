#include <ics46/factory/DynamicFactory.hpp>
#include "mSolver.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"
#include <iostream>
#include <vector>
#include "Direction.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, mSolver, "Zaid's Solver (Required)");



mSolver::mSolver()
{

}


void mSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{

	std::vector<std::vector<bool>> isVisited(maze.getWidth(), std::vector<bool>(maze.getHeight(), false)); //creates a vector that contains maze.getWidth() vectors
																										   //that contain maze.getHeight() bool elements initialized to false

	solve(maze, mazeSolution, isVisited);	//begin solving
}




void mSolver::solve(const Maze& maze, MazeSolution& mazeSolution, std::vector<std::vector<bool>> isVisited)
{
	int x = mazeSolution.getCurrentCell().first;	//gets current cell's x value
	int y = mazeSolution.getCurrentCell().second;	//gets current cell's y value
	std::vector<Direction> nxtMove = nextMove(x, y, isVisited, maze); //contins Direction elements of possible moves
	int numOfMoves = nxtMove.size();
	isVisited[x][y] = true;	//marks cell at (x,y) as visited

	if(mazeSolution.isComplete())
	{
		return;	//if maze is solved, return from function
	}

	if(numOfMoves == 0)	//hits a dead end
	{
		mazeSolution.backUp(); //backs up to most recent cell
		solve(maze, mazeSolution, isVisited);	//recursively call solve()
	}
	else
	{
		if(nxtMove.at(0) == Direction::up)	//if first element in nxtMove is up...
		{
			mazeSolution.extend(Direction::up);		//extend up
			solve(maze, mazeSolution, isVisited);	//recursively call using the next currentCell
		}

		if(nxtMove.at(0) == Direction::down)
		{
			mazeSolution.extend(Direction::down);
			solve(maze, mazeSolution, isVisited);
		}

		if(nxtMove.at(0) == Direction::right)
		{
			mazeSolution.extend(Direction::right);
			solve(maze, mazeSolution, isVisited);
		}

		if(nxtMove.at(0) == Direction::left)
		{
			mazeSolution.extend(Direction::left);
			solve(maze, mazeSolution, isVisited);
		}
	}

	return;
	
}

std::vector<Direction> mSolver::nextMove(int x, int y, std::vector<std::vector<bool>>& isVisited, const Maze& maze)
{


	std::vector<Direction> possibleMoves; //declare local vector

	if((y+1) <= (maze.getHeight() - 1) && isVisited[x][y+1] == false && !maze.wallExists(x, y, Direction::down))	//if cell has not been visited and is not a bottom row edge case
	{																												//and if there is no bottom wall
		possibleMoves.push_back(Direction::down);
	}

	if((x+1) <= (maze.getWidth() - 1) && isVisited[x+1][y] == false && !maze.wallExists(x, y, Direction::right))	//if cell has not been visited and is not a right column edge case
	{																												//and if there is no right wall
		possibleMoves.push_back(Direction::right);
	}

	if((x-1) >= 0 && isVisited[x-1][y] == false && !maze.wallExists(x, y, Direction::left))	//if cell has not been visited and is not a left column edge case
	{																						//and if there is no left wall
		possibleMoves.push_back(Direction::left);
	}

	if((y-1) >= 0 && isVisited[x][y-1] == false && !maze.wallExists(x, y, Direction::up))	//if cell has not been visited and is not top row edge case
	{																						//and if there is no top wall
		possibleMoves.push_back(Direction::up);
	}

	return possibleMoves; //return vector with possible Directions stored in it

}


