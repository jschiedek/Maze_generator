
#include "Maze_Generator.h"

using std::rand;

int main()
{
	Generator gen(10, 20);

	//gen.Generate_Maze_For_RB();
	//Recursive_Backtrack_Solve(gen);

	gen.Generate_Maze_For_BFS();
	BFS_Solve(gen);



	//drawGen(gen);

	return 0;
}

Generator::Generator(size_t rows, size_t cols) : rows(rows), columns(cols)
{

	Matrix = new Cell * [rows];

	for (size_t i = 0; i < rows; i++)
	{
		Matrix[i] = new Cell[columns];
	}
	this->start.rowPos = 0;
	this->start.columnPos = columns / 2 + columns % 2;

	this->finish.rowPos = this->rows - 1;
	this->finish.columnPos = rand() % columns;

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			Matrix[i][j].position.rowPos = i;
			Matrix[i][j].position.columnPos = j;
		}
	}


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					Matrix[i][j].leftNeighbour = nullptr;
					Matrix[i][j].topNeighbour = nullptr;
					Matrix[i][j].rightNeighbour = &Matrix[0][j+1];
					Matrix[i][j].downNeighbour = &Matrix[i+1][j];

				}
				else if (j == columns - 1)
				{
					Matrix[i][j].rightNeighbour = nullptr;
					Matrix[i][j].topNeighbour = nullptr;
					Matrix[i][j].leftNeighbour = &Matrix[i][j - 1];
					Matrix[i][j].downNeighbour = &Matrix[i + 1][j];
				}
				else
				{
					Matrix[i][j].topNeighbour = nullptr;
					Matrix[i][j].leftNeighbour = &Matrix[i][j - 1];
					Matrix[i][j].rightNeighbour = &Matrix[i][j + 1];
					Matrix[i][j].downNeighbour = &Matrix[i + 1][j];
				}
				
				
			}

			else if (i == rows - 1)
			{
				if (j == 0)
				{
					Matrix[i][j].leftNeighbour = nullptr;
					Matrix[i][j].topNeighbour = &Matrix[i - 1][j];
					Matrix[i][j].rightNeighbour = &Matrix[i][j + 1];
					Matrix[i][j].downNeighbour = nullptr;

				}
				else if (j == columns - 1)
				{
					Matrix[i][j].leftNeighbour = &Matrix[i][j - 1];
					Matrix[i][j].topNeighbour = &Matrix[i - 1][j];
					Matrix[i][j].rightNeighbour = nullptr;
					Matrix[i][j].downNeighbour = nullptr;
				}
				else
				{
					Matrix[i][j].topNeighbour = &Matrix[i - 1][j];
					Matrix[i][j].leftNeighbour = &Matrix[i][j - 1];
					Matrix[i][j].rightNeighbour = &Matrix[i][j + 1];
					Matrix[i][j].downNeighbour = nullptr;
				}
			}
			
			else
			{
				if (j == 0)
				{
					Matrix[i][j].leftNeighbour = nullptr;
					Matrix[i][j].topNeighbour = &Matrix[i - 1][j];
					Matrix[i][j].rightNeighbour = &Matrix[i][j + 1];
					Matrix[i][j].downNeighbour = &Matrix[i + 1][j];

				}
				else if (j == columns - 1)
				{
					Matrix[i][j].leftNeighbour = &Matrix[i][j - 1];
					Matrix[i][j].topNeighbour = &Matrix[i - 1][j];
					Matrix[i][j].rightNeighbour = nullptr;
					Matrix[i][j].downNeighbour = &Matrix[i - 1][j];
				}
				else
				{
					Matrix[i][j].topNeighbour = &Matrix[i - 1][j];
					Matrix[i][j].leftNeighbour = &Matrix[i][j - 1];
					Matrix[i][j].rightNeighbour = &Matrix[i][j + 1];
					Matrix[i][j].downNeighbour = &Matrix[i + 1][j];
				}
			}
			
		}
		
	}
}

