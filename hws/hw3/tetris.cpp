//File: tetris.cpp
//Purpose: tetris class implementation File

#include "tetris.h"
#include <iostream>

Tetris::Tetris(int the_width) //constructor
{
	width = the_width;

	//integer array for heights
	heights = new int[the_width];
	for (int i=0;i<the_width;i++)
	{
		heights[i] = 0;
	}
	//2D array of characters for board layout
	data = new char*[the_width];
	for (int i=0;i<the_width;i++)
	{
		data[i] = new char[0];
	}

}

int Tetris::get_width() const
{
	return width;
}
int Tetris::get_max_height() const
{
	int max = 0;
	for (int i=0;i<width;i++)
	{
		if (heights[i]>max)
		{
			max = heights[i];
		}
	}
	return max;
}
int Tetris::get_min_height() const
{
	int min = get_max_height();
	for (int i=0;i<width;i++)
	{
		if (heights[i]<min)
		{
			min = heights[i];
		}
	}
	return min;
}
int Tetris::count_squares() const
{
	int squares = 0;
	for (int i=0;i<width;i++)
	{
		for (int j=0;j<heights[i];j++)
		{
			if (data[i][j]!=' ')
			{
				squares++;
			}
		}
	}
	return (squares);
}

void Tetris::add_piece(char shape, int rotation, int location)
{
	if (shape=='I')
	{
		I_block(rotation, location);
	}
	else if (shape=='O')
	{
		O_block(rotation, location);
	}
	else if (shape=='T')
	{
		T_block(rotation,location);
	}
	else if (shape=='Z')
	{
		Z_block(rotation,location);
	}
	else if (shape=='S')
	{
		S_block(rotation,location);
	}
	else if (shape=='L')
	{
		L_block(rotation,location);
	}
	else if (shape=='J')
	{
		J_block(rotation,location);
	}
}
void Tetris::I_block(int rotation, int location)
{
	char *temp_column;

	if (rotation==0 or rotation==180)
	{
		//create temporary copy of old column with space needed for piece
		temp_column = new char[heights[location]+4];
		for (int i=0;i<heights[location];i++)
		{
			temp_column[i] = data[location][i];
		}
		//add peice to temporary column
		for (int i=0;i<4;i++)
		{
			temp_column[heights[location]+i] = 'I';
		}
		//replace old column with new one
		delete [] data[location];
		data[location] = new char[heights[location]+4];
		for (int n=0;n<heights[location]+4;n++)
		{
			data[location][n] = temp_column[n];
		}
		delete [] temp_column;
		//change height value
		heights[location] += 4;
	}
	else if (rotation==90 or rotation==270)
		{
		//find height of piece
		int highest = heights[location];
		for (int i=1;i<4;i++)
		{
			if (heights[location+i]>highest)
			{
				highest = heights[location+i];
			}
		}
		//create, replace, and delete 4 arrays with piece added on top
		for (int i=0;i<4;i++)
		{
			
			if (heights[location+i]!=0)
			{
				temp_column = new char[highest+1];
				for (int j=0;j<heights[location+i];j++)
				{
					temp_column[j] = data[location+i][j];
				}
				if (heights[location+i]<highest)
				{
					for (int n=heights[location+i];n<highest;n++)
					{
						temp_column[n] = ' ';
					}
				}
				temp_column[highest] = 'I';
			}
			else
			{
				temp_column = new char[highest+1];
				for (int j=0;j<(highest);j++)
				{
					temp_column[j] = ' ';
				}
				temp_column[highest] = 'I';
			}
			delete [] data[location+i];
			data[location+i] = new char[highest+1];
			for (int k=0;k<highest+1;k++)
			{
				data[location+i][k] = temp_column[k];
			}
			delete [] temp_column;
			heights[location+i] = highest + 1;
		}
	}
}
void Tetris::O_block(int rotation, int location)
{
	char *temp_column;

	int highest = heights[location];
	if (heights[location+1]>highest)
	{
		highest = heights[location+1];
	}
	for (int i=0;i<2;i++)
	{
		temp_column = new char[highest+2];
		if (heights[location+i]!=0)
		{
			for (int j=0;j<heights[location+i];j++)
			{
				temp_column[j] = data[location+i][j];
			}
			if (heights[location+i]<highest)
			{
				for (int n=heights[location+i];n<highest;n++)
				{
					temp_column[n] = ' ';
				}
			}
			temp_column[highest] = 'O';
			temp_column[highest+1] = 'O';
		}
		else
		{
			for (int j=0;j<highest;j++)
			{
				temp_column[j] = ' ';
			}
			temp_column[highest] = 'O';
			temp_column[highest+1] = 'O';
		}
		delete [] data[location+i];
		data[location+i] = new char[highest+2];
		for (int k=0;k<highest+2;k++)
		{
			data[location+i][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location+i] = highest + 2;
	}
}
void Tetris::T_block(int rotation, int location)
{ 
	int highest;
	char* temp_column;
	if (rotation==0)
	{
		highest = heights[location];
		if (heights[location+2]>highest)
		{
			highest = heights[location+2];
		}
		if (heights[location+1]>highest)
		{
			highest = heights[location+1];
		}
		if (heights[location+1]<highest)
		{
			highest--;
		}
		for (int i=0;i<3;i++)
		{
			temp_column = new char[highest+2];
			if (i!=1)
			{
				if (heights[location+i]!=0)
				{
					for (int j=0;j<heights[location+i];j++)
					{
						temp_column[j] = data[location+i][j];
					}
					if (heights[location+i]<highest+1)
					{
						for (int j=heights[location+i];j<highest+1;j++)
						{
							temp_column[j] = ' '; 
						}
					}
				}
				else
				{
					for (int j=0;j<highest+1;j++)
					{
						temp_column[j] = ' ';
					}
				}
				temp_column[highest+1] = 'T';
			}
			else
			{
				if (heights[location+i]!=0)
				{
					for (int j=0;j<heights[location+i];j++)
					{
						temp_column[j] = data[location+i][j];
					}
					if (heights[location+i]<highest)
					{
						for (int j=heights[location+i];j<highest;j++)
						{
							temp_column[j] = ' '; 
						}
					}
				}
				else
				{
					for (int j=0;j<highest;j++)
					{
						temp_column[j] = ' ';
					}
				}
				temp_column[highest] = 'T';
				temp_column[highest+1] = 'T';
			}
			delete [] data[location+i];
			data[location+i] = new char[highest+2];
			for (int k=0;k<highest+2;k++)
			{
				data[location+i][k] = temp_column[k];
			}
			delete [] temp_column;
			heights[location+i] = highest + 2;
		}
	}
	else if (rotation==180)
	{
		highest = heights[location];
		for (int i=1;i<3;i++)
		{
			if (heights[location+i]>highest)
			{
				highest = heights[i];
			}
		}
		for (int i=0;i<3;i++)
		{
			if (i!=1)
			{
				temp_column = new char[highest+1];
				if (heights[location+i]!=0)
				{
					for (int j=0;j<heights[location+i];j++)
					{
						temp_column[j] = data[location+i][j];
					}
					if (heights[location+i]<highest)
					{
						for (int j=heights[location+i];j<highest;j++)
						{
							temp_column[j] = ' '; 
						}
					}
				}
				else
				{
					for (int j=0;j<highest;j++)
					{
						temp_column[j] = ' ';
					}
				}
				temp_column[highest] = 'T';

				delete [] data[location+i];
				data[location+i] = new char[highest+1];
				for (int k=0;k<highest+1;k++)
				{
					data[location+i][k] = temp_column[k];
				}
				delete [] temp_column;
				heights[location+i] = highest + 1;
			}
			else
			{
				temp_column = new char[highest+2];
				if (heights[location+i]!=0)
				{
					for (int j=0;j<heights[location+i];j++)
					{
						temp_column[j] = data[location+i][j];
					}
					if (heights[location+i]<highest)
					{
						for (int j=heights[location+i];j<highest;j++)
						{
							temp_column[j] = ' '; 
						}
					}
				}
				else
				{
					for (int j=0;j<highest;j++)
					{
						temp_column[j] = ' ';
					}
				}
				temp_column[highest] = 'T';
				temp_column[highest+1] = 'T';

				delete [] data[location+i];
				data[location+i] = new char[highest+2];
				for (int k=0;k<highest+2;k++)
				{
					data[location+i][k] = temp_column[k];
				}
				delete [] temp_column;
				heights[location+i] = highest + 2;
			}
		}

	}
	else if (rotation==270)
	{
		highest = heights[location];
		if (heights[location+1]>highest)
		{
			highest = heights[location+1];
		}
		if (heights[location]<highest)
		{
			highest--;
		}
		temp_column = new char[highest+3];
		if (heights[location]!=0)
		{
			for (int i=0;i<heights[location];i++)
			{
				temp_column[i] = data[location][i];
			}
			if (heights[location]<highest)
			{
				for (int i=heights[location];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest] = 'T';
		temp_column[highest+1] = 'T';
		temp_column[highest+2] = 'T';

		delete [] data[location];
		data[location] = new char[highest+3];
		for (int k=0;k<highest+3;k++)
		{
			data[location][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location] = highest + 3;

		temp_column = new char[highest+2];
		if (heights[location+1]!=0)
		{
			for (int i=0;i<heights[location+1];i++)
			{
				temp_column[i] = data[location+1][i];
			}
			if (heights[location+1]<highest+1)
			{
				for (int i=heights[location+1];i<highest+1;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest+1;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest+1] = 'T';

		delete [] data[location+1];
		data[location+1] = new char[highest+2];
		for (int k=0;k<highest+2;k++)
		{
			data[location+1][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location+1] = highest + 2;		

		
	}
	else if (rotation==90)
	{
		highest = heights[location+1];
		if (heights[location]>highest)
		{
			highest = heights[location];
		}
		if (heights[location+1]<highest)
		{
			highest--;
		}

		temp_column = new char[highest+3];
		if (heights[location+1]!=0)
		{
			for (int i=0;i<heights[location+1];i++)
			{
				temp_column[i] = data[location+1][i];
			}
			if (heights[location+1]<highest)
			{
				for (int i=heights[location+1];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest] = 'T';
		temp_column[highest+1] = 'T';
		temp_column[highest+2] = 'T';

		delete [] data[location+1];
		data[location+1] = new char[highest+3];
		for (int k=0;k<highest+3;k++)
		{
			data[location+1][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location+1] = highest + 3;

		temp_column = new char[highest+2];
		if (heights[location]!=0)
		{
			for (int i=0;i<heights[location];i++)
			{
				temp_column[i] = data[location][i];
			}
			if (heights[location]<highest+1)
			{
				for (int i=heights[location];i<highest+1;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest+1;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest+1] = 'T';

		delete [] data[location];
		data[location] = new char[highest+2];
		for (int k=0;k<highest+2;k++)
		{
			data[location][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location] = highest + 2;	
	}
}
void Tetris::Z_block(int rotation, int location)
{
	int highest;
	char* temp_column;
	if (rotation==0 or rotation==180)
	{
		highest = heights[location];
		if (heights[location+1]>highest)
		{
			highest = heights[location+1];
		}
		if (heights[location+2]>highest)
		{
			highest = heights[location+2];
		}
		if (heights[location+1]<highest)
		{
			highest--;
		}

		//first column
		temp_column = new char[highest+2];
		if (heights[location]!=0)
		{
			for (int i=0;i<heights[location];i++)
			{
				temp_column[i] = data[location][i];
			}
			if (heights[location]<highest+1)
			{
				for (int i=heights[location];i<highest+1;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest+1;i++)
			{
				temp_column[i]=' ';
			}
		}
		temp_column[highest+1] = 'Z';

		delete [] data[location];
		data[location] = new char[highest+2];
		for (int k=0;k<highest+2;k++)
		{
			data[location][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location] = highest + 2;

		//second column
		temp_column = new char[highest+2];
		if (heights[location+1]!=0)
		{
			for (int i=0;i<heights[location+1];i++)
			{
				temp_column[i] = data[location+1][i];
			}
			if (heights[location+1]<highest)
			{
				for (int i=heights[location+1];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i]=' ';
			}
		}
		temp_column[highest] = 'Z';
		temp_column[highest+1] = 'Z';

		delete [] data[location+1];
		data[location+1] = new char[highest+2];
		for (int k=0;k<highest+2;k++)
		{
			data[location+1][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location+1] = highest + 2;

		//third column
		temp_column = new char[highest+1];
		if (heights[location+2]!=0)
		{
			for (int i=0;i<heights[location+2];i++)
			{
				temp_column[i] = data[location+2][i];
			}
			if (heights[location+2]<highest)
			{
				for (int i=heights[location+2];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i]=' ';
			}
		}
		temp_column[highest] = 'Z';

		delete [] data[location+2];
		data[location+2] = new char[highest+1];
		for (int k=0;k<highest+1;k++)
		{
			data[location+2][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location+2] = highest + 1;
	}
	else if (rotation==90 or rotation==270)
	{
		highest = heights[location+1];
		if (heights[location]>highest)
		{
			highest = heights[location];
		}
		if (heights[location]<highest)
		{
			highest--;
		}

		//first column
		temp_column = new char[highest+2];
		if (heights[location]!=0)
		{
			for (int i=0;i<heights[location];i++)
			{
				temp_column[i] = data[location][i];
			}
			if (heights[location]<highest)
			{
				for (int i=heights[location];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest] = 'Z';
		temp_column[highest+1] = 'Z';

		delete [] data[location];
		data[location] = new char[highest+2];
		for (int k=0;k<highest+2;k++)
		{
			data[location][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location] = highest + 2;	

		//second column
		temp_column = new char[highest+3];
		if (heights[location+1]!=0)
		{
			for (int i=0;i<heights[location+1];i++)
			{
				temp_column[i] = data[location+1][i];
			}
			if (heights[location+1]<highest+1)
			{
				for (int i=heights[location+1];i<highest+1;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest+1;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest+1] = 'Z';
		temp_column[highest+2] = 'Z';

		delete [] data[location+1];
		data[location+1] = new char[highest+3];
		for (int k=0;k<highest+3;k++)
		{
			data[location+1][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location+1] = highest + 3;
	}
}
void Tetris::S_block(int rotation, int location)
{
	int highest;
	char* temp_column;
	if (rotation==0 or rotation==180)
	{
		highest = heights[location+2];
		if (heights[location+1]>highest)
		{
			highest = heights[location+2];
		}
		if (heights[location]>highest)
		{
			highest = heights[location];
		}
		if (heights[location+1]<highest)
		{
			highest--;
		}

		//first column
		temp_column = new char[highest+1];
		if (heights[location]!=0)
		{
			for (int i=0;i<heights[location];i++)
			{
				temp_column[i] = data[location][i];
			}
			if (heights[location]<highest)
			{
				for (int i=heights[location];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i]=' ';
			}
		}
		temp_column[highest] = 'S';

		delete [] data[location];
		data[location] = new char[highest+1];
		for (int k=0;k<highest+1;k++)
		{
			data[location][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location] = highest + 1;

		//second column
		temp_column = new char[highest+2];
		if (heights[location+1]!=0)
		{
			for (int i=0;i<heights[location+1];i++)
			{
				temp_column[i] = data[location+1][i];
			}
			if (heights[location+1]<highest)
			{
				for (int i=heights[location+1];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i]=' ';
			}
		}
		temp_column[highest] = 'S';
		temp_column[highest+1] = 'S';

		delete [] data[location+1];
		data[location+1] = new char[highest+2];
		for (int k=0;k<highest+2;k++)
		{
			data[location+1][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location+1] = highest + 2;

		//third column
		temp_column = new char[highest+2];
		if (heights[location+2]!=0)
		{
			for (int i=0;i<heights[location+2];i++)
			{
				temp_column[i] = data[location+2][i];
			}
			if (heights[location+2]<highest+1)
			{
				for (int i=heights[location+2];i<highest+1;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest+1;i++)
			{
				temp_column[i]=' ';
			}
		}
		temp_column[highest+1] = 'S';

		delete [] data[location+2];
		data[location+2] = new char[highest+2];
		for (int k=0;k<highest+2;k++)
		{
			data[location+2][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location+2] = highest + 2;
	}
	else if (rotation==90 or rotation==270)
	{
		highest = heights[location];
		if (heights[location+1]>highest)
		{
			highest = heights[location+1];
		}
		if (heights[location+1]<highest)
		{
			highest--;
		}

		//second column
		temp_column = new char[highest+2];
		if (heights[location+1]!=0)
		{
			for (int i=0;i<heights[location+1];i++)
			{
				temp_column[i] = data[location+1][i];
			}
			if (heights[location+1]<highest)
			{
				for (int i=heights[location+1];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest] = 'S';
		temp_column[highest+1] = 'S';

		delete [] data[location+1];
		data[location+1] = new char[highest+2];
		for (int k=0;k<highest+2;k++)
		{
			data[location+1][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location+1] = highest + 2;	

		//first column
		temp_column = new char[highest+3];
		if (heights[location]!=0)
		{
			for (int i=0;i<heights[location];i++)
			{
				temp_column[i] = data[location][i];
			}
			if (heights[location]<highest+1)
			{
				for (int i=heights[location];i<highest+1;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest+1;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest+1] = 'S';
		temp_column[highest+2] = 'S';

		delete [] data[location];
		data[location] = new char[highest+3];
		for (int k=0;k<highest+3;k++)
		{
			data[location][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location] = highest + 3;
	}
}
void Tetris::L_block(int rotation, int location)
{
	int highest;
	char* temp_column;

	if (rotation==0)
	{
		highest = heights[location];
		if (heights[location+1]>highest)
		{
			highest = heights[location+1];
		}

		//first column
		temp_column = new char[highest+3];
		if (heights[location]!=0)
		{
			for (int i=0;i<heights[location];i++)
			{
				temp_column[i] = data[location][i];
			}
			if (heights[location]<highest)
			{
				for (int i=heights[location];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest] = 'L';
		temp_column[highest+1] = 'L';
		temp_column[highest+2] = 'L';

		delete [] data[location];
		data[location] = new char[highest+3];
		for (int k=0;k<highest+3;k++)
		{
			data[location][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location] = highest + 3;

		//second column
		temp_column = new char[highest+1];
		if (heights[location+1]!=0)
		{
			for (int i=0;i<heights[location+1];i++)
			{
				temp_column[i] = data[location+1][i];
			}
			if (heights[location+1]<highest)
			{
				for (int i=heights[location+1];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest] = 'L';

		delete [] data[location+1];
		data[location+1] = new char[highest+1];
		for (int k=0;k<highest+1;k++)
		{
			data[location+1][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location+1] = highest + 1;
	}
	else if (rotation==90)
	{
		highest = heights[location];
		if (heights[location+1]>highest)
		{
			highest = heights[location+1];
		}
		if (heights[location+2]>highest)
		{
			highest = heights[location+2];
		}
		if (heights[location]<highest)
		{
			highest--;
		}

		//first column
		temp_column = new char[highest+2];
		if (heights[location]!=0)
		{
			for (int i=0;i<heights[location];i++)
			{
				temp_column[i] = data[location][i];
			}
			if (heights[location]<highest)
			{
				for (int i=heights[location];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest] = 'L';
		temp_column[highest+1] = 'L';

		delete [] data[location];
		data[location] = new char[highest+2];
		for (int k=0;k<highest+2;k++)
		{
			data[location][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location] = highest + 2;

		//second/third column
		for (int i=1;i<3;i++)
		{
			temp_column = new char[highest+2];
			if (heights[location+i]!=0)
			{
				for (int j=0;j<heights[location+i];j++)
				{
					temp_column[j] = data[location+i][j];
				}
				if (heights[location+i]<highest+1)
				{
					for (int j=heights[location+i];j<highest+1;j++)
					{
						temp_column[j] = ' ';
					}
				}
			}
			else
			{
				for (int j=0;j<highest+1;j++)
				{
					temp_column[j] = ' ';
				}
			}
			temp_column[highest+1] = 'L';

			delete [] data[location+i];
			data[location+i] = new char[highest+2];
			for (int k=0;k<highest+2;k++)
			{
				data[location+i][k] = temp_column[k];
			}
			delete [] temp_column;
			heights[location+i] = highest + 2;			
		}		
	}
	else if (rotation==180)
	{
		highest = heights[location];
		if (heights[location+1]>highest)
		{
			highest = heights[location+1];
		}
		if (heights[location+1]<highest)
		{
			if ((highest-heights[location+1])==1)
			{
				highest--;
			}
			else
			{
				highest -= 2;
			}
		}

		//first column
		temp_column = new char[highest+3];
		if (heights[location]!=0)
		{
			for (int i=0;i<heights[location];i++)
			{
				temp_column[i] = data[location][i];
			}
			if (heights[location]<highest+2)
			{
				for (int i=heights[location];i<highest+2;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest+2;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest+2] = 'L';

		delete [] data[location];
		data[location] = new char[highest+3];
		for (int k=0;k<highest+3;k++)
		{
			data[location][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location] = highest+3;

		//second column	
		temp_column = new char[highest+3];
		if (heights[location+1]!=0)
		{
			for (int i=0;i<heights[location+1];i++)
			{
				temp_column[i] = data[location+1][i];
			}
			if (heights[location+1]<highest)
			{
				for (int i=heights[location+1];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest] = 'L';
		temp_column[highest+1] = 'L';
		temp_column[highest+2] = 'L';

		delete [] data[location+1];
		data[location+1] = new char[highest+3];
		for (int k=0;k<highest+3;k++)
		{
			data[location+1][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location+1] = highest + 3;			
	}
	else if (rotation==270)
	{
		highest = heights[location];
		if (heights[location+1]>highest)
		{
			highest = heights[location=1];
		}
		if (heights[location+2]>highest)
		{
			highest = heights[location+2];
		}

		//first/second column
		for (int i=0;i<2;i++)
		{
			temp_column = new char[highest+1];
			if (heights[location+i]!=0)
			{
				for (int j=0;j<heights[location+i];j++)
				{
					temp_column[j] = data[location+i][j];
				}
				if (heights[location+i]<highest)
				{
					for (int k=heights[location+i];k<highest;k++)
					{
						temp_column[k] = ' ';
					}
				}
			}
			else
			{
				for (int j=0;j<highest;j++)
				{
					temp_column[j] = ' ';
				}
			}
			temp_column[highest] = 'L';
			delete [] data[location+i];
			data[location+i] = new char[highest+1];
			for (int k=0;k<highest+1;k++)
			{
				data[location+i][k] = temp_column[k];
			}
			delete [] temp_column;
			heights[location+i] = highest+1;		
		}

		//third column
		temp_column = new char[highest+2];
		if (heights[location+2]!=0)
		{
			for (int i=0;i<heights[location+2];i++)
			{
				temp_column[i] = data[location+2][i];
			}
			if (heights[location+2]<highest)
			{
				for (int i=heights[location+2];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest] = 'L';
		temp_column[highest+1] = 'L';

		delete [] data[location+2];
		data[location+2] = new char[highest+2];
		for (int k=0;k<highest+2;k++)
		{
			data[location+2][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location+2] = highest + 2;		
	}
}
void Tetris::J_block(int rotation, int location)
{
	int highest;
	char* temp_column;
	if (rotation==0)
	{
		highest = heights[location];
		if (heights[location+1]>highest)
		{
			highest = heights[location+1];
		}

		//second column
		temp_column = new char[highest+3];
		if (heights[location+1]!=0)
		{
			for (int i=0;i<heights[location+1];i++)
			{
				temp_column[i] = data[location+1][i];
			}
			if (heights[location+1]<highest)
			{
				for (int i=heights[location+1];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest] = 'J';
		temp_column[highest+1] = 'J';
		temp_column[highest+2] = 'J';

		delete [] data[location+1];
		data[location+1] = new char[highest+3];
		for (int k=0;k<highest+3;k++)
		{
			data[location+1][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location+1] = highest + 3;

		//first column
		temp_column = new char[highest+1];
		if (heights[location]!=0)
		{
			for (int i=0;i<heights[location];i++)
			{
				temp_column[i] = data[location][i];
			}
			if (heights[location]<highest)
			{
				for (int i=heights[location];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest] = 'J';

		delete [] data[location];
		data[location] = new char[highest+1];
		for (int k=0;k<highest+1;k++)
		{
			data[location][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location] = highest + 1;		
	}
	else if (rotation==270)
	{
		highest = heights[location+2];
		if (heights[location+1]>highest)
		{
			highest = heights[location+1];
		}
		if (heights[location]>highest)
		{
			highest = heights[location];
		}
		if (heights[location+2]<highest)
		{
			highest--;
		}

		//third column
		temp_column = new char[highest+2];
		if (heights[location+2]!=0)
		{
			for (int i=0;i<heights[location+2];i++)
			{
				temp_column[i] = data[location+2][i];
			}
			if (heights[location+2]<highest)
			{
				for (int i=heights[location+2];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest] = 'J';
		temp_column[highest+1] = 'J';

		delete [] data[location+2];
		data[location+2] = new char[highest+2];
		for (int k=0;k<highest+2;k++)
		{
			data[location+2][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location+2] = highest + 2;

		//first/second column
		for (int i=0;i<2;i++)
		{
			temp_column = new char[highest+2];
			if (heights[location+i]!=0)
			{
				for (int j=0;j<heights[location+i];j++)
				{
					temp_column[j] = data[location+i][j];
				}
				if (heights[location+i]<highest+1)
				{
					for (int j=heights[location+i];j<highest+1;j++)
					{
						temp_column[j] = ' ';
					}
				}
			}
			else
			{
				for (int j=0;j<highest+1;j++)
				{
					temp_column[j] = ' ';
				}
			}
			temp_column[highest+1] = 'J';

			delete [] data[location+i];
			data[location+i] = new char[highest+2];
			for (int k=0;k<highest+2;k++)
			{
				data[location+i][k] = temp_column[k];
			}
			delete [] temp_column;
			heights[location+i] = highest + 2;			
		}		
	}
	else if (rotation==180)
	{
		highest = heights[location+1];
		if (heights[location]>highest)
		{
			highest = heights[location];
		}
		if (heights[location]<highest)
		{
			if ((highest-heights[location])==1)
			{
				highest--;
			}
			else
			{
				highest -= 2;
			}
		}

		//second column
		temp_column = new char[highest+3];
		if (heights[location+1]!=0)
		{
			for (int i=0;i<heights[location+1];i++)
			{
				temp_column[i] = data[location+1][i];
			}
			if (heights[location+1]<highest+2)
			{
				for (int i=heights[location+1];i<highest+2;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest+2;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest+2] = 'J';

		delete [] data[location+1];
		data[location+1] = new char[highest+3];
		for (int k=0;k<highest+3;k++)
		{
			data[location+1][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location+1] = highest+3;

		//first column	
		temp_column = new char[highest+3];
		if (heights[location]!=0)
		{
			for (int i=0;i<heights[location];i++)
			{
				temp_column[i] = data[location][i];
			}
			if (heights[location]<highest)
			{
				for (int i=heights[location];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest] = 'J';
		temp_column[highest+1] = 'J';
		temp_column[highest+2] = 'J';

		delete [] data[location];
		data[location] = new char[highest+3];
		for (int k=0;k<highest+3;k++)
		{
			data[location][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location] = highest + 3;			
	}
	else if (rotation==90)
	{
		highest = heights[location];
		if (heights[location+1]>highest)
		{
			highest = heights[location=1];
		}
		if (heights[location+2]>highest)
		{
			highest = heights[location+2];
		}

		//second/third column
		for (int i=1;i<3;i++)
		{
			temp_column = new char[highest+1];
			if (heights[location+i]!=0)
			{
				for (int j=0;j<heights[location+i];j++)
				{
					temp_column[j] = data[location+i][j];
				}
				if (heights[location+i]<highest)
				{
					for (int k=heights[location+i];k<highest;k++)
					{
						temp_column[k] = ' ';
					}
				}
			}
			else
			{
				for (int j=0;j<highest;j++)
				{
					temp_column[j] = ' ';
				}
			}
			temp_column[highest] = 'J';
			delete [] data[location+i];
			data[location+i] = new char[highest+1];
			for (int k=0;k<highest+1;k++)
			{
				data[location+i][k] = temp_column[k];
			}
			delete [] temp_column;
			heights[location+i] = highest+1;		
		}

		//first column
		temp_column = new char[highest+2];
		if (heights[location]!=0)
		{
			for (int i=0;i<heights[location];i++)
			{
				temp_column[i] = data[location][i];
			}
			if (heights[location]<highest)
			{
				for (int i=heights[location];i<highest;i++)
				{
					temp_column[i] = ' ';
				}
			}
		}
		else
		{
			for (int i=0;i<highest;i++)
			{
				temp_column[i] = ' ';
			}
		}
		temp_column[highest] = 'J';
		temp_column[highest+1] = 'J';

		delete [] data[location];
		data[location] = new char[highest+2];
		for (int k=0;k<highest+2;k++)
		{
			data[location][k] = temp_column[k];
		}
		delete [] temp_column;
		heights[location] = highest + 2;		
	}
}
int Tetris::remove_full_rows()
{
	char* temp_column;
	int score=0;
	bool empty_col;

	if (get_min_height()!=0)
	{
		int count;
		for (int i=(get_min_height()-1);i>=0;i--)
		{
			count = 0;
			for (int j=0;j<width;j++)
			{
				if (data[j][i]!=' ')
				{
					count++;
				}
			}
			if (count==width)
			{
				score++;
				for (int col=0;col<width;col++)
				{
					empty_col = true;
					temp_column = new char[heights[col]-1];
					for (int row=0;row<(heights[col]-1);row++)
					{
						if (row<i)
						{
							temp_column[row] = data[col][row];
						}
						else
						{
							temp_column[row] = data[col][row+1];
						}

					}
					for (int row = 0;row<(heights[col]-1);row++)
					{
						if (temp_column[row]!=' ')
						{
							empty_col = false;
						}
					}
					if (empty_col!=true)
					{
						delete [] data[col];
						data[col] = new char[heights[col]-1];
						for (int n=0;n<heights[col]-1;n++)
						{
							data[col][n] = temp_column[n];
						}
						delete [] temp_column;
						heights[col] -= 1;
					}
					else
					{
						delete [] temp_column;
						heights[col] = 0;
					}
				}
			}

		}
	}
	return score;
}

void Tetris::destroy()
{
	delete [] heights;
	for (int i=0;i<width;i++)
	{
		delete [] data[i];
	}
	delete [] data;
}

void Tetris::add_left_column()
{
	char** new_data;
	new_data = new char*[width+1];
	new_data[0] = new char[0];
	for (int i=1;i<(width+1);i++)
	{
		new_data[i] = data[i-1];
	}
	delete []data;
	data = new_data;

	int* new_heights = new int[width+1];
	new_heights[0] = 0;
	for (int i=1;i<width+1;i++)
	{
		new_heights[i] = heights[i-1];
	}
	delete [] heights;
	heights = new int[width+1];
	for (int i=0;i<width+1;i++)
	{
		heights[i] = new_heights[i];
	}
	delete [] new_heights;
	width++;
}
void Tetris::add_right_column()
{
	char** new_data;
	new_data = new char*[width+1];
	new_data[width] = new char[0];
	for (int i=0;i<width;i++)
	{
		new_data[i] = data[i];
	}
	delete []data;
	data = new_data;

	int* new_heights = new int[width+1];
	new_heights[width] = 0;
	for (int i=0;i<width;i++)
	{
		new_heights[i] = heights[i];
	}
	delete [] heights;
	heights = new int[width+1];
	for (int i=0;i<width+1;i++)
	{
		heights[i] = new_heights[i];
	}
	delete [] new_heights;
	width++;
}
void Tetris::remove_left_column()
{
	char** new_data;
	new_data = new char*[width-1];
	for (int i=0;i<(width-1);i++)
	{
		new_data[i] = data[i+1];
	}
	delete [] data[0];
	delete [] data;
	data = new_data;

	int* new_heights = new int[width-1];
	for (int i=0;i<width-1;i++)
	{
		new_heights[i] = heights[i+1];
	}
	delete [] heights;
	heights = new int[width-1];
	for (int i=0;i<width-1;i++)
	{
		heights[i] = new_heights[i];
	}
	delete [] new_heights;
	width--;
}
void Tetris::remove_right_column()
{
	char** new_data;
	new_data = new char*[width-1];
	for (int i=0;i<(width-1);i++)
	{
		new_data[i] = data[i];
	}
	delete [] data[width-1];
	delete [] data;
	data = new_data;

	int* new_heights = new int[width-1];
	for (int i=0;i<width-1;i++)
	{
		new_heights[i] = heights[i];
	}
	delete [] heights;
	heights = new int[width-1];
	for (int i=0;i<width-1;i++)
	{
		heights[i] = new_heights[i];
	}
	delete [] new_heights;
	width--;
}