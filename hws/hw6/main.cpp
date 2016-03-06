#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <cassert>

#include "MersenneTwister.h"

#include "tile.h"
#include "location.h"
#include "board.h"


// this global variable is set in main.cpp and is adjustable from the command line
// (you are not allowed to make your own global variables)
int GLOBAL_TILE_SIZE = 11;


// ==========================================================================
// Helper function that is called when an error in the command line
// arguments is detected.
void usage(int argc, char *argv[]) {
  std::cerr << "USAGE: " << std::endl;
  std::cerr << "  " << argv[0] << " <filename>  -board_dimensions <h> <w>" << std::endl;
  std::cerr << "  " << argv[0] << " <filename>  -board_dimensions <h> <w>  -all_solutions" << std::endl;
  std::cerr << "  " << argv[0] << " <filename>  -board_dimensions <h> <w>  -allow_rotations" << std::endl;
  std::cerr << "  " << argv[0] << " <filename>  -all_solutions  -allow_rotations" << std::endl;
  std::cerr << "  " << argv[0] << " <filename>  -tile_size <odd # >= 11>" << std::endl;
  exit(1);
}



// ==========================================================================
// To get you started, this function places tiles on the board
// randomly and outputs the results (in all likelihood *not* a
// solution!) in the required format
/*
void RandomlyPlaceTiles(Board &board, const std::vector<Tile*> &tiles, std::vector<Location> &locations) {

  // MersenneTwister is an excellent library for psuedo-random numbers!
  MTRand mtrand;

  for (int t = 0; t < tiles.size(); t++) {
    // loop generates random locations until we (eventually) find one
    // that is not occupied
    int i,j;
    do {
      // generate a random coordinate within the range 0,0 -> rows-1,cols-1
      i = mtrand.randInt(board.numRows()-1);
      j = mtrand.randInt(board.numColumns()-1);
      Location l(i,j,0);
    } while (board.getTile(l) != NULL);

    // rotation is always 0 (for now)
    locations.push_back(l);
    board.setTile(l,tiles[t]);
  }
}
*/

// ==========================================================================
void HandleCommandLineArguments(int argc, char *argv[], std::string &filename, 
                                int &rows, int &columns, bool &all_solutions, bool &allow_rotations) {

  // must at least put the filename on the command line
  if (argc < 2) {
    usage(argc,argv);
  }
  filename = argv[1];

  // parse the optional arguments
  for (int i = 2; i < argc; i++) {
    if (argv[i] == std::string("-tile_size")) {
      i++;
      assert (i < argc);
      GLOBAL_TILE_SIZE = atoi(argv[i]);
      if (GLOBAL_TILE_SIZE < 11 || GLOBAL_TILE_SIZE % 2 == 0) {
        std::cerr << "ERROR: bad tile_size" << std::endl;
        usage(argc,argv);
      }
    } else if (argv[i] == std::string("-all_solutions")) {
      all_solutions = true;
    } else if (argv[i] == std::string("-board_dimensions")) {
      i++;
      assert (i < argc);
      rows = atoi(argv[i]);
      i++;
      assert (i < argc);
      columns = atoi(argv[i]);
      if (rows < 1 || columns < 1) {
        usage(argc,argv);
      }
    } else if (argv[i] == std::string("-allow_rotations")) {
      allow_rotations = true;
    } else {
      std::cerr << "ERROR: unknown argument '" << argv[i] << "'" << std::endl;
      usage(argc,argv);
    }
  }
}


// ==========================================================================
void ParseInputFile(int argc, char *argv[], const std::string &filename, std::vector<Tile*> &tiles) {

  // open the file
  std::ifstream istr(filename.c_str());
  if (!istr) {
    std::cerr << "ERROR: cannot open file '" << filename << "'" << std::endl;
    usage(argc,argv);
  }
  assert (istr);

  // read each line of the file
  std::string token, north, east, south, west;
  while (istr >> token >> north >> east >> south >> west) {
    assert (token == "tile");
    Tile *t = new Tile(north,east,south,west);
    tiles.push_back(t);
  }
}

