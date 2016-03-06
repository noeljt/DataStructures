#ifndef  __TILE_H__
#define __TILE_H__

#include <iostream>
#include <string>
#include <vector>


// This class represents a single Carcassonne tile and includes code
// to produce a human-readable ASCII art representation of the tile.

class Tile {
public:

  //constructor takes in 4 strings, representing what is on the edge
  // of each tile.  Each edge string is "pasture", "road", or "city".
  Tile(std::string &north, std::string &east, std::string &south, std::string &west);

  // ACCESSORS
  std::string& getNorth() { return north_; }
  std::string& getSouth() { return south_; }
  std::string& getEast() { return east_; }
  std::string& getWest() { return west_; }
  int numCities() { return num_cities; }
  int numRoads() { return num_roads; }
  int hasAbbey() { return (num_cities == 0 && num_roads <= 1); }

  //Modifier
  Tile* rotate(int rot);

  // for ASCII art printing
  void printRow(std::ostream &ostr, int i);

private:

  // helper function called by the constructor for printing
  void prepare_ascii_art();

  // REPRESENTATION
  std::string north_;
  std::string east_;
  std::string south_;
  std::string west_;
  int num_roads;
  int num_cities;
  std::vector<std::string> ascii_art;
};


#endif