Generator::~Generator()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			Matrix[i][j].downNeighbour = nullptr;
			Matrix[i][j].leftNeighbour = nullptr;
			Matrix[i][j].topNeighbour = nullptr;
			Matrix[i][j].rightNeighbour = nullptr;
		}
	}
}


//funkce na vytvoreni bludiste k reseni
void Generator::Generate_Maze_For_RB()
{
	std::stack<Cell*> zasobnik;

	zasobnik.push(&Matrix[start.rowPos][start.columnPos]);
	
	while (zasobnik.size() != 0)
	{
		Cell* currentCell = zasobnik.top();
		currentCell->status = UNVISITED;
		int num = rand() % 4;

		if (num == 0)
		{
			if (currentCell->leftNeighbour != nullptr && currentCell->leftNeighbour->status == NOTPREPARED)
			{
				zasobnik.push(&Matrix[currentCell->position.rowPos][currentCell->position.columnPos - 1]);

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.left = OPEN;
				Matrix[currentCell->position.rowPos][currentCell->position.columnPos - 1].walls.right = OPEN;
			}
			else if (currentCell->topNeighbour != nullptr && currentCell->topNeighbour->status == NOTPREPARED)
			{
				zasobnik.push(&Matrix[currentCell->position.rowPos - 1][currentCell->position.columnPos]);

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.top = OPEN;
				Matrix[currentCell->position.rowPos - 1][currentCell->position.columnPos].walls.down = OPEN;
			}
			else if (currentCell->rightNeighbour != nullptr && currentCell->rightNeighbour->status == NOTPREPARED)
			{
				zasobnik.push(&Matrix[currentCell->position.rowPos][currentCell->position.columnPos + 1]);

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.right = OPEN;
				Matrix[currentCell->position.rowPos][currentCell->position.columnPos + 1].walls.left = OPEN;
			}
			else if (currentCell->downNeighbour != nullptr && currentCell->downNeighbour->status == NOTPREPARED)
			{
				zasobnik.push(&Matrix[currentCell->position.rowPos + 1][currentCell->position.columnPos]);

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.down = OPEN;
				Matrix[currentCell->position.rowPos + 1][currentCell->position.columnPos].walls.top = OPEN;
			}
			else
			{
				zasobnik.pop();
			}
		}
		else if (num == 1)
		{
			
			if (currentCell->rightNeighbour != nullptr && currentCell->rightNeighbour->status == NOTPREPARED)
			{
				zasobnik.push(&Matrix[currentCell->position.rowPos][currentCell->position.columnPos + 1]);

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.right = OPEN;
				Matrix[currentCell->position.rowPos][currentCell->position.columnPos + 1].walls.left = OPEN;
			}
			else if (currentCell->leftNeighbour != nullptr && currentCell->leftNeighbour->status == NOTPREPARED)
			{
				zasobnik.push(&Matrix[currentCell->position.rowPos][currentCell->position.columnPos - 1]);

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.left = OPEN;
				Matrix[currentCell->position.rowPos][currentCell->position.columnPos - 1].walls.right = OPEN;
			}

			else if (currentCell->downNeighbour != nullptr && currentCell->downNeighbour->status == NOTPREPARED)
			{
				zasobnik.push(&Matrix[currentCell->position.rowPos + 1][currentCell->position.columnPos]);

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.down = OPEN;
				Matrix[currentCell->position.rowPos + 1][currentCell->position.columnPos].walls.top = OPEN;
			}
			
			else if (currentCell->topNeighbour != nullptr && currentCell->topNeighbour->status == NOTPREPARED)
			{
				zasobnik.push(&Matrix[currentCell->position.rowPos - 1][currentCell->position.columnPos]);

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.top = OPEN;
				Matrix[currentCell->position.rowPos - 1][currentCell->position.columnPos].walls.down = OPEN;
			}
			else
			{
				zasobnik.pop();
			}
		}
		else if (num == 2)
		{
			if (currentCell->downNeighbour != nullptr && currentCell->downNeighbour->status == NOTPREPARED)
			{
				zasobnik.push(&Matrix[currentCell->position.rowPos + 1][currentCell->position.columnPos]);

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.down = OPEN;
				Matrix[currentCell->position.rowPos + 1][currentCell->position.columnPos].walls.top = OPEN;
			}
			else if (currentCell->leftNeighbour != nullptr && currentCell->leftNeighbour->status == NOTPREPARED)
			{
				zasobnik.push(&Matrix[currentCell->position.rowPos][currentCell->position.columnPos - 1]);

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.left = OPEN;
				Matrix[currentCell->position.rowPos][currentCell->position.columnPos - 1].walls.right = OPEN;
			}
			else if (currentCell->rightNeighbour != nullptr && currentCell->rightNeighbour->status == NOTPREPARED)
			{
				zasobnik.push(&Matrix[currentCell->position.rowPos][currentCell->position.columnPos + 1]);

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.right = OPEN;
				Matrix[currentCell->position.rowPos][currentCell->position.columnPos + 1].walls.left = OPEN;
			}

			else if (currentCell->topNeighbour != nullptr && currentCell->topNeighbour->status == NOTPREPARED)
			{
				zasobnik.push(&Matrix[currentCell->position.rowPos - 1][currentCell->position.columnPos]);

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.top = OPEN;
				Matrix[currentCell->position.rowPos - 1][currentCell->position.columnPos].walls.down = OPEN;
			}
			
			else
			{
				zasobnik.pop();
			}
		}
		else if (num == 3)
		{
			if (currentCell->topNeighbour != nullptr && currentCell->topNeighbour->status == NOTPREPARED)
			{
				zasobnik.push(&Matrix[currentCell->position.rowPos - 1][currentCell->position.columnPos]);

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.top = OPEN;
				Matrix[currentCell->position.rowPos - 1][currentCell->position.columnPos].walls.down = OPEN;
			}
			
			else if (currentCell->leftNeighbour != nullptr && currentCell->leftNeighbour->status == NOTPREPARED)
			{
				zasobnik.push(&Matrix[currentCell->position.rowPos][currentCell->position.columnPos - 1]);

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.left = OPEN;
				Matrix[currentCell->position.rowPos][currentCell->position.columnPos - 1].walls.right = OPEN;
			}
			else if (currentCell->downNeighbour != nullptr && currentCell->downNeighbour->status == NOTPREPARED)
			{
				zasobnik.push(&Matrix[currentCell->position.rowPos + 1][currentCell->position.columnPos]);

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.down = OPEN;
				Matrix[currentCell->position.rowPos + 1][currentCell->position.columnPos].walls.top = OPEN;
			}
			else if (currentCell->rightNeighbour != nullptr && currentCell->rightNeighbour->status == NOTPREPARED)
			{
				zasobnik.push(&Matrix[currentCell->position.rowPos][currentCell->position.columnPos + 1]);

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.right = OPEN;
				Matrix[currentCell->position.rowPos][currentCell->position.columnPos + 1].walls.left = OPEN;
			}
			else
			{
				zasobnik.pop();
			}
		}
		
	}
}


