#include <vector>
#include <set>
#include <iostream>
#include <math.h>
#include <cassert>
#include "sudoku.h"

using std::set;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

// ======================================================
// A program to solve very simple Sudoku puzzles
// ======================================================

int main() {
  int size;
  while (cin >> size) {
    // Read in the board size and create an empty board
    Sudoku board(size);
    // Read in and set the known positions in the board
    char c;
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {      
        cin >> c;
        if (c != '.') {
          board.Set(i,j,c-'0');
        }
      }
    }
    // The iterative solving routine 
    while (1) {
      // Is the puzzle already solved?
      if (board.IsSolved()) {
        cout << "\nPuzzle is solved:" << endl;
        board.Print();
        break;
      }
      
      // Is the puzzle impossible?
      if (board.Impossible()) {
        cout << "\nCannot solve this puzzle:" << endl;
        board.Print();
        break;
      }
      
      // Try to reduce the number of choices in one or more board cells
      // by propagating known values within each row, column, and quadrant
      int changed = 0;
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          if (board.KnownValue(i,j))
            changed += board.Propagate(i,j);
        }
      }
      
      // If nothing changed this iteration, give up
      if (changed == 0) {
        cout << "\nPuzzle is too difficult for this solver!" << endl;
        board.Print();
        break;      
      }
    }
  }
}

// ======================================================

// Construct an empty board
Sudoku::Sudoku(int s) {
  // set the size
  size = s;
  quadrant_size = (int)sqrt(size);
  assert (quadrant_size*quadrant_size == s);

  
  // You need to finish this function!
  for (int n=0;n<size;n++) {
    vector<set<int> > row;
    for (int i=0;i<size;i++) {
      vector<int> myints;
      for (int i=1;i<=size;i++) {
        myints.push_back(i);
      }
      set<int> start(myints.begin(),myints.end());
      row.push_back(start);
    }
    board.push_back(row);
  }
}

// To construct the puzzle, set the value of a particular cell
void Sudoku::Set(int i, int j, int value) {
  // make sure the value is one of the legal values
  assert (board[i][j].find(value) != board[i][j].end());
  board[i][j].clear();
  board[i][j].insert(value);
}

// Does the cell have exactly one legal value?
bool Sudoku::KnownValue(int i, int j) const {
  return (board[i][j].size() == 1);
}
int  Sudoku::GetKnownValue(int i, int j) const {
  if (KnownValue(i,j)) {
    set<int>::iterator it = board[i][j].begin();
    return *it;
  }
  else {
    return 0;
  }
}

// If there is exactly one number in each cell of the grid, the puzzle is solved!
bool Sudoku::IsSolved() const {


  // You need to write this function
  for (int i=0;i<size;i++) {
    for (int n=0;n<size;n++) {
      if (board[i][n].size()!=1) {
        return false;
      }
    }
  }
  return true;


}

// If there are no legal choices in one or more cells of the grid, the puzzle is impossible
bool Sudoku::Impossible() const {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (board[i][j].size() == 0) 
        return true;
    }
  }
  return false;
}

// print out the solution
void Sudoku::Print() const {
  int solved = IsSolved();
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      int count = size+1;
      for (set<int>::iterator itr = board[i][j].begin(); itr != board[i][j].end(); itr++) {
        count--;
        cout << *itr;
      }
      if (!solved) {
        // if it's not solved, print out spaces to separate the values
        for (int k = 0; k < count; k++) {
          cout << " ";
        }
      }
    }
    cout << endl;
  }
}


