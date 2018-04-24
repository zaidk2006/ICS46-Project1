#include <ics46/factory/DynamicFactory.hpp>
#include "maze1.hpp"
#include <iostream>
#include <random>
#include <vector>
#include "Direction.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, maze1, "Zaid's Maze (Required)");

maze1::maze1()
{

}

std::random_device device;		//entropy source
std::default_random_engine engine{device()};

void maze1::generateMaze(Maze& maze)
{
    
	maze.addAllWalls();	//adds all walls

	std::vector<std::vector<int>> isVisited(maze.getWidth(), std::vector<int> (maze.getHeight(), 0)); //creates a vector that contains maze.getWidth() vectors of ints
																										   //that contain maze.getHeight() int elements initialized to 0
																										   // 0 means not visited, 1 means visited

	std::vector<std::pair<int,int>> visitedCells;	//a vector that stores type std::pair<int,int> 
	std::uniform_int_distribution<int> x{0, static_cast<int>(maze.getWidth()) - 1};
	std::uniform_int_distribution<int> y{0, static_cast<int>(maze.getHeight()) - 1};
	done = false;
	do
	{
		createMaze(x(engine), y(engine), isVisited, visitedCells, maze);	//loop until done = true;
		
	}while(!done);
}

bool maze1::createMaze(int x,int y, std::vector<std::vector<int>>& isVisited, std::vector<std::pair<int,int>>& visitedCells, Maze& maze)
{
	std::pair<int, int> pairs;	//stores x and y coordinates
	std::vector<Direction> nxtMove = nextMove(x, y, isVisited, maze);	//stores possible Direction
	int numOfMoves = nxtMove.size();	//number of elements in nxtMove
	int randomChoice = 0;
	isVisited[x][y] = 1;	//marks cell at (x,y) to visited
	
	if(numOfMoves == 0)	//hits dead end
	{

		if(visitedCells.size() > 1)	//execute if there are more than 1 elements in visitedCells
		{	
			visitedCells.pop_back(); // return to most recent coordinates
			visitedCells.shrink_to_fit();	//resize vector to match number of elements
			createMaze(visitedCells.back().first, visitedCells.back().second, isVisited, visitedCells, maze); //recursively call createMaze
		}
		
		else //hits dead end and there is only one element in visitedCells (BASE CASE)
		{
			done = true;	//indicate that the maze generator is finished
			return done;
		}
	}

	if(!done)	//if not done, execute
	{
			
		
		std::uniform_int_distribution<int> rand{0, numOfMoves - 1}; // create a uniform distribution of numbers between and numOfMoves - 1
		randomChoice = rand(engine);	//generate a random number from the distribution

		if(nxtMove.at(randomChoice) == Direction::right)		//randomly chosen element is right
		{
			maze.removeWall(x, y, Direction::right);			//remove right wall
			pairs.first = x;									//set first element in pairs to x
			pairs.second = y;									//set second element in pairs to y
			visitedCells.push_back(pairs);						//push back pairs in visitedCells
			createMaze(++x, y, isVisited, visitedCells, maze);	//recursive call
		}
		if(nxtMove.at(randomChoice) == Direction::left)	
		{
			maze.removeWall(x, y, Direction::left);
			pairs.first = x;
			pairs.second = y;
			visitedCells.push_back(pairs);
			createMaze(--x, y, isVisited, visitedCells, maze);
		}
		if(nxtMove.at(randomChoice) == Direction::up)
		{
			maze.removeWall(x, y, Direction::up);
			pairs.first = x;
			pairs.second = y;
			visitedCells.push_back(pairs);
			createMaze(x, --y, isVisited, visitedCells, maze);
		}
		if(nxtMove.at(randomChoice) == Direction::down)
		{
			maze.removeWall(x, y, Direction::down);
			pairs.first = x;
			pairs.second = y;
			visitedCells.push_back(pairs);	
			createMaze(x, ++y, isVisited, visitedCells, maze);
		}

	}

	return done; //return done
}
	

std::vector<Direction> maze1::nextMove(int x, int y, std::vector<std::vector<int>>& isVisited, Maze& maze)
{


	std::vector<Direction> possibleMoves; //declare local vector

	if((y+1) <= (maze.getHeight() - 1) && isVisited[x][y+1] == 0)	//if cell has not been visited and is not a bottom row edge case
	{
		possibleMoves.push_back(Direction::down);
	}

	if((x+1) <= (maze.getWidth() - 1) && isVisited[x+1][y] == 0)	//if cell has not been visited and is not a right column edge case
	{
		possibleMoves.push_back(Direction::right);
	}

	if((x-1) >= 0 && isVisited[x-1][y] == 0 )	//if cell has not been visited and is not a left column edge case
	{
		possibleMoves.push_back(Direction::left);
	}

	if((y-1) >= 0 && isVisited[x][y-1] == 0 )	//if cell has not been visited and is not top row edge case
	{
		possibleMoves.push_back(Direction::up);
	}

	return possibleMoves; //return vector with possible Directions stored in it

}