void Generator::Generate_Maze_For_BFS()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			Cell* currentCell = &Matrix[i][j];
			currentCell->status = UNVISITED;

			int num = rand() % 2;

			if (currentCell->leftNeighbour != nullptr && currentCell->walls.left == CLOSED && num == 1)
			{

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.left = OPEN;
				Matrix[currentCell->position.rowPos][currentCell->position.columnPos - 1].walls.right = OPEN;
			}

			num = rand() % 2;

			if (currentCell->topNeighbour != nullptr && currentCell->walls.top == CLOSED && num == 1)
			{

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.top = OPEN;
				Matrix[currentCell->position.rowPos - 1][currentCell->position.columnPos].walls.down = OPEN;
			}

			num = rand() % 2;

			if (currentCell->rightNeighbour != nullptr && currentCell->walls.right == CLOSED && num == 1)
			{

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.right = OPEN;
				Matrix[currentCell->position.rowPos][currentCell->position.columnPos + 1].walls.left = OPEN;
			}

			num = rand() % 2;

			if (currentCell->downNeighbour != nullptr && currentCell->walls.down == CLOSED && num == 1)
			{

				Matrix[currentCell->position.rowPos][currentCell->position.columnPos].walls.down = OPEN;
				Matrix[currentCell->position.rowPos + 1][currentCell->position.columnPos].walls.top = OPEN;
			}
		}
	}
}

