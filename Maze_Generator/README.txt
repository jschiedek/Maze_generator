
Jakub Schiedek
SCH0417

MAZE GENERATOR

Generator::Generator(size_t rows, size_t cols)	- konstruktor matice na bludiste
												- obsahuje pocet bunek uvedenych v parametrech konstruktoru
												- jednotlive bunky maji pointery na sousedni


void Generate_Maze_For_RB()	- vyuziva rekurzivni back-tracking pro vytvoreni bludiste
							- zaroven meni stav bunek z NOTPREPARED na UNVISITED
							- vyuziva funkci rand() k urceni postupu prochazeni	- 0	left up right down
																				- 1	right left down up
																				- 2	down left right up
																				- 3	up left down right


void Generate_Maze_For_BFS()	- vyuziva nahodne otevirani sten kazde bunky pro vytvoreni bludiste
								- zaroven meni stav bunek z NOTPREPARED na UNVISITED
								- vyuziva funkci rand() k otevirani pro kazdou stenu	- 0	close
																						- 1	open


void Recursive_Backtrack_Solve(Generator gen)	- vyreseni bludiste RB
												- pouzije funkci RB_Algorithm nize
												- pote vykresli vyresene bludiste



bool RB_Algorithm(Cell**& matrix, Position end, std::vector<Position>& path)	- rekurzivne vola sama sebe
																				- pridava a vyhazuje pozice bunek podle postupu v bludisti
																				- na konci vrati vektor s pozicemi bunek k pruchozu bludiste	


void BFS_Solve(Generator gen)	- vyreseni bludiste BFS
								- pouzije funkci BFS_A
								- pote vykresli vyresene bludiste


bool BFS_Algorithm(Cell**& matrix, Position end, std::vector<Position> &path)	- zjisti pomoci BFS algoritmu nejkratsi cestu k cili
																				- nasledne vola funkci BFS_Backtracking


bool BFS_Backtracking(Cell**& matrix, Position end, std::vector<Position>& path, int& max_depth, int& depth)	- najde pomoci backtrackingu a vzdalenosti k cili nejkratsi cestu
																												- vola sama sebe
																												- na konci vrati path


void drawGen()	- vykresleni matice bludiste po jedne z generovacich funkci
				- pouzita nova matice charu pro dobre zobrazeni zdi mezi bunkami


