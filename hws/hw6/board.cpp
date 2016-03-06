#include <cassert>
#include <cstdlib>
#include <cstdio>

#include "board.h"
#include "location.h"


// this global variable is set in main.cpp and is adjustable from the command line
// (you are not allowed to make your own global variables)
extern int GLOBAL_TILE_SIZE;


// ==========================================================================
// CONSTRUCTOR
Board::Board(int i, int j) {
  board = std::vector<std::vector<Tile*> >
    ( (unsigned int)i,
      std::vector<Tile*>((unsigned int)j,NULL) );
}


// ==========================================================================
// ACCESSORS
Tile* Board::getTile(Location l) const {
  assert (l.row >= 0 && l.row < numRows());
  assert (l.column >= 0 && l.column < numColumns());
  return board[l.row][l.column];
}

Tile* Board::getTile_coords(int r, int c) const {
  return board[r][c];
}


// ==========================================================================
// MODIFIERS
void Board::setTile(Location l, Tile* t) {
  assert (l.row >= 0 && l.row < numRows());
  assert (l.column >= 0 && l.column < numColumns());
  board[l.row][l.column] = t;
}

// ==========================================================================
// PRINTING
void Board::Print() const {
  for (int b = 0; b < numRows(); b++) {
    for (int i = 0; i < GLOBAL_TILE_SIZE; i++) {
      for (int j = 0; j < numColumns(); j++) {
        if (board[b][j] != NULL) {
          board[b][j]->printRow(std::cout,i);
        } else {
          std::cout << std::string(GLOBAL_TILE_SIZE,' ');
        }
      }
      std::cout << "\n";
    }
  }
  fflush(stdout);
}

Board Board::transpose() const {
  int row=0;
  int column=0;
  for (unsigned int r=0;r<numRows();r++) {
    for (unsigned int c=0;c<numColumns();c++) {
      if (getTile_coords(r,c)!=NULL) {
        if (r>row) {
          row = r;
        }
        if (c>column) {
          column = c;
        }
      }
    }
  }
  Board b_cut(row+1,column+1);
  for (unsigned int r=0;r<b_cut.numRows();r++) {
    for (unsigned int c=0;c<b_cut.numColumns();c++) {
      Location l(r,c,0);
      b_cut.setTile(l,getTile_coords(r,c));
    }
  }
  Board b_2(numRows(),numColumns());
  for (unsigned int r=0;r<b_cut.numRows();r++) {
    for (unsigned int c=0;c<b_cut.numColumns();c++) {
      Location l(c,b_cut.numRows()-1-r,0);
      Tile* t = b_cut.getTile_coords(r,c);
      Tile* t_2;
      if (t!=NULL) {
        t_2 = t->rotate(90);
      }
      else {
        t_2 = NULL;
      }
      b_2.setTile(l,t_2);
    }
  }
  return b_2;
}

void Board::destroy() {
  for (unsigned int r = 0;r<numRows();r++) {
    for (unsigned int c =0;c<numColumns();c++) {
      if (getTile_coords(r,c)!=NULL) {
        delete getTile_coords(r,c);
      }
    }
  }
}

bool operator==(const Board & b1, const Board & b2) {
  if (b1.numRows()!=b2.numRows() or b1.numColumns()!=b2.numColumns()) {
    return false;
  }
  for (unsigned int r = 0;r<b1.numRows();r++) {
    for (unsigned int c =0;c<b1.numColumns();c++) {
      if (b1.getTile_coords(r,c)!=NULL and b2.getTile_coords(r,c)!=NULL) {
        Tile* t1 = b1.getTile_coords(r,c);
        Tile* t2 = b2.getTile_coords(r,c);
        if (t1->getNorth()!=t2->getNorth()) {
          return false;
        }
        if (t1->getSouth()!=t2->getSouth()) {
          return false;
        }
        if (t1->getWest()!=t2->getWest()) {
          return false;
        }
        if (t1->getEast()!=t2->getEast()) {
          return false;
        }
      }
      else if (b1.getTile_coords(r,c)!=NULL and b2.getTile_coords(r,c)==NULL ||
               b1.getTile_coords(r,c)==NULL and b2.getTile_coords(r,c)!=NULL) {
        return false;
      }
    }
  }
  return true;
}
// ==========================================================================