size_t Generator::getRows()
{
	return this->rows;
}

size_t Generator::getColumns()
{
	return this->columns;
}

Position Generator::getStart()
{
	return this->start;
}

Position Generator::getFinish()
{
	return this->finish;
}

//funkce k vykresleni bludiste
void drawGen(Generator gen)
{
	std::vector<std::vector<char>> matrix(gen.getRows() * 2 + 1, std::vector<char>(gen.getColumns() * 2 + 1, 219));

	matrix[gen.getStart().rowPos][(gen.getStart().columnPos * 2) + 1] = ' ';
	matrix[gen.getFinish().rowPos * 2 + 2][(gen.getFinish().columnPos * 2) + gen.getFinish().columnPos % 2] = ' ';

	for (int row = 1; row < matrix.size() - 1; row++)
	{
		for (int col = 0; col < matrix.at(0).size(); col++)
		{
			if ((col+1) % 2 == 0) {
				matrix[row][col] = ' ';
			}
		}
		row++;
	}

	for (int i = 0; i < gen.getRows(); i++)
	{
		for (int j = 0; j < gen.getColumns(); j++)
		{
			if (gen.Matrix[i][j].walls.left == OPEN && gen.Matrix[i][j].leftNeighbour != nullptr)
			{
				matrix[i * 2 + 1][j * 2] = ' ';
			}
			if (gen.Matrix[i][j].walls.top == OPEN && gen.Matrix[i][j].topNeighbour != nullptr)
			{
				matrix[i * 2][j * 2 + 1] = ' ';
			}
			if (gen.Matrix[i][j].walls.right == OPEN && gen.Matrix[i][j].rightNeighbour != nullptr)
			{
				matrix[i * 2 + 1][j * 2 + 1 + 1] = ' ';
			}
			if (gen.Matrix[i][j].walls.down == OPEN && gen.Matrix[i][j].downNeighbour != nullptr)
			{
				matrix[i * 2 + 1 + 1][j * 2 + 1] = ' ';
			}
		}
	}

	std::cout << "\n";
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix.at(0).size(); ++j) {
			std::cout << matrix[i][j];
		}
		std::cout << '\n';
	}
}