bool shift(Board & board, std::vector<Location> & locations, std::vector<Tile*> & tiles, 
           std::vector<Tile*> & tiles_90, std::vector<Tile*> & tiles_180, 
           std::vector<Tile*> & tiles_270, std::string d, int n) { //shifts all tiles one space in specified direction
  Board new_board(board.numRows(), board.numColumns());
  if (d=="down") {
    for (int i=0;i<n;i++) {
      locations[i].row++;
      if (locations[i].row==new_board.numRows()) {
        return true;
      }
      if (locations[i].rotation==0) {
        new_board.setTile(locations[i],tiles[i]);
      }
      else if (locations[i].rotation==90) {
        new_board.setTile(locations[i],tiles_90[i]);
      }
      else if (locations[i].rotation==180) {
        new_board.setTile(locations[i],tiles_180[i]);
      }
      else if (locations[i].rotation==270) {
        new_board.setTile(locations[i],tiles_270[i]);
      }
    }
    board = new_board;
    return false;
  }
  else if (d=="right") {
    for (int i=0;i<n;i++) {
      locations[i].column++;
      if (locations[i].column==new_board.numColumns()) {
        return true;
      }
      if (locations[i].rotation==0) {
        new_board.setTile(locations[i],tiles[i]);
      }
      else if (locations[i].rotation==90) {
        new_board.setTile(locations[i],tiles_90[i]);
      }
      else if (locations[i].rotation==180) {
        new_board.setTile(locations[i],tiles_180[i]);
      }
      else if (locations[i].rotation==270) {
        new_board.setTile(locations[i],tiles_270[i]);
      }
    }
    board = new_board;
    return false;
  }
  else if (d=="up") {
    for (int i=0;i<n;i++) {
      locations[i].row--;
      if (locations[i].row<0) {
        return true;
      }
      if (locations[i].rotation==0) {
        new_board.setTile(locations[i],tiles[i]);
      }
      else if (locations[i].rotation==90) {
        new_board.setTile(locations[i],tiles_90[i]);
      }
      else if (locations[i].rotation==180) {
        new_board.setTile(locations[i],tiles_180[i]);
      }
      else if (locations[i].rotation==270) {
        new_board.setTile(locations[i],tiles_270[i]);
      }
    }
    board = new_board;
    return false;   
  }
  else if (d=="left") {
    for (int i=0;i<n;i++) {
      locations[i].column--;
      if (locations[i].column<0) {
        return true;
      }
      if (locations[i].rotation==0) {
        new_board.setTile(locations[i],tiles[i]);
      }
      else if (locations[i].rotation==90) {
        new_board.setTile(locations[i],tiles_90[i]);
      }
      else if (locations[i].rotation==180) {
        new_board.setTile(locations[i],tiles_180[i]);
      }
      else if (locations[i].rotation==270) {
        new_board.setTile(locations[i],tiles_270[i]);
      }
    }
    board = new_board;
    return false;
  }
}

bool is_solution(std::vector<Location> & locations, Board & board, std::vector<Tile*> & tiles) {
  bool bad_edge = false;
  for (unsigned int i=0;i<tiles.size();i++) { //check for pastures on outer edges
    if (locations[i].row==0) { //on top edge
      if (board.getTile(locations[i])->getNorth()!="pasture") { //top
        bad_edge = true;
      }
      Location l_down(locations[i].row+1,locations[i].column,0);
      if (board.getTile(l_down)==NULL and board.getTile(locations[i])->getSouth()!="pasture") { //bottom
        bad_edge = true;
      }
    }
    else if (locations[i].row==board.numRows()-1) { //on bottom
      if (board.getTile(locations[i])->getSouth()!="pasture") { //bottom
        bad_edge = true;
      }
      Location l_up(locations[i].row-1, locations[i].column,0);
      if (board.getTile(l_up)==NULL and board.getTile(locations[i])->getNorth()!="pasture") { //top
        bad_edge = true;
      }
    }
    else { //vertically not on an edge
      Location l_up(locations[i].row-1, locations[i].column,0);
      if (board.getTile(l_up)==NULL and board.getTile(locations[i])->getNorth()!="pasture") { //top
        bad_edge = true;
      }
      Location l_down(locations[i].row+1, locations[i].column,0);
      if (board.getTile(l_down)==NULL and board.getTile(locations[i])->getSouth()!="pasture") { //bottom
        bad_edge = true;
      }        
    }
    if (locations[i].column==0) { //on west edge
      if (board.getTile(locations[i])->getWest()!="pasture") { //west
        bad_edge = true;
      }
      Location l_east(locations[i].row, locations[i].column+1,0);
      if (board.getTile(l_east)==NULL and board.getTile(locations[i])->getEast()!="pasture") { //east
        bad_edge = true;
      }
    }
    else if (locations[i].column==board.numColumns()-1) { //on east edge
      if (board.getTile(locations[i])->getEast()!="pasture") { //east
        bad_edge = true;
      }
      Location l_west(locations[i].row, locations[i].column-1,0);
      if (board.getTile(l_west)==NULL and board.getTile(locations[i])->getWest()!="pasture") { //west
        bad_edge = true;
      }        
    }
    else { //horizontally not on an edge
      Location l_east(locations[i].row, locations[i].column+1,0);
      if (board.getTile(l_east)==NULL and board.getTile(locations[i])->getEast()!="pasture") { //east
        bad_edge = true;
      }
      Location l_west(locations[i].row, locations[i].column-1,0);
      if (board.getTile(l_west)==NULL and board.getTile(locations[i])->getWest()!="pasture") { //west
        bad_edge = true;
      }      
    }
  }
  if (bad_edge==true) {
    return false;
  }
  else {
    for (unsigned int i=0;i<locations.size();i++) { //check for mismatched connections
      Tile* t = board.getTile(locations[i]);
      if (locations[i].row!=0) { //north
        Location l_n(locations[i].row-1,locations[i].column,0);
        if (board.getTile(l_n)!=NULL) {
          if (t->getNorth()!=board.getTile(l_n)->getSouth()) {
            return false;
          }
        }
      }
      if (locations[i].row!=board.numRows()-1) { //south
        Location l_s(locations[i].row+1, locations[i].column,0);
        if (board.getTile(l_s)!=NULL) {
          if (t->getSouth()!=board.getTile(l_s)->getNorth()) {           
            return false;
          }
        }
      }
      if (locations[i].column!=0) { //west
        Location l_e(locations[i].row, locations[i].column-1, 0);
        if (board.getTile(l_e)!=NULL) {
          if (t->getWest()!=board.getTile(l_e)->getEast()) {
            return false;
          }
        }
      }
      if (locations[i].column!=board.numColumns()-1) { //east
        Location l_w(locations[i].row, locations[i].column+1, 0);
        if (board.getTile(l_w)!=NULL) {
          if (t->getEast()!=board.getTile(l_w)->getWest()) {
            return false;
          }
        }
      }
    }
    return true;
  }
}