// Propagate information from this cell along columns & rows &
// within quadrant. Return the number of cells that changed.
int Sudoku::Propagate(int i, int j) {


  // You need to write this function
  int total;
  for (int r=0;r<size;r++) {
    for (int c=0;c<size;c++) {
      if (KnownValue(r,c)==true) {
        continue;
      }
      bool changed = false;
      //check row
      for (int c_c=0;c_c<size;c_c++) {
        if (c_c==c) {
          continue;
        }
        if (KnownValue(r,c_c)==true) {
          if (board[r][c].erase(GetKnownValue(r,c_c))!=0) {
            changed = true;
          }
        }
      }
      //check column
      for (int r_r=0;r_r<size;r_r++) {
        if (r_r==r) {
          continue;
        }
        if (KnownValue(r_r,c)==true) {
          if (board[r][c].erase(GetKnownValue(r_r,c))!=0) {
            changed = true;
          }
        }
      }
      //check box
      if (size==4) {
        if (r>=0 and r<quadrant_size) { //first row
          if (c>=0 and c<quadrant_size) { //first column
            for (int r_r=0;r_r<quadrant_size;r_r++) {
              for (int c_c=0;c_c<quadrant_size;c_c++) {
                if (KnownValue(r_r,c_c)==true) {
                  if (r_r==r and c_c==c) {continue;}
                  if (board[r][c].erase(GetKnownValue(r_r,c_c))!=0) {
                    changed = true;
                  }
                }
              }
            }
          }
          else if (c>=quadrant_size and c<(2*quadrant_size)) { //second column
            for (int r_r=0;r_r<quadrant_size;r_r++) {
              for (int c_c=quadrant_size;c_c<(2*quadrant_size);c_c++) {
                if (KnownValue(r_r,c_c)==true) {
                  if (r_r==r and c_c==c) {continue;}
                  if (board[r][c].erase(GetKnownValue(r_r,c_c))!=0) {
                    changed = true;
                  }
                }
              }
            }
          }
        } 
        else if (r>=quadrant_size and r<(2*quadrant_size)) { //second row
          if (c>=0 and c<quadrant_size) { //first column
            for (int r_r=quadrant_size;r_r<(2*quadrant_size);r_r++) {
              for (int c_c=0;c_c<quadrant_size;c_c++) {
                if (KnownValue(r_r,c_c)==true) {
                  if (r_r==r and c_c==c) {continue;}
                  if (board[r][c].erase(GetKnownValue(r_r,c_c))!=0) {
                    changed = true;
                  }
                }
              }
            }
          }
          else if (c>=quadrant_size and c<(2*quadrant_size)) { //second column
            for (int r_r=quadrant_size;r_r<(2*quadrant_size);r_r++) {
              for (int c_c=quadrant_size;c_c<(2*quadrant_size);c_c++) {
                if (KnownValue(r_r,c_c)==true) {
                  if (r_r==r and c_c==c) {continue;}
                  if (board[r][c].erase(GetKnownValue(r_r,c_c))!=0) {
                    changed = true;
                  }
                }
              }
            }
          }
        }
      }
      else if (size==9) {
        if (r>=0 and r<quadrant_size) { //first row
          if (c>=0 and c<quadrant_size) { //first column
            for (int r_r=0;r_r<quadrant_size;r_r++) {
              for (int c_c=0;c_c<quadrant_size;c_c++) {
                if (KnownValue(r_r,c_c)==true) {
                  if (r_r==r and c_c==c) {continue;}
                  if (board[r][c].erase(GetKnownValue(r_r,c_c))!=0) {
                    changed = true;
                  }
                }
              }
            }
          }
          else if (c>=quadrant_size and c<(2*quadrant_size)) { //second column
            for (int r_r=0;r_r<quadrant_size;r_r++) {
              for (int c_c=quadrant_size;c_c<(2*quadrant_size);c_c++) {
                if (KnownValue(r_r,c_c)==true) {
                  if (r_r==r and c_c==c) {continue;}
                  if (board[r][c].erase(GetKnownValue(r_r,c_c))!=0) {
                    changed = true;
                  }
                }
              }
            }
          }
          else if (c>=(2*quadrant_size) and c<(3*quadrant_size)) { //third column
            for (int r_r=0;r_r<quadrant_size;r_r++) {
              for (int c_c=(2*quadrant_size);c_c<(3*quadrant_size);c_c++) {
                if (KnownValue(r_r,c_c)==true) {
                  if (r_r==r and c_c==c) {continue;}
                  if (board[r][c].erase(GetKnownValue(r_r,c_c))!=0) {
                    changed = true;
                  }
                }
              }
            }            
          }
        }
        else if (r>=quadrant_size and r<(2*quadrant_size)) { //second row
          if (c>=0 and c<quadrant_size) { //first column
            for (int r_r=quadrant_size;r_r<(2*quadrant_size);r_r++) {
              for (int c_c=0;c_c<quadrant_size;c_c++) {
                if (KnownValue(r_r,c_c)==true) {
                  if (r_r==r and c_c==c) {continue;}
                  if (board[r][c].erase(GetKnownValue(r_r,c_c))!=0) {
                    changed = true;
                  }
                }
              }
            }
          }
          else if (c>=quadrant_size and c<(2*quadrant_size)) { //second column
            for (int r_r=quadrant_size;r_r<(2*quadrant_size);r_r++) {
              for (int c_c=quadrant_size;c_c<(2*quadrant_size);c_c++) {
                if (KnownValue(r_r,c_c)==true) {
                  if (r_r==r and c_c==c) {continue;}
                  if (board[r][c].erase(GetKnownValue(r_r,c_c))!=0) {
                    changed = true;
                  }
                }
              }
            }
          }
          else if (c>=(2*quadrant_size) and c<(3*quadrant_size)) { //third column
            for (int r_r=quadrant_size;r_r<(2*quadrant_size);r_r++) {
              for (int c_c=(2*quadrant_size);c_c<(3*quadrant_size);c_c++) {
                if (KnownValue(r_r,c_c)==true) {
                  if (r_r==r and c_c==c) {continue;}
                  if (board[r][c].erase(GetKnownValue(r_r,c_c))!=0) {
                    changed = true;
                  }
                }
              }
            }            
          }
        }
        else if (r>=(2*quadrant_size) and r<(3*quadrant_size)) { //third row
          if (c>=0 and c<quadrant_size) { //first column
            for (int r_r=(2*quadrant_size);r_r<(3*quadrant_size);r_r++) {
              for (int c_c=0;c_c<quadrant_size;c_c++) {
                if (KnownValue(r_r,c_c)==true) {
                  if (r_r==r and c_c==c) {continue;}
                  if (board[r][c].erase(GetKnownValue(r_r,c_c))!=0) {
                    changed = true;
                  }
                }
              }
            }
          }
          else if (c>=quadrant_size and c<(2*quadrant_size)) { //second column
            for (int r_r=(2*quadrant_size);r_r<(3*quadrant_size);r_r++) {
              for (int c_c=quadrant_size;c_c<(2*quadrant_size);c_c++) {
                if (KnownValue(r_r,c_c)==true) {
                  if (r_r==r and c_c==c) {continue;}
                  if (board[r][c].erase(GetKnownValue(r_r,c_c))!=0) {
                    changed = true;
                  }
                }
              }
            }
          }
          else if (c>=(2*quadrant_size) and c<(3*quadrant_size)) { //third column
            for (int r_r=(2*quadrant_size);r_r<(3*quadrant_size);r_r++) {
              for (int c_c=(2*quadrant_size);c_c<(3*quadrant_size);c_c++) {
                if (KnownValue(r_r,c_c)==true) {
                  if (r_r==r and c_c==c) {continue;}
                  if (board[r][c].erase(GetKnownValue(r_r,c_c))!=0) {
                    changed = true;
                  }
                }
              }
            }            
          }
        }
      }

      if (changed) {
        total++;
      }
    }
  }
  return total;
}