//funkce k vyreseni bludiste RB
void Recursive_Backtrack_Solve(Generator gen)
{
	std::vector<Position> path;
	path.push_back(gen.getStart());
	RB_Algorithm(gen.Matrix, gen.getFinish(), path);

	std::vector<std::vector<char>> matrix(gen.getRows() * 2 + 1, std::vector<char>(gen.getColumns() * 2 + 1, 219));

	matrix[gen.getStart().rowPos][(gen.getStart().columnPos * 2) + 1] = 178;
	matrix[gen.getFinish().rowPos * 2 + 2][(gen.getFinish().columnPos * 2) + gen.getFinish().columnPos % 2] = 178;

	
	for (int row = 1; row < matrix.size() - 1; row++)
	{
		for (int col = 0; col < matrix.at(0).size(); col++)
		{
			if ((col + 1) % 2 == 0) {
				matrix[row][col] = ' ';
			}
		}
		row++;
	
	}

	for (int i = 0; i < gen.getRows(); i++)
	{
		for (int j = 0; j < gen.getColumns(); j++)
		{
			if (gen.Matrix[i][j].walls.left == OPEN)
			{
				matrix[i * 2 + 1][j * 2] = ' ';
			}
			if (gen.Matrix[i][j].walls.top == OPEN)
			{
				matrix[i * 2][j * 2 + 1] = ' ';
			}
			if (gen.Matrix[i][j].walls.right == OPEN)
			{
				matrix[i * 2 + 1][j * 2 + 1 + 1] = ' ';
			}
			if (gen.Matrix[i][j].walls.down == OPEN)
			{
				matrix[i * 2 + 1 + 1][j * 2 + 1] = ' ';
			}
			std::cout << "\n";
		}
	}

	for (int i = 0; i < path.size() - 1; i++)
	{
		matrix[path.at(i).rowPos * 2 + 1][path.at(i).columnPos * 2 + 1] = 178;

		if (path.at(i + 1).rowPos > path.at(i).rowPos)
		{
			matrix[path.at(i).rowPos * 2 + 2][path.at(i).columnPos * 2 + 1] = 178;
		}
		else if (path.at(i + 1).columnPos > path.at(i).columnPos)
		{
			matrix[path.at(i).rowPos * 2 + 1][path.at(i).columnPos * 2 + 2] = 178;
		}
		else if (path.at(i + 1).rowPos < path.at(i).rowPos)
		{
			matrix[path.at(i).rowPos * 2][path.at(i).columnPos * 2 + 1] = 178;
		}
		else if (path.at(i + 1).columnPos < path.at(i).columnPos)
		{
			matrix[path.at(i).rowPos * 2 + 1][path.at(i).columnPos * 2] = 178;
		}
		
		if (i == path.size() - 2)
		{
			matrix[path.at(i + 1).rowPos * 2 + 1][path.at(i + 1).columnPos * 2 + 1] = 178;
		}

		system("cls");

		for (int i = 0; i < matrix.size(); ++i) {
			for (int j = 0; j < matrix.at(0).size(); ++j) {
				std::cout << matrix[i][j];
			}
			std::cout << '\n';
		}

		std::this_thread::sleep_for(std::chrono::microseconds(800));
	
	}

	for (int i = 0; i < path.size(); i++)
	{
		path.pop_back();
	}
}
//vyuzivani rekurze k reeni bludiste
bool RB_Algorithm(Cell** &matrix, Position end, std::vector<Position> &path)
{
	
	Position pos = path.back();
	if (matrix[pos.rowPos][pos.columnPos].status == UNVISITED)
	{
		matrix[pos.rowPos][pos.columnPos].status = VISITED;
	}
	
	if (path.empty())
	{
		return false;
	}
	
	if( pos.rowPos == end.rowPos && pos.columnPos == end.columnPos)
	{
		return true;
	}
	if (matrix[pos.rowPos][pos.columnPos].walls.left == OPEN && matrix[pos.rowPos][pos.columnPos - 1].status == UNVISITED)
	{
		path.push_back(matrix[pos.rowPos][pos.columnPos - 1].position);
		if (RB_Algorithm(matrix, end, path) == true)
		{
			return true;
		};
	}
	if (matrix[pos.rowPos][pos.columnPos].walls.top == OPEN && matrix[pos.rowPos - 1][pos.columnPos].status == UNVISITED)
	{
		path.push_back(matrix[pos.rowPos - 1][pos.columnPos].position);
		if (RB_Algorithm(matrix, end, path) == true)
		{
			return true;
		};
	}
	if (matrix[pos.rowPos][pos.columnPos].walls.right == OPEN && matrix[pos.rowPos][pos.columnPos + 1].status == UNVISITED)
	{
		path.push_back(matrix[pos.rowPos][pos.columnPos + 1].position);
		if (RB_Algorithm(matrix, end, path) == true)
		{
			return true;
		};
	}
	if (matrix[pos.rowPos][pos.columnPos].walls.down == OPEN && matrix[pos.rowPos + 1][pos.columnPos].status == UNVISITED)
	{
		path.push_back(matrix[pos.rowPos + 1][pos.columnPos].position);
		if (RB_Algorithm(matrix, end, path) == true)
		{
			return true;
		};
	}
	
	path.pop_back();

	return false;
}

//////////////////////
//////////////////////
//////////////////////
//////////////////////
//////////////////////