void solver(Board & board, std::vector<Tile*> & tiles, std::vector<Location> & locations, 
            std::vector<Board> & solutions, std::vector<std::vector<Location> >& sol_locations,
            bool rotations);
void solver(Board board, std::vector<Tile*> & tiles, std::vector<Tile*> & tiles_90,
            std::vector<Tile*> & tiles_180, std::vector<Tile*> & tiles_270,
            std::vector<Location> locations, std::string side, int n, int rot, int t, 
            std::vector<Board> & solutions, std::vector<std::vector<Location> >& sol_locations,
            bool rotations) {
  bool out_of_bounds = false;
  if (side=="north") {
    if (locations[t].row==0) { //off top board
      out_of_bounds = shift(board, locations, tiles, tiles_90, tiles_180, tiles_270, "down", n);
    }
    if (out_of_bounds!=true) {
      Location l(locations[t].row-1,locations[t].column,rot);
      locations.push_back(l);
      if (rot==0) {
        board.setTile(l,tiles[n]);
      }
      else if (rot==90) {
        board.setTile(l,tiles_90[n]);
      }
      else if (rot==180) {
        board.setTile(l,tiles_180[n]);
      }
      else if (rot==270) {
        board.setTile(l,tiles_270[n]);
      }
    }
  }
  else if (side=="west") {
    if (locations[t].column==0) { //off left of board
      out_of_bounds = shift(board,locations,tiles,tiles_90,tiles_180,tiles_270,"right", n);
    }
    if (out_of_bounds!=true) {
      Location l(locations[t].row,locations[t].column-1,rot);
      locations.push_back(l);
      if (rot==0) {
        board.setTile(l,tiles[n]);
      }
      else if (rot==90) {
        board.setTile(l,tiles_90[n]);
      }
      else if (rot==180) {
        board.setTile(l,tiles_180[n]);
      }
      else if (rot==270) {
        board.setTile(l,tiles_270[n]);
      }
    }
  }
  else if (side=="south") { 
    if (locations[t].row==board.numRows()-1) { //off bottom of board
      out_of_bounds = shift(board,locations,tiles, tiles_90, tiles_180, tiles_270, "up", n);
    }
    if (out_of_bounds!=true) {
      Location l(locations[t].row+1,locations[t].column,rot);
      locations.push_back(l);
      if (rot==0) {
        board.setTile(l,tiles[n]);
      }
      else if (rot==90) {
        board.setTile(l,tiles_90[n]);
      }
      else if (rot==180) {
        board.setTile(l,tiles_180[n]);
      }
      else if (rot==270) {
        board.setTile(l,tiles_270[n]);
      }
    }
  }
  else if (side=="east") {
    if (locations[t].column==board.numColumns()-1) { //off right of board
      out_of_bounds = shift(board,locations,tiles, tiles_90, tiles_180, tiles_270, "left", n);
    }
    if (out_of_bounds!=true) {
      Location l(locations[t].row,locations[t].column+1,rot);
      locations.push_back(l);
      if (rot==0) {
        board.setTile(l,tiles[n]);
      }
      else if (rot==90) {
        board.setTile(l,tiles_90[n]);
      }
      else if (rot==180) {
        board.setTile(l,tiles_180[n]);
      }
      else if (rot==270) {
        board.setTile(l,tiles_270[n]);
      }
    }
  }
  if (out_of_bounds!=true and n!=tiles.size()-1) {
    for (int i=0;i<=n;i++) {
      if (board.getTile(locations[i])->getNorth()==tiles[n+1]->getSouth() and 
          board.getTile(locations[i])->getNorth()!="pasture") {
        if (locations[i].row!=0) {
          Location l(locations[i].row-1,locations[i].column,0);
          if (board.getTile(l)==NULL) {
            solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"north",
                   n+1, 0, i, solutions, sol_locations, rotations);
          }
        }
        else {
          solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"north",
                 n+1, 0, i, solutions, sol_locations, rotations);
        }
      }
      if (board.getTile(locations[i])->getEast()==tiles[n+1]->getWest() and 
          board.getTile(locations[i])->getEast()!="pasture") {
        if (locations[i].column!=board.numColumns()-1) {
          Location l(locations[i].row,locations[i].column+1,0);
          if (board.getTile(l)==NULL) {
            solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"east",
                   n+1, 0, i, solutions, sol_locations, rotations);
          }
        }
        else {
          solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"east",
                 n+1, 0, i, solutions, sol_locations, rotations);
        }
      }
      if (board.getTile(locations[i])->getSouth()==tiles[n+1]->getNorth() and 
          board.getTile(locations[i])->getSouth()!="pasture") {
        if (locations[i].row!=board.numRows()-1) {
          Location l(locations[i].row+1,locations[i].column,0);
          if (board.getTile(l)==NULL) {
            solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"south",
                   n+1, 0, i, solutions, sol_locations, rotations);
          }
        }
        else {
          solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"south",
                 n+1, 0, i, solutions, sol_locations, rotations);
        }
      }
      if (board.getTile(locations[i])->getWest()==tiles[n+1]->getEast() and 
          board.getTile(locations[i])->getWest()!="pasture") {
        if (locations[i].column!=0) {
          Location l(locations[i].row,locations[i].column-1,0);
          if (board.getTile(l)==NULL) {
            solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"west",
                   n+1, 0, i, solutions, sol_locations, rotations);
          }
        }
        else {
          solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"west",
                 n+1, 0, i, solutions, sol_locations, rotations);
        }
      }
      if (rotations==true) {
        Tile* t_90 = tiles_90[n+1];
        if (board.getTile(locations[i])->getNorth()==t_90->getSouth() and 
            board.getTile(locations[i])->getNorth()!="pasture") {
          if (locations[i].row!=0) {
            Location l(locations[i].row-1,locations[i].column,90);
            if (board.getTile(l)==NULL) {
              solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"north",
                     n+1, 90, i, solutions, sol_locations, rotations);
            }
          }
          else {
            solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"north",
                   n+1, 90, i, solutions, sol_locations, rotations);
          }
        }
        if (board.getTile(locations[i])->getEast()==t_90->getWest() and 
            board.getTile(locations[i])->getEast()!="pasture") {
          if (locations[i].column!=board.numColumns()-1) {
            Location l(locations[i].row,locations[i].column+1,90);
            if (board.getTile(l)==NULL) {
              solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"east",
                     n+1, 90, i, solutions, sol_locations, rotations);
            }
          }
          else {
            solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"east",
                   n+1, 90, i, solutions, sol_locations, rotations);
          }
        }
        if (board.getTile(locations[i])->getSouth()==t_90->getNorth() and 
            board.getTile(locations[i])->getSouth()!="pasture") {
          if (locations[i].row!=board.numRows()-1) {
            Location l(locations[i].row+1,locations[i].column,90);
            if (board.getTile(l)==NULL) {
              solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"south",
                     n+1, 90, i, solutions, sol_locations, rotations);
            }
          }
          else {
            solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"south",
                   n+1, 90, i, solutions, sol_locations, rotations);
          }
        }
        if (board.getTile(locations[i])->getWest()==t_90->getEast() and 
            board.getTile(locations[i])->getWest()!="pasture") {
          if (locations[i].column!=0) {
            Location l(locations[i].row,locations[i].column-1,90);
            if (board.getTile(l)==NULL) {
              solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"west",
                     n+1, 90, i, solutions, sol_locations, rotations);
            }
          }
          else {
            solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"west",
                   n+1, 90, i, solutions, sol_locations, rotations);
          }
        }
        Tile* t_180 = tiles_180[n+1];
        if (board.getTile(locations[i])->getNorth()==t_180->getSouth() and 
            board.getTile(locations[i])->getNorth()!="pasture") {
          if (locations[i].row!=0) {
            Location l(locations[i].row-1,locations[i].column,180);
            if (board.getTile(l)==NULL) {
              solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"north",
                     n+1, 180, i, solutions, sol_locations, rotations);
            }
          }
          else {
            solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"north",
                   n+1, 180, i, solutions, sol_locations, rotations);
          }
        }
        if (board.getTile(locations[i])->getEast()==t_180->getWest() and 
            board.getTile(locations[i])->getEast()!="pasture") {
          if (locations[i].column!=board.numColumns()-1) {
            Location l(locations[i].row,locations[i].column+1,180);
            if (board.getTile(l)==NULL) {
              solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"east",
                     n+1, 180, i, solutions, sol_locations, rotations);
            }
          }
          else {
            solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"east",
                   n+1, 180, i, solutions, sol_locations, rotations);
          }
        }
        if (board.getTile(locations[i])->getSouth()==t_180->getNorth() and 
            board.getTile(locations[i])->getSouth()!="pasture") {
          if (locations[i].row!=board.numRows()-1) {
            Location l(locations[i].row+1,locations[i].column,180);
            if (board.getTile(l)==NULL) {
              solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"south",
                     n+1, 180, i, solutions, sol_locations, rotations);
            }
          }
          else {
            solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"south",
                   n+1, 180, i, solutions, sol_locations, rotations);
          }
        }
        if (board.getTile(locations[i])->getWest()==t_180->getEast() and 
            board.getTile(locations[i])->getWest()!="pasture") {
          if (locations[i].column!=0) {
            Location l(locations[i].row,locations[i].column-1,180);
            if (board.getTile(l)==NULL) {
              solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"west",
                     n+1, 180, i, solutions, sol_locations, rotations);
            }
          }
          else {
            solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"west",
                   n+1, 180, i, solutions, sol_locations, rotations);
          }
        }
        Tile* t_270 = tiles_270[n+1];
        if (board.getTile(locations[i])->getNorth()==t_270->getSouth() and 
            board.getTile(locations[i])->getNorth()!="pasture") {
          if (locations[i].row!=0) {
            Location l(locations[i].row-1,locations[i].column,270);
            if (board.getTile(l)==NULL) {
              solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"north",
                     n+1, 270, i, solutions, sol_locations, rotations);
            }
          }
          else {
            solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"north",
                   n+1, 270, i, solutions, sol_locations, rotations);
          }
        }
        if (board.getTile(locations[i])->getEast()==t_270->getWest() and 
            board.getTile(locations[i])->getEast()!="pasture") {
          if (locations[i].column!=board.numColumns()-1) {
            Location l(locations[i].row,locations[i].column+1,270);
            if (board.getTile(l)==NULL) {
              solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"east",
                     n+1, 270, i, solutions, sol_locations, rotations);
            }
          }
          else {
            solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"east",
                   n+1, 270, i, solutions, sol_locations, rotations);
          }
        }
        if (board.getTile(locations[i])->getSouth()==t_270->getNorth() and 
            board.getTile(locations[i])->getSouth()!="pasture") {
          if (locations[i].row!=board.numRows()-1) {
            Location l(locations[i].row+1,locations[i].column,270);
            if (board.getTile(l)==NULL) {
              solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"south",
                     n+1, 270, i, solutions, sol_locations, rotations);
            }
          }
          else {
            solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"south",
                   n+1, 270, i, solutions, sol_locations, rotations);
          }
        }
        if (board.getTile(locations[i])->getWest()==t_270->getEast() and 
            board.getTile(locations[i])->getWest()!="pasture") {
          if (locations[i].column!=0) {
            Location l(locations[i].row,locations[i].column-1,270);
            if (board.getTile(l)==NULL) {
              solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"west",
                     n+1, 270, i, solutions, sol_locations, rotations);
            }
          }
          else {
            solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"west",
                   n+1, 270, i, solutions, sol_locations, rotations);
          }
        }
      }
    }
  }
  else if (n==tiles.size()-1 and out_of_bounds!=true) { //all tiles added
    if (is_solution(locations, board, tiles)==true) { //check for pastures on edges and correct connections
      if (sol_locations.size()==0) {
        solutions.push_back(board);
        sol_locations.push_back(locations);
      }
      else {
        int same_count;
        bool same = false;
        bool same_board = false;
        for (unsigned int i=0;i<solutions.size();i++) { //check to see if board is visually identical
          if (board==solutions[i]) {
            same_board = true;
            break;
          }
          else {
            Board t1 = board.transpose();
            Board t2 = board.transpose().transpose();
            Board t3 = board.transpose().transpose().transpose();
            if (t1==solutions[i] or t2==solutions[i] or t3==solutions[i]) { //entire board is not rotated
              same_board = true;
            }
            t1.destroy();
            t2.destroy();
            t3.destroy();
          }
        }
        for (unsigned int i=0;i<sol_locations.size();i++) { //check to see whether location coords are the same
          same_count = 0;
          for (unsigned int x=0;x<sol_locations[i].size();x++) { 
            if (sol_locations[i][x]==locations[x]) {
              same_count++;
            }
            else {
              continue;
            }
          }
          if (same_count==locations.size()) {
            same = true;
            break;
          }
        }
        if (same==false and same_board==false) {
          solutions.push_back(board);
          sol_locations.push_back(locations);
        }
      }
    }
  }
}
void solver(Board & board, std::vector<Tile*> & tiles, std::vector<Tile*> & tiles_90,
            std::vector<Tile*> & tiles_180, std::vector<Tile*> & tiles_270, std::vector<Location> & locations,
            std::vector<Board> & solutions, std::vector<std::vector<Location> >& sol_locations, 
            bool rotations) {
  Location l(0,0,0);
  locations.push_back(l);
  board.setTile(l,tiles[0]);
  if (tiles.size()>1) {
    if (tiles[0]->getNorth()==tiles[1]->getSouth() and tiles[0]->getNorth()!="pasture")
    {
      solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"north",
             1, 0, 0, solutions, sol_locations, rotations);
    }
    if (tiles[0]->getEast()==tiles[1]->getWest() and tiles[0]->getEast()!="pasture") {
      solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"east",
             1, 0, 0, solutions, sol_locations, rotations);
    }
    if (tiles[0]->getSouth()==tiles[1]->getNorth() and tiles[0]->getSouth()!="pasture") {
      solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"south",
             1, 0, 0, solutions, sol_locations, rotations);
    }
    if (tiles[0]->getWest()==tiles[1]->getEast() and tiles[0]->getWest()!="pasture") {
      solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"west",
             1, 0, 0, solutions, sol_locations, rotations);
    }
  }
  if (rotations==true) {
    //check matches to original position to second tiles's rotations
    if (tiles[0]->getNorth()==tiles_90[1]->getSouth() and tiles[0]->getNorth()!="pasture")
    {
      solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"north",
             1, 90, 0, solutions, sol_locations, rotations);
    }
    if (tiles[0]->getEast()==tiles_90[1]->getWest() and tiles[0]->getEast()!="pasture") {
      solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"east",
             1, 90, 0, solutions, sol_locations, rotations);
    }
    if (tiles[0]->getSouth()==tiles_90[1]->getNorth() and tiles[0]->getSouth()!="pasture") {
      solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"south",
             1, 90, 0, solutions, sol_locations, rotations);
    }
    if (tiles[0]->getWest()==tiles_90[1]->getEast() and tiles[0]->getWest()!="pasture") {
      solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"west",
             1, 90, 0, solutions, sol_locations, rotations);
    }
    if (tiles[0]->getNorth()==tiles_180[1]->getSouth() and tiles[0]->getNorth()!="pasture")
    {
      solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"north",
             1, 180, 0, solutions, sol_locations, rotations);
    }
    if (tiles[0]->getEast()==tiles_180[1]->getWest() and tiles[0]->getEast()!="pasture") {
      solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"east",
             1, 180, 0, solutions, sol_locations, rotations);
    }
    if (tiles[0]->getSouth()==tiles_180[1]->getNorth() and tiles[0]->getSouth()!="pasture") {
      solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"south",
             1, 180, 0, solutions, sol_locations, rotations);
    }
    if (tiles[0]->getWest()==tiles_180[1]->getEast() and tiles[0]->getWest()!="pasture") {
      solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"west",
             1, 180, 0, solutions, sol_locations, rotations);
    }
    if (tiles[0]->getNorth()==tiles_270[1]->getSouth() and tiles[0]->getNorth()!="pasture")
    {
      solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"north",
             1, 270, 0, solutions, sol_locations, rotations);
    }
    if (tiles[0]->getEast()==tiles_270[1]->getWest() and tiles[0]->getEast()!="pasture") {
      solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"east",
             1, 270, 0, solutions, sol_locations, rotations);
    }
    if (tiles[0]->getSouth()==tiles_270[1]->getNorth() and tiles[0]->getSouth()!="pasture") {
      solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"south",
             1, 270, 0, solutions, sol_locations, rotations);
    }
    if (tiles[0]->getWest()==tiles_270[1]->getEast() and tiles[0]->getWest()!="pasture") {
      solver(board,tiles,tiles_90,tiles_180,tiles_270,locations,"west",
             1, 270, 0, solutions, sol_locations, rotations);
    }
    //create and check tile 0 rotated 90 degree for matches
    Location l_90(0,0,90);
    std::vector<Location> locations_90;
    locations_90.push_back(l_90);
    board.setTile(l_90, tiles_90[0]);
    if (tiles.size()>1) {
      if (tiles_90[0]->getNorth()==tiles[1]->getSouth() and tiles_90[0]->getNorth()!="pasture")
      {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_90,"north",
               1, 0, 0, solutions, sol_locations, rotations);
      }
      if (tiles_90[0]->getEast()==tiles[1]->getWest() and tiles_90[0]->getEast()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_90,"east",
               1, 0, 0, solutions, sol_locations, rotations);
      }
      if (tiles_90[0]->getSouth()==tiles[1]->getNorth() and tiles_90[0]->getSouth()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_90,"south",
               1, 0, 0, solutions, sol_locations, rotations);
      }
      if (tiles_90[0]->getWest()==tiles[1]->getEast() and tiles_90[0]->getWest()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_90,"west",
               1, 0, 0, solutions, sol_locations, rotations);
      }
      if (tiles_90[0]->getNorth()==tiles_90[1]->getSouth() and tiles_90[0]->getNorth()!="pasture")
      {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_90,"north",
               1, 90, 0, solutions, sol_locations, rotations);
      }
      if (tiles_90[0]->getEast()==tiles_90[1]->getWest() and tiles_90[0]->getEast()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_90,"east",
               1, 90, 0, solutions, sol_locations, rotations);
      }
      if (tiles_90[0]->getSouth()==tiles_90[1]->getNorth() and tiles_90[0]->getSouth()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_90,"south",
               1, 90, 0, solutions, sol_locations, rotations);
      }
      if (tiles_90[0]->getWest()==tiles_90[1]->getEast() and tiles_90[0]->getWest()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_90,"west",
               1, 90, 0, solutions, sol_locations, rotations);
      }
      if (tiles_90[0]->getNorth()==tiles_180[1]->getSouth() and tiles_90[0]->getNorth()!="pasture")
      {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_90,"north",
               1, 180, 0, solutions, sol_locations, rotations);
      }
      if (tiles_90[0]->getEast()==tiles_180[1]->getWest() and tiles_90[0]->getEast()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_90,"east",
               1, 180, 0, solutions, sol_locations, rotations);
      }
      if (tiles_90[0]->getSouth()==tiles_180[1]->getNorth() and tiles_90[0]->getSouth()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_90,"south",
               1, 180, 0, solutions, sol_locations, rotations);
      }
      if (tiles_90[0]->getWest()==tiles_180[1]->getEast() and tiles_90[0]->getWest()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_90,"west",
               1, 180, 0, solutions, sol_locations, rotations);
      }
      if (tiles_90[0]->getNorth()==tiles_270[1]->getSouth() and tiles_90[0]->getNorth()!="pasture")
      {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_90,"north",
               1, 270, 0, solutions, sol_locations, rotations);
      }
      if (tiles_90[0]->getEast()==tiles_270[1]->getWest() and tiles_90[0]->getEast()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_90,"east",
               1, 270, 0, solutions, sol_locations, rotations);
      }
      if (tiles_90[0]->getSouth()==tiles_270[1]->getNorth() and tiles_90[0]->getSouth()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_90,"south",
               1, 270, 0, solutions, sol_locations, rotations);
      }
      if (tiles_90[0]->getWest()==tiles_270[1]->getEast() and tiles_90[0]->getWest()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_90,"west",
               1, 270, 0, solutions, sol_locations, rotations);
      }
    }
    //create and check tile 0 rotated 180 degree for matches
    Location l_180(0,0,180);
    std::vector<Location> locations_180;
    locations_180.push_back(l_180);
    board.setTile(l_180, tiles_180[0]);
    if (tiles.size()>1) {
      if (tiles_180[0]->getNorth()==tiles[1]->getSouth() and tiles_180[0]->getNorth()!="pasture")
      {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_180,"north",
               1, 0, 0, solutions, sol_locations, rotations);
      }
      if (tiles_180[0]->getEast()==tiles[1]->getWest() and tiles_180[0]->getEast()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_180,"east",
               1, 0, 0, solutions, sol_locations, rotations);
      }
      if (tiles_180[0]->getSouth()==tiles[1]->getNorth() and tiles_180[0]->getSouth()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_180,"south",
               1, 0, 0, solutions, sol_locations, rotations);
      }
      if (tiles_180[0]->getWest()==tiles[1]->getEast() and tiles_180[0]->getWest()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_180,"west",
               1, 0, 0, solutions, sol_locations, rotations);
      }
      if (tiles_180[0]->getNorth()==tiles_90[1]->getSouth() and tiles_180[0]->getNorth()!="pasture")
      {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_180,"north",
               1, 90, 0, solutions, sol_locations, rotations);
      }
      if (tiles_180[0]->getEast()==tiles_90[1]->getWest() and tiles_180[0]->getEast()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_180,"east",
               1, 90, 0, solutions, sol_locations, rotations);
      }
      if (tiles_180[0]->getSouth()==tiles_90[1]->getNorth() and tiles_180[0]->getSouth()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_180,"south",
               1, 90, 0, solutions, sol_locations, rotations);
      }
      if (tiles_180[0]->getWest()==tiles_90[1]->getEast() and tiles_180[0]->getWest()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_180,"west",
               1, 90, 0, solutions, sol_locations, rotations);
      }
      if (tiles_180[0]->getNorth()==tiles_180[1]->getSouth() and tiles_180[0]->getNorth()!="pasture")
      {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_180,"north",
               1, 180, 0, solutions, sol_locations, rotations);
      }
      if (tiles_180[0]->getEast()==tiles_180[1]->getWest() and tiles_180[0]->getEast()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_180,"east",
               1, 180, 0, solutions, sol_locations, rotations);
      }
      if (tiles_180[0]->getSouth()==tiles_180[1]->getNorth() and tiles_180[0]->getSouth()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_180,"south",
               1, 180, 0, solutions, sol_locations, rotations);
      }
      if (tiles_180[0]->getWest()==tiles_180[1]->getEast() and tiles_180[0]->getWest()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_180,"west",
               1, 180, 0, solutions, sol_locations, rotations);
      }
      if (tiles_180[0]->getNorth()==tiles_270[1]->getSouth() and tiles_180[0]->getNorth()!="pasture")
      {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_180,"north",
               1, 270, 0, solutions, sol_locations, rotations);
      }
      if (tiles_180[0]->getEast()==tiles_270[1]->getWest() and tiles_180[0]->getEast()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_180,"east",
               1, 270, 0, solutions, sol_locations, rotations);
      }
      if (tiles_180[0]->getSouth()==tiles_270[1]->getNorth() and tiles_180[0]->getSouth()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_180,"south",
               1, 270, 0, solutions, sol_locations, rotations);
      }
      if (tiles_180[0]->getWest()==tiles_270[1]->getEast() and tiles_180[0]->getWest()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_180,"west",
               1, 270, 0, solutions, sol_locations, rotations);
      }
    }
    //create and check tile 0 rotated 270 degree for matches
    Location l_270(0,0,270);
    std::vector<Location> locations_270;
    locations_270.push_back(l_270);
    board.setTile(l_270, tiles_270[0]);
    if (tiles.size()>1) {
      if (tiles_270[0]->getNorth()==tiles[1]->getSouth() and tiles_270[0]->getNorth()!="pasture")
      {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_270,"north",
               1, 0, 0, solutions, sol_locations, rotations);
      }
      if (tiles_270[0]->getEast()==tiles[1]->getWest() and tiles_270[0]->getEast()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_270,"east",
               1, 0, 0, solutions, sol_locations, rotations);
      }
      if (tiles_270[0]->getSouth()==tiles[1]->getNorth() and tiles_270[0]->getSouth()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_270,"south",
               1, 0, 0, solutions, sol_locations, rotations);
      }
      if (tiles_270[0]->getWest()==tiles[1]->getEast() and tiles_270[0]->getWest()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_270,"west",
               1, 0, 0, solutions, sol_locations, rotations);
      }
      if (tiles_270[0]->getNorth()==tiles_90[1]->getSouth() and tiles_270[0]->getNorth()!="pasture")
      {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_270,"north",
               1, 90, 0, solutions, sol_locations, rotations);
      }
      if (tiles_270[0]->getEast()==tiles_90[1]->getWest() and tiles_270[0]->getEast()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_270,"east",
               1, 90, 0, solutions, sol_locations, rotations);
      }
      if (tiles_270[0]->getSouth()==tiles_90[1]->getNorth() and tiles_270[0]->getSouth()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_270,"south",
               1, 90, 0, solutions, sol_locations, rotations);
      }
      if (tiles_270[0]->getWest()==tiles_90[1]->getEast() and tiles_270[0]->getWest()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_270,"west",
               1, 90, 0, solutions, sol_locations, rotations);
      }
      if (tiles_270[0]->getNorth()==tiles_180[1]->getSouth() and tiles_270[0]->getNorth()!="pasture")
      {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_270,"north",
               1, 180, 0, solutions, sol_locations, rotations);
      }
      if (tiles_270[0]->getEast()==tiles_180[1]->getWest() and tiles_270[0]->getEast()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_270,"east",
               1, 180, 0, solutions, sol_locations, rotations);
      }
      if (tiles_270[0]->getSouth()==tiles_180[1]->getNorth() and tiles_270[0]->getSouth()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_270,"south",
               1, 180, 0, solutions, sol_locations, rotations);
      }
      if (tiles_270[0]->getWest()==tiles_180[1]->getEast() and tiles_270[0]->getWest()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_270,"west",
               1, 180, 0, solutions, sol_locations, rotations);
      }
      if (tiles_270[0]->getNorth()==tiles_270[1]->getSouth() and tiles_270[0]->getNorth()!="pasture")
      {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_270,"north",
               1, 270, 0, solutions, sol_locations, rotations);
      }
      if (tiles_270[0]->getEast()==tiles_270[1]->getWest() and tiles_270[0]->getEast()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_270,"east",
               1, 270, 0, solutions, sol_locations, rotations);
      }
      if (tiles_270[0]->getSouth()==tiles_270[1]->getNorth() and tiles_270[0]->getSouth()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_270,"south",
               1, 270, 0, solutions, sol_locations, rotations);
      }
      if (tiles_270[0]->getWest()==tiles_270[1]->getEast() and tiles_270[0]->getWest()!="pasture") {
        solver(board,tiles,tiles_90,tiles_180,tiles_270,locations_270,"west",
               1, 270, 0, solutions, sol_locations, rotations);
      }
    }
  }
}

