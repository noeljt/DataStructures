// Starting code for Checkpoints 2 and 3.  This includes
// functions to read the grid and to output it.

#include <fstream>
#include <iostream>
#include <list>
#include <vector>
using namespace std;


// A simple class to represent a point location.  It only has a
// constructor and a two public member variables.  This is one of the
// few times that you are allowed to use non-private member variables.

class Point {
public:
  Point(int x0, int y0) : x(x0), y(y0) {}
  int x,y;
};


// Input the grid and the start location.  The input is a sequence of
// x y locations, terminated by x==0 and y==0.  The last input, which
// follows 0 0 input, is the start location.
//
// The grid is represented as a 2d vector of bools, with each location
// that is blocked --- meaning that no path can go through --- being
// represented by the value "true".  The grid is large enough to
// include all blocked points and include the starting location.  The
// first coordinate of the vector of vectors is the x coordinate, and
// the second is the y coordinate.  The format of the input is
// specified in the lab handout.

void read_grid(istream& istr, vector<vector<bool> > & blocked_grid,
	       int & start_x, int & start_y) {

  // Read the x y locations into a list of Points.  Keep track of the
  // max x and max y values so that the size of the grid can be
  // determined.
  int x, y;
  int max_x = 0, max_y = 0;  // keep track of the max coordinate values
  list<Point> blocked_points;
  while ((istr >> x >> y) && ! (x==0 && y==0)) {
    blocked_points.push_back(Point(x,y));
    if (x > max_x) max_x = x;
    if (y > max_y) max_y = y;
  }

  // Now that a 0 0 location has been read, read the start location.
  // If this is beyond the max x or y value then update these values.
  istr >> start_x >> start_y;
  if (start_x > max_x) max_x = start_x;
  if (start_y > max_y) max_y = start_y;

  // Make a vector of vectors with all entries marked false.   
  vector<bool> one_row_of_ys(max_y+1, false);
  vector<vector<bool> > empty_grid(max_x+1, one_row_of_ys);
  blocked_grid = empty_grid;

  // For Point in the list, mark the location in the list as blocked.
  list<Point>::iterator p;
  for (p = blocked_points.begin(); p != blocked_points.end(); ++p) {
    blocked_grid[p->x][p->y] = true;
  }
}


// Output the grid to cout.  The form of the output is explained in
// the cout statement below.

void print_grid(vector<vector<bool> > const& blocked_grid, int start_x, int start_y, 
                vector<vector<bool> > const& copy) {

  cout << "Here is the grid with the origin in the upper left corner, x increasing \n"
       << "horizontally and y increasing down the screen.  An 'X' represents a blocked\n"
       << "location and the 'S' represents the starting location.\n\n";

  for (int y=0; y<blocked_grid[0].size(); ++y) {
    for (int x=0; x<blocked_grid.size(); ++x) {
      if (x == start_x && y == start_y) {
	     cout << " S";
      }
      else if (blocked_grid[x][y]) {
	      cout << " X";
      }
      else {
        if (copy[y][x]) {
          cout << " P";
        }
        else {
	       cout << " .";
       }
      }
    }
    cout << '\n';
  }
}

//prototype
int paths(Point & p, int i, vector<Point> & blocks, vector<Point> path, vector<vector<bool> > & copy);

