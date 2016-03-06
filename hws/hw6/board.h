#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include "tile.h"
#include "location.h"


// This class stores a grid of Tile pointers, which are NULL if the
// grid location does not (yet) contain a tile

class Board {
public:

  // CONSTRUCTOR
  // takes in the dimensions (height & width) of the board
  Board(int i, int j);

  // ACCESSORS
  int numRows() const { return board.size(); }
  int numColumns() const { return board[0].size(); }
  Tile* getTile(Location l) const;
  Tile* getTile_coords(int r, int c) const;

  // MODIFIERS
  void setTile(Location l, Tile* t);

  // FOR PRINTING
  void Print() const;

  //other
  Board transpose() const;
  void destroy();

private:

  // REPRESENTATION
  std::vector<std::vector<Tile*> > board;
};

bool operator==(const Board & b1, const Board & b2);

#endif