// ==========================================================================
int main(int argc, char *argv[]) {

  std::string filename;
  int rows = -1;
  int columns = -1;
  bool all_solutions = false;
  bool allow_rotations = false;
  HandleCommandLineArguments(argc, argv, filename, rows, columns, all_solutions, allow_rotations);

  // load in the tiles
  std::vector<Tile*> tiles;
  ParseInputFile(argc,argv,filename,tiles);
  if (rows<0 and columns<0) {
    rows = tiles.size();
    columns = tiles.size();
  }
  std::vector<Tile*> tiles_90;
  std::vector<Tile*> tiles_180;
  std::vector<Tile*> tiles_270;
  for (unsigned int i=0;i<tiles.size();i++) { //make vector of tiles rotated 90
    tiles_90.push_back(tiles[i]->rotate(90));
  }
  for (unsigned int i=0;i<tiles.size();i++) { //make vector of tiles rotated 180
    tiles_180.push_back(tiles[i]->rotate(180));
  }
  for (unsigned int i=0;i<tiles.size();i++) { //make vector of tiles rotated 270
    tiles_270.push_back(tiles[i]->rotate(270));
  }


  // confirm the specified board is large enough
  if (rows < 1  ||  columns < 1  ||  rows * columns < (int)tiles.size()) {
    std::cerr << "ERROR: specified board is not large enough" << rows << "X" << columns << "=" << rows*columns << " " << tiles.size() << std::endl;
    usage(argc,argv);
  }

  Board board(rows,columns);
  std::vector<Location> locations;
  std::vector<std::vector<Location> > sol_locations;
  std::vector<Board> solutions;
  solver(board,tiles,tiles_90,tiles_180,tiles_270,locations, solutions, sol_locations, allow_rotations);
  if (solutions.size()==0) {
    std::cout << "No Solutions.";
  }
  else if (all_solutions==false) {
    std::cout << "Solution: ";
    for (unsigned int i=0;i<sol_locations[0].size();i++) {
      std::cout << sol_locations[0][i];
    }
    std::cout<< '\n';
    solutions[0].Print();
  }
  else if (all_solutions==true) {
    for (unsigned int i=0;i<solutions.size();i++) {
      std::cout << "Solution: ";
      for (unsigned int n=0;n<sol_locations[i].size();n++) {
        std::cout << sol_locations[i][n];
      }
      std::cout<< '\n';
      solutions[i].Print();
    }
    std::cout << "Found " << solutions.size() << " Solution(s).";
  }
  
  /*
  for (int i = 0; i < 5; i++) {

    // generate a random tile layouts
    Board board(rows,columns);
    std::vector<Location> locations;
    RandomlyPlaceTiles(board, tiles, locations);
    
    // print the solution
    std::cout << "probably-not-a-Solution: ";
    for (int i = 0; i < locations.size(); i++) {
      std::cout << locations[i];
    }
    std::cout << std::endl;

    // print the ASCII art board representation
    board.print();
    std::cout << std::endl;
  }
*/
  
  // delete the tiles
  for (int t = 0; t < tiles.size(); t++) {
    delete tiles[t];
    delete tiles_90[t];
    delete tiles_180[t];
    delete tiles_270[t];
  }
}
// ==========================================================================