void BFS_Solve(Generator gen)
{
	std::vector<Position> path;
	path.push_back(gen.getStart());
	
	BFS_Algorithm(gen.Matrix, gen.getFinish(), path);

	std::vector<std::vector<char>> matrix(gen.getRows() * 2 + 1, std::vector<char>(gen.getColumns() * 2 + 1, 219));

	matrix[gen.getStart().rowPos][(gen.getStart().columnPos * 2) + 1] = 178;
	matrix[gen.getFinish().rowPos * 2 + 2][(gen.getFinish().columnPos * 2) + gen.getFinish().columnPos % 2] = 178;


	for (int row = 1; row < matrix.size() - 1; row++)
	{
		for (int col = 0; col < matrix.at(0).size(); col++)
		{
			if ((col + 1) % 2 == 0) {
				matrix[row][col] = ' ';
			}
		}
		row++;

	}

	for (int i = 0; i < gen.getRows(); i++)
	{
		for (int j = 0; j < gen.getColumns(); j++)
		{
			if (gen.Matrix[i][j].walls.left == OPEN)
			{
				matrix[i * 2 + 1][j * 2] = ' ';
			}
			if (gen.Matrix[i][j].walls.top == OPEN)
			{
				matrix[i * 2][j * 2 + 1] = ' ';
			}
			if (gen.Matrix[i][j].walls.right == OPEN)
			{
				matrix[i * 2 + 1][j * 2 + 1 + 1] = ' ';
			}
			if (gen.Matrix[i][j].walls.down == OPEN)
			{
				matrix[i * 2 + 1 + 1][j * 2 + 1] = ' ';
			}
			std::cout << "\n";
		}
	}

	for (int i = 0; i < path.size() - 1; i++)
	{
		matrix[path.at(i).rowPos * 2 + 1][path.at(i).columnPos * 2 + 1] = 178;

		if (path.at(i + 1).rowPos > path.at(i).rowPos)
		{
			matrix[path.at(i).rowPos * 2 + 2][path.at(i).columnPos * 2 + 1] = 178;
		}
		else if (path.at(i + 1).columnPos > path.at(i).columnPos)
		{
			matrix[path.at(i).rowPos * 2 + 1][path.at(i).columnPos * 2 + 2] = 178;
		}
		else if (path.at(i + 1).rowPos < path.at(i).rowPos)
		{
			matrix[path.at(i).rowPos * 2][path.at(i).columnPos * 2 + 1] = 178;
		}
		else if (path.at(i + 1).columnPos < path.at(i).columnPos)
		{
			matrix[path.at(i).rowPos * 2 + 1][path.at(i).columnPos * 2] = 178;
		}

		if (i == path.size() - 2)
		{
			matrix[path.at(i + 1).rowPos * 2 + 1][path.at(i + 1).columnPos * 2 + 1] = 178;
		}

		system("cls");

		for (int i = 0; i < matrix.size(); ++i) {
			for (int j = 0; j < matrix.at(0).size(); ++j) {
				std::cout << matrix[i][j];
			}
			std::cout << '\n';
		}

		std::this_thread::sleep_for(std::chrono::microseconds(800));

	}

	for (int i = 0; i < path.size(); i++)
	{
		path.pop_back();
	}
}