//initial
int paths(Point & p, vector<Point> & blocks, vector<vector<bool> > &copy) {
  if (p.x==0 and p.y==0) {
    return 0;
  }
  else {
    vector<Point> path;
    path.push_back(p);
    if (p.x==0) {
      Point p_1(p.x,(p.y)-1);
      for (int q=0;q<blocks.size();q++) {
        if (p_1.x==blocks[q].x and p_1.y==blocks[q].y) {
          return 0;
        }
      }
      return paths(p_1,1, blocks, path, copy);
    }
    else if (p.y==0) {
      Point p_1((p.x)-1,p.y);
      for (int q=0;q<blocks.size();q++) {
        if (p_1.x==blocks[q].x and p_1.y==blocks[q].y) {
          return 0;
        }
      }
      return paths(p_1,1, blocks, path, copy);
    }
    else {
      Point p_1((p.x)-1,p.y);
      Point p_2(p.x,(p.y)-1);
      for (int q=0;q<blocks.size();q++) {
        if (p_1.x==blocks[q].x and p_1.y==blocks[q].y
          and p_2.x==blocks[q].x and p_2.y==blocks[q].y) {
          return 0;
        }
        else if (p_1.x==blocks[q].x and p_1.y==blocks[q].y) {
          return paths(p_2,1,blocks, path, copy);
        }
        else if (p_2.x==blocks[q].x and p_2.y==blocks[q].y) {
          return paths(p_1,1,blocks, path, copy);
        }
      }
      return (paths(p_1,1, blocks, path, copy)+paths(p_2,1, blocks, path, copy));
    }
  }
}

//
int paths(Point & p, int i, vector<Point> & blocks, vector<Point> path, vector<vector<bool> > & copy) {
  path.push_back(p);
  if (p.x==0 and p.y==0) {
    for (int y=0;y<copy[0].size();y++) {
      for (int x=0;x<copy.size();x++) {
        copy[x][y] = false;
      }
    }
    for (int q=0;q<path.size();q++) {
      copy[path[q].y][path[q].x] = true;
    }
    return i;
  }
  else if (p.x==0) {
    Point n(p.x,(p.y)-1);
    for (int q=0;q<blocks.size();q++) {
      if (n.x==blocks[q].x and n.y==blocks[q].y) {
        return 0;
      }
    }
    return paths(n,i, blocks, path, copy);
  }
  else if (p.y==0) {
    Point n((p.x)-1,p.y);
    for (int q=0;q<blocks.size();q++) {
      if (n.x==blocks[q].x and n.y==blocks[q].y) {
        return 0;
      }
    }
    return paths(n,i, blocks, path, copy);

  }
  else {
    Point n_1((p.x)-1,p.y);
    Point n_2(p.x,(p.y)-1);
    for (int q=0;q<blocks.size();q++) {
      if (n_1.x==blocks[q].x and n_1.y==blocks[q].y
        and n_2.x==blocks[q].x and n_2.y==blocks[q].y) {
        return 0;
      }
      else if (n_1.x==blocks[q].x and n_1.y==blocks[q].y) {
        return paths(n_2,1,blocks,path,copy);
      }
      else if (n_2.x==blocks[q].x and n_2.y==blocks[q].y) {
        return paths(n_1,1,blocks,path,copy);
      }
    }
    return (paths(n_1,i, blocks,path,copy)+paths(n_2,i, blocks,path,copy));
  }
}

void blocked_points(vector<vector<bool> > & blocked_grid, vector<Point> & v) {
  for (int y=0;y<blocked_grid[0].size();y++) {
    for (int x=0;x<blocked_grid.size();x++) {
      if (blocked_grid[x][y]) {
        Point p(x,y);
        v.push_back(p);
      }
    }
  }
}


int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " grid-file\n";
    return 1;
  }
  ifstream istr(argv[1]);
  if (!istr) {
    cerr << "Could not open " << argv[1] << endl;
    return 1;
  }
  
  vector<vector<bool> > blocked_grid;
  int start_x, start_y;
  read_grid(istr, blocked_grid, start_x, start_y);
  vector<vector<bool> > copy;
  copy = blocked_grid;
  print_grid(blocked_grid, start_x, start_y, copy);

  // Start here with your code...
  vector<Point> blocks;
  Point i(start_x, start_y);
  blocked_points(blocked_grid, blocks);
  cout << "Number of paths: " << paths(i, blocks, copy) << endl;
  print_grid(blocked_grid, start_x, start_y, copy);

  return 0;
}
      
