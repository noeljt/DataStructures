//File: tetris.h
//Purpose: header file for tetris class 

#ifndef __tetris_h_
#define __tetris_h_

class Tetris
{
public:
	Tetris(int the_width);

	//ACCESSORS
	int get_width() const;
	int get_max_height() const;
	int get_min_height() const;
	int count_squares() const;

	//MODIFIERS
	void add_piece(char shape, int rotation, int location);
	void I_block(int rotation, int location);
	void O_block(int rotation, int location);
	void T_block(int rotation, int location);
	void Z_block(int rotation, int location);
	void S_block(int rotation, int location);
	void L_block(int rotation, int location);
	void J_block(int rotation, int location);
	int remove_full_rows();
	void add_left_column();
	void add_right_column();
	void remove_left_column();
	void remove_right_column();

	//OTHER
	void print() const;
	void destroy();

private:
	int width;
	int *heights;
	char** data;
};

#endif
