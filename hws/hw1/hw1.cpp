#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

//Read grid from input file
void read_grid(std::vector<std::string> & grid, std::string & file_name)
{
	std::ifstream file;
	file.open(file_name.c_str());
	if (!file.good())
	{
		std::cerr << "Can't open " << file_name << " to read.\n";
		exit(1);
	}
	std::string line;
	if (file.is_open())
	{
		while (getline(file, line))
		{
			grid.push_back(line);
		}
	}
}

//Change foreground or background characters ("color")
void replace(std::vector<std::string> & grid, char & take_away, char & take_place)
{
	for (unsigned int i=0; i<grid.size();i++)
	{
		std::replace( grid[i].begin(), grid[i].end(), take_away, take_place );
	}
}

//prints the grid - useful for debugging
void print_grid(std::vector<std::string> & grid)
{
	for (unsigned int i=0;i<grid.size();i++)
	{
		std::cout << grid[i] << std::endl;
	}
}

//dilation
void dilation(std::vector<std::string> & grid, char & foreground)
{
	std::vector<std::string> grid_copy(grid);
	for (unsigned int row=0;row<grid.size();row++)
	{
		for (unsigned int col=0;col<grid[row].size();col++)
		{
			bool dilate = false;
			//center
			if (!(grid[row][col]==foreground))
			{
				//top
				if (!row-1<0)
				{
					if (grid[row-1][col]==foreground) {dilate = true;}
				}
				//bottom
				if (!(row+1>grid.size()-1))
				{
					if (grid[row+1][col]==foreground) {dilate = true;}
				}
				//left
				if (!col-1<0)
				{
					if (grid[row][col-1]==foreground) {dilate = true;}
				}
				//right
				if (!(col+1>grid[row].size()-1))
				{
					if (grid[row][col+1]==foreground) {dilate = true;}
				}

				if (dilate==true) {grid_copy[row][col] = foreground;}
			}
		}
	}
	grid = grid_copy;
}

//erosion
void erosion(std::vector<std::string> & grid, char & foreground, char & background)
{
	std::vector<std::string> grid_copy(grid);
	for (unsigned int row=0;row<grid.size();row++)
	{
		for (unsigned int col=0;col<grid[row].size();col++)
		{
			int erode = 0;
			//center
			if (grid[row][col]==foreground)
			{
				//top
				if (!row-1<0)
				{
					if (grid[row-1][col]==foreground) {erode++;}
				}
				//bottom
				if (!(row+1>grid.size()-1))
				{
					if (grid[row+1][col]==foreground) {erode++;}
				}
				//left
				if (!col-1<0)
				{
					if (grid[row][col-1]==foreground) {erode++;}
				}
				//right
				if (!(col+1>grid[row].size()-1))
				{
					if (grid[row][col+1]==foreground) {erode++;}
				}

				if (erode<4) {grid_copy[row][col] = background;}
			}
		}
	}
	grid = grid_copy;
}

//floodfill
void floodfill(std::vector<std::string> & grid, unsigned int row, unsigned int col, char replacement )
{
	std::vector<std::string> grid_copy(grid);
	char initial = grid[row][col];
	grid_copy[row][col] = replacement;
	for (row = 0;row<grid.size();row++)
	{
		for (col = 0;col<grid[row].size();col++)
		{
			bool flood = false;
			//center
			if (grid[row][col]==initial)
			{
				//top
				if (!row-1<0)
				{
					if (grid_copy[row-1][col]==replacement) {flood=true;}
				}
				//bottom
				if (!(row+1>grid.size()-1))
				{
					if (grid_copy[row+1][col]==replacement) {flood=true;}
				}
				//left
				if (!col-1<0)
				{
					if (grid_copy[row][col-1]==replacement) {flood=true;}
				}
				//right
				if (!(col+1>grid[row].size()-1))
				{
					if (grid_copy[row][col+1]==replacement) {flood=true;}
				}

				if (flood==true) {grid_copy[row][col] = replacement;}
			}
		}
	}
	for (row = grid.size()-1;row>=0;row--)
	{
		for (col = 0;col<grid[row].size();col++)
		{
			bool flood = false;
			//center
			if (grid[row][col]==initial)
			{
				//top
				if (!row-1<0)
				{
					if (grid_copy[row-1][col]==replacement) {flood=true;}
				}
				//bottom
				if (!(row+1>grid.size()-1))
				{
					if (grid_copy[row+1][col]==replacement) {flood=true;}
				}
				//left
				if (!col-1<0)
				{
					if (grid_copy[row][col-1]==replacement) {flood=true;}
				}
				//right
				if (!(col+1>grid[row].size()-1))
				{
					if (grid_copy[row][col+1]==replacement) {flood=true;}
				}

				if (flood==true) {grid_copy[row][col] = replacement;}
			}
		}
		if (row == 0)
		{
			break;
		}
	}
	grid = grid_copy;
}

//write new grid to file
void write_grid(std::vector<std::string> & grid, std::string & output_file)
{
	std::ofstream file;
	file.open(output_file.c_str());
	if (!file.good())
	{
		std::cerr << "Can't open " << output_file << " to write.\n";
		exit(1);
	}
	for (unsigned int i = 0;i<grid.size();i++)
	{
		file << grid[i] << '\n';
	}
	file.close();
}

int main(int argc, char* argv[])
{
	std::string file_name = argv[1];
	std::string output_file = argv[2];
	std::vector<std::string> grid;
	read_grid(grid, file_name);

	if (std::string(argv[3])==std::string("erosion"))
	{
		char foreground = argv[4][0];
		char background = argv[5][0];
		erosion(grid, foreground, background);
	}
	else if (std::string(argv[3])==std::string("dilation"))
	{
		char foreground = argv[4][0];
		dilation(grid, foreground);
	}
	else if (std::string(argv[3])==std::string("replace"))
	{
		char take_away = argv[4][0];
		char take_place = argv[5][0];
		replace(grid, take_away, take_place);
	}
	else if (std::string(argv[3])==std::string("floodfill"))
	{
		char replacement = argv[6][0];
		unsigned int row = std::atoi(argv[4]);
		unsigned int col = std::atoi(argv[5]);
		floodfill(grid, row, col, replacement);
	}
	write_grid(grid, output_file);
	return 0;
}