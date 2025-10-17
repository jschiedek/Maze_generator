// CMakeProject1.h: Soubor k zahrnutí pro standardní systémové soubory k zahrnutí
// nebo soubory k zahrnutí specifické pro projekt.

#pragma once

#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <queue>

//definice stavu bunky pro reseni bludiste
#define VISITED 2
#define UNVISITED 1
#define NOTPREPARED 0

//mozna nebude potreba
#define BASIC 0
#define STARTING 1
#define FINISHING 2

//stav zdi mezi bunkami
#define OPEN 1
#define CLOSED 0

struct Position
{
	size_t rowPos;
	size_t columnPos;
};

struct Walls
{
	bool left = CLOSED;
	bool top = CLOSED;
	bool right = CLOSED;
	bool down = CLOSED;

};

struct Cell
{
	Position position;

	int status = NOTPREPARED;
	//bool startfinish = BASIC; //mozna nebude potreba

	Cell* leftNeighbour = nullptr;
	Cell* topNeighbour = nullptr;
	Cell* rightNeighbour = nullptr;
	Cell* downNeighbour = nullptr;

	Walls walls;

	int depth = 0;
};

class Generator
{
public:
	Generator(size_t rows, size_t cols);
	~Generator();
	void Generate_Maze_For_RB();
	void Generate_Maze_For_BFS();

	size_t getRows();
	size_t getColumns();
	Position getStart();
	Position getFinish();
	
	Cell** Matrix;

private:
	size_t rows;
	size_t columns;

	Position start;
	Position finish;
};

void drawGen(Generator gen);

void Recursive_Backtrack_Solve(Generator gen);

bool RB_Algorithm(Cell**& matrix, Position end, std::vector<Position>& path);

void BFS_Solve(Generator gen);

bool BFS_Algorithm(Cell**& matrix, Position end, std::vector<Position> &path);

bool BFS_Backtracking(Cell**& matrix, Position end, std::vector<Position>& path, int& max_depth, int& depth);