bool BFS_Algorithm(Cell**& matrix, Position end, std::vector<Position> &path)
{

	Position pos = path.back();

	std::queue<Position> nodes;

	nodes.push(pos);

	int counter = 0;
	int anticounter = 0;

	if (matrix[pos.rowPos][pos.columnPos].status == UNVISITED)
	{
		matrix[pos.rowPos][pos.columnPos].status = VISITED;
	}

	int deep = 1;

	while (!nodes.empty())
	{
		pos = nodes.front();

		Position after = nodes.front();
	
		nodes.pop();


		if (matrix[pos.rowPos][pos.columnPos].position.columnPos == end.columnPos && matrix[pos.rowPos][pos.columnPos].position.rowPos == end.rowPos)
		{
			counter = matrix[pos.rowPos][pos.columnPos].depth;

			while (!nodes.empty())
			{
				nodes.pop();
			}
		}

		if (matrix[pos.rowPos][pos.columnPos].walls.left == OPEN && matrix[pos.rowPos][pos.columnPos - 1].status == UNVISITED)
		{
			nodes.push(matrix[pos.rowPos][pos.columnPos - 1].position);
			matrix[pos.rowPos][pos.columnPos - 1].status = VISITED;
			matrix[pos.rowPos][pos.columnPos - 1].depth = deep;

		}
		if (matrix[pos.rowPos][pos.columnPos].walls.top == OPEN && matrix[pos.rowPos - 1][pos.columnPos].status == UNVISITED)
		{
			nodes.push(matrix[pos.rowPos - 1][pos.columnPos].position);
			matrix[pos.rowPos - 1][pos.columnPos].status = VISITED;
			matrix[pos.rowPos - 1][pos.columnPos].depth = deep;
			
		}
		if (matrix[pos.rowPos][pos.columnPos].walls.right == OPEN && matrix[pos.rowPos][pos.columnPos + 1].status == UNVISITED)
		{
			nodes.push(matrix[pos.rowPos][pos.columnPos + 1].position);
			matrix[pos.rowPos][pos.columnPos + 1].status = VISITED;
			matrix[pos.rowPos][pos.columnPos + 1].depth = deep;
			
		}
		if (matrix[pos.rowPos][pos.columnPos].walls.down == OPEN && matrix[pos.rowPos + 1][pos.columnPos].status == UNVISITED)
		{
			nodes.push(matrix[pos.rowPos + 1][pos.columnPos].position);
			matrix[pos.rowPos + 1][pos.columnPos].status = VISITED;
			matrix[pos.rowPos + 1][pos.columnPos].depth = deep;

		}



		if(!nodes.empty())
		{
			after = nodes.front();
		}

		if (matrix[after.rowPos][after.columnPos].depth > matrix[pos.rowPos][pos.columnPos].depth)
		{
			deep++;
		}
	}


	if (counter != 0)
	{
		int BacktrackDepth = 0;
		BFS_Backtracking(matrix, end, path, counter, BacktrackDepth);
		return true;
	}
	else
	{
		std::cout << "Nelze vyresit";
		return false;
	}
}



bool BFS_Backtracking(Cell**& matrix, Position end, std::vector<Position>& path, int &max_depth, int &depth)
{

	Position pos = path.back();

	if ( depth > max_depth)
	{
		depth--;
		path.pop_back();
		return false;
	}

	if (pos.rowPos == end.rowPos && pos.columnPos == end.columnPos)
	{
		return true;
	}
	if (matrix[pos.rowPos][pos.columnPos].walls.left == OPEN)
	{
		depth++;
		path.push_back(matrix[pos.rowPos][pos.columnPos - 1].position);
		if (BFS_Backtracking(matrix, end, path, max_depth, depth) == true)
		{
			return true;
		};
	}
	if (matrix[pos.rowPos][pos.columnPos].walls.top == OPEN)
	{
		depth++;
		path.push_back(matrix[pos.rowPos - 1][pos.columnPos].position);
		if (BFS_Backtracking(matrix, end, path, max_depth, depth) == true)
		{
			return true;
		};
	}
	if (matrix[pos.rowPos][pos.columnPos].walls.right == OPEN)
	{
		depth++;
		path.push_back(matrix[pos.rowPos][pos.columnPos + 1].position);
		if (BFS_Backtracking(matrix, end, path, max_depth, depth) == true)
		{
			return true;
		};
	}
	if (matrix[pos.rowPos][pos.columnPos].walls.down == OPEN)
	{
		depth++;
		path.push_back(matrix[pos.rowPos + 1][pos.columnPos].position);
		if (BFS_Backtracking(matrix, end, path, max_depth, depth) == true)
		{
			return true;
		};
	}

	path.pop_back();

	depth--;
	return false;
}
