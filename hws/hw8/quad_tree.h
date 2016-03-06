// ===================================================================
//
// We provide the Point class and the implementation of several
// QuadTree member functions for printing.  
//
// IMPORTANT: You should modify this file to add all of the necessary
// functionality for the QuadTree class and its helper classes: Node,
// DepthIterator, and BreadthIterator.
//
// ===================================================================

#ifndef quad_tree_h_
#define quad_tree_h_

#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <algorithm>


// ==============================================================
// ==============================================================
// A tiny templated class to store 2D coordinates.  This class works
// with number_type = int, float, double, unsigned char (a 1 byte=8
// bit integer), short (a 2 byte=16 bit integer).

template <class number_type>
class Point {
public:
  Point(const number_type& x_, const number_type& y_) : x(x_),y(y_) {}
  // REPRESENTATION
  number_type x;
  number_type y;
};

// a helper function to print Points to STL output stream
template <class number_type>
inline std::ostream& operator<<(std::ostream &ostr, const Point<number_type> &pt) {
  ostr << "(" << pt.x << "," << pt.y << ")";
  return ostr;
}

//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
//+*+*+**+*+*+*+*+*+*+MY CODE START*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+

//---------------------------------------------------------------
// TREE NODE CLASS
template <class number_type, class label_type>
class Node {
public:
  Node() : parent(NULL), pt(-1,-1) {
    children[0] = NULL;
    children[1] = NULL;
    children[2] = NULL;
    children[3] = NULL;
  }
  Node(const Point<number_type> & pt_, const label_type & l) : parent(NULL),pt(pt_.x,pt_.y),label(l) {
    children[0] = NULL;
    children[1] = NULL;
    children[2] = NULL;
    children[3] = NULL;
  }
  Point<number_type> pt;
  label_type label;
  Node<number_type,label_type>* children[4];
  Node<number_type,label_type>* parent;
};

template <class number_type,class label_type> class QuadTree;

//---------------------------------------------------------------
// DEPTH ITERATOR CLASS
template <class number_type, class label_type>
class DepthIterator {
public:
  DepthIterator() : ptr(NULL) {}
  DepthIterator(Node<number_type,label_type>* p) : ptr(p) {}
  //operator*
  const Point<number_type> & operator*() const { return ptr->pt; }
  bool operator!() const {return ptr==NULL;}
  //comparison operators
  bool operator== (const DepthIterator<number_type,label_type> & other) {
    if (ptr==NULL and other.ptr==NULL) {return true;}
    else if (other.ptr==NULL) {return false;}
    else if (ptr==NULL) {return false;}
    return (ptr->pt.x == other.ptr->pt.x && ptr->pt.y == other.ptr->pt.y); 
  }
  bool operator!= (const DepthIterator<number_type,label_type> & other) {
    if (ptr==NULL and other.ptr==NULL) {return false;}
    else if (other.ptr==NULL) {return true;}
    else if (ptr==NULL) {return true;}
    return (ptr->pt.x != other.ptr->pt.x || ptr->pt.y != other.ptr->pt.y);
  }

  //increment
  DepthIterator<number_type,label_type> & operator++() { // pre-increment, ++itr
    if (ptr==NULL) {return *this;} //no nodes/end
    for (int i=0;i<4;i++) {
      if (ptr->children[i]!=NULL) { //search through children
        ptr = ptr->children[i];
        return *this;
      }
    }
    //no direct children
    Node<number_type,label_type>* tmp = ptr->parent;
    if (tmp==NULL) { //node has no parent
      ptr=NULL;
      return *this;
    }
    while (true) { //node has a parent
      int location = 4;
      for (int i=0;i<4;i++) { //search through children for previous
        if (ptr==tmp->children[i]) { //found current place
          location = i+1;
          break;
        }
      }
      if (location<4) {
        if (tmp->children[location]!=NULL) { //next location isnt NULL
          ptr = tmp->children[location];
          return *this;
        }
        else {
          for (int i=location;i<4;i++) { //next location is NULL
            if (tmp->children[i]!=NULL) { //found non-null node
              ptr = tmp->children[i];
              return *this;
            }
          }
        }
      }
      ptr = tmp;
      tmp = tmp->parent;
      if (!tmp) {
        ptr = NULL;
        return *this;
      }
    }
  }

  DepthIterator<number_type,label_type> operator++(int) { //post-increment, itr++
    DepthIterator<number_type,label_type> temp(*this);
    ++(*this);
    return temp;
  }

  label_type getLabel() const {return ptr->label;}
  int getDepth() const {
    if (ptr==NULL) {return -1;}
    Node<number_type,label_type>* temp = ptr;
    int depth = 0;
    while (temp->parent!=NULL) {
      temp = temp->parent;
      depth++;
    }
    return depth;
  }

private:
  //rep
  Node<number_type,label_type>* ptr;
};

// --------------------------------------------------------------
// BREADTH ITERATOR CLASS
template <class number_type, class label_type>
class BreadthIterator {
public:
  BreadthIterator() : ptr(NULL) {}
  BreadthIterator(Node<number_type,label_type>* p) : ptr(p) {}
  //operator*
  const Point<number_type> & operator*() const { return ptr->pt; }
  bool operator!() const {return this->ptr==NULL;}
  //comparison operators
  bool operator== (const BreadthIterator<number_type,label_type> & other) {
    if (ptr==NULL and other.ptr==NULL) {return true;}
    else if (other.ptr==NULL) {return false;}
    else if (ptr==NULL) {return false;}
    return (ptr->pt.x == other.ptr->pt.x && ptr->pt.y == other.ptr->pt.y); 
  }
  bool operator!= (const BreadthIterator<number_type,label_type> & other) {
    if (ptr==NULL and other.ptr==NULL) {return false;}
    else if (other.ptr==NULL) {return true;}
    else if (ptr==NULL) {return true;}
    return (ptr->pt.x != other.ptr->pt.x || ptr->pt.y != other.ptr->pt.y);
  }
  //increment
  BreadthIterator<number_type,label_type> & operator++() { // pre-increment, ++itr
    if (!ptr) {return *this;}
    int height = 1;
    Node<number_type,label_type>* root = ptr;
    while (true) { //find root
      if (root->parent==NULL) {
        break;
      }
      else {
        root = root->parent;
        height++;
      }
    }
    std::vector<Node<number_type,label_type>*> current;
    std::vector<Node<number_type,label_type>*> next;
    current.push_back(root);
    height--;
    for (int x=0;x<current.size();x++) {
      for (int i=0;i<4;i++) {
        if (current[x]->children[i]!=NULL) {
          next.push_back(current[x]->children[i]);
        }
      }
    }
    height--;
    while (height>=0) { //go through tree to find correct level/next level
      current = next;
      next.clear();
      for (int x=0;x<current.size();x++) {
        for (int i=0;i<4;i++) {
          if (current[x]->children[i]!=NULL) {
            next.push_back(current[x]->children[i]);
          }
        }
      }
      height--;
    }
    if (ptr==current[current.size()-1]) {
      if (next.size()==0) {
        ptr = NULL;
        return *this;
      }
      else {
        ptr = next[0];
        return *this;
      }
    }
    else {
      for (unsigned int i=0;i<current.size();i++) {
        if (ptr==current[i]) {
          ptr = current[i+1];
          return *this;
        }
      }
    }

  }
  BreadthIterator<number_type,label_type> operator++(int) { //post-increment, itr++
    BreadthIterator<number_type,label_type> temp(*this);
    ++(*this);
    return temp;
  }

  label_type getLabel() const {return ptr->label;}
  int getDepth() {
    if (!ptr) {return -1;}
    Node<number_type,label_type>* temp = ptr;
    int depth = 0;
    while (temp->parent!=NULL) {
      temp = temp->parent;
      depth++;
    }
    return depth;
  }

private:
  //rep
  Node<number_type,label_type>* ptr;
};

// --------------------------------------------------------------
//QuadTree Class
template <class number_type, class label_type>
class QuadTree {
public:
  //default + destructor
  QuadTree() : root_(NULL), size_(0) {}
  QuadTree(const QuadTree<number_type,label_type> & old) : size_(old.size_) {
    root_ = copy_tree(old.root_,NULL);
  }
  QuadTree & operator=(const QuadTree<number_type,label_type> & old) {
    if (&old != this) {
      this->destroy_tree(root_);
      root_ = this->copy_tree(old.root_,NULL);
      size_ = old.size_; 
    }
    return *this;
  }
  ~QuadTree() {
    this->destroy_tree(root_);
    root_ = NULL;
  }

  typedef DepthIterator<number_type,label_type> iterator;
  friend class DepthIterator<number_type,label_type>;

  typedef BreadthIterator<number_type,label_type> bf_iterator;
  friend class BreadthIterator<number_type,label_type>;

  // ACCESSORS
  int size() const {return size_;}
  bool operator==(const QuadTree<number_type,label_type> & old) const {
    return  old.root_==this->root_;
  }

  //Find and Insert
  iterator find(const int x_, const int y_) {return find(x_,y_,root_);}
  std::pair<iterator,bool> insert(const Point<number_type> & pt, const label_type & l) {
    if (!root_) { //empty tree
      root_ = new Node<number_type,label_type>(pt,l);
      size_++;
      return std::make_pair(iterator(root_),true);
    }
    return insert(pt,l,root_,root_->parent);
  }

  // Depth iterators
  iterator begin() const {
    if (!root_) {return iterator(NULL);}
    return iterator(root_);
  }
  iterator end() const {
    return iterator(NULL);
  }

  //Breadth iterators
  bf_iterator bf_begin() const {
    if (!root_) {return bf_iterator(NULL);}
    return bf_iterator(root_);
  }
  bf_iterator bf_end() const {
    return bf_iterator(NULL);
  }

  int height() {
    if (!root_) {return -1;}
    std::vector<int> heights;
    height(root_,heights,0);
    return *std::max_element(heights.begin(),heights.end());
  }

  bool sanity_check() const {
    if (root_ == NULL) return true;
    if (root_->parent != NULL) {
      return false;
    }
    return sanity_check(root_);
  }  

  // ==============================================================
  // PROVIDED CODE : QUAD TREE MEMBER FUNCTIONS FOR PRINTING
  // ==============================================================

  // NOTE: this function only works for quad trees with non negative
  // integer coordinates and char labels

  // NOTE2: this function assumes that no two points have the same x
  // coordinate or the same y coordinate.

  // plot driver function
  // takes in the maximum x and y coordinates for these data points
  // the optional argument draw_lines defaults to true
  void plot(int max_x, int max_y, bool draw_lines=true) const {
    // allocate blank space for the center of the board
    std::vector<std::string> board(max_y+1,std::string(max_x+1,' '));
    // edit the board to add the point labels and draw vertical and
    // horizontal subdivisions
    plot(root_,board,0,max_x,0,max_y,draw_lines);
    // print the top border of the plot
    std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
    for (int i = 0; i <= max_y; i++) {
      // print each row of the board between vertical border bars
      std::cout << "|" << board[i] << "|" << std::endl;
    }
    // print the top border of the plot
    std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
  }

  // actual recursive function for plotting
  void plot(Node<number_type,label_type> *p, std::vector<std::string> &board,
            int x_min, int x_max, int y_min, int y_max, bool draw_lines) const {
    // base case, draw nothing if this node is NULL
    if (p == NULL) return;
    // check that the dimensions range of this node make sense
    assert (x_min >= 0 && x_min <= x_max);
    assert (y_min >= 0 && y_min <= y_max);
    assert (board.size() >= y_max);
    assert (board[0].size() >= x_max);
    // verify that the point stored at this node fits on the board
    assert (p->pt.y >= 0 && p->pt.y < board.size());
    assert (p->pt.x >= 0 && p->pt.x < board[0].size());
    // draw the vertical and horizontal bars extending across the
    // range of this node
    if (draw_lines) {
      for (int x = x_min; x <= x_max; x++) {
        board[p->pt.y][x] = '-';
      }
      for (int y = y_min; y <= y_max; y++) {
        board[y][p->pt.x] = '|';
      }
    }
    // draw this label
    board[p->pt.y][p->pt.x] = p->label;
    // recurse on the 4 children
    plot(p->children[0],board,x_min ,p->pt.x-1,y_min ,p->pt.y-1,draw_lines);
    plot(p->children[1],board,p->pt.x+1,x_max ,y_min ,p->pt.y-1,draw_lines);
    plot(p->children[2],board,x_min ,p->pt.x-1,p->pt.y+1,y_max ,draw_lines);
    plot(p->children[3],board,p->pt.x+1,x_max ,p->pt.y+1,y_max ,draw_lines);
  }


  // ==============================================================

  // prints all of the tree data with a pre-order (node first, then
  // children) traversal of the tree structure

  // driver function
  void print_sideways() const { print_sideways(root_,""); }

  // actual recursive function
  void print_sideways(Node<number_type,label_type>* p, const std::string &indent) const {
    // base case
    if (p == NULL) return;
    // print out this node
    std::cout << indent << p->label << " (" << p->pt.x << "," << p->pt.y << ")" << std::endl;
    // recurse on each of the children trees
    // increasing the indentation
    print_sideways(p->children[0],indent+"  ");
    print_sideways(p->children[1],indent+"  ");
    print_sideways(p->children[2],indent+"  ");
    print_sideways(p->children[3],indent+"  ");
  }

  // ==============================================================
  //====================END PROVIDED CODE==========================
  // ==============================================================

private:
  //rep
  Node<number_type,label_type>* root_;
  int size_;

  //private helper functions
  void destroy_tree(Node<number_type,label_type>* p) {
    if (!p) return;
    destroy_tree(p->children[0]);
    destroy_tree(p->children[1]);
    destroy_tree(p->children[2]);
    destroy_tree(p->children[3]);
    delete p;
  }

  Node<number_type,label_type>* copy_tree(Node<number_type,label_type>* old_r, 
                                          Node<number_type,label_type>* parent) {
    if (old_r==NULL) {
      return NULL;
    }
    Node<number_type,label_type>* answer = new Node<number_type,label_type>();
    answer->pt = Point<number_type>(old_r->pt.x, old_r->pt.y);
    answer->label = old_r->label;
    answer->children[0] = copy_tree(old_r->children[0],answer);
    answer->children[1] = copy_tree(old_r->children[1],answer);
    answer->children[2] = copy_tree(old_r->children[2],answer);
    answer->children[3] = copy_tree(old_r->children[3],answer);
    answer->parent = parent;
    return answer;
  }

  iterator find(const int x_, const int y_, Node<number_type,label_type>* & p) {
    if (!p) {return iterator(NULL);}
    if (p->pt.x==x_ and p->pt.y==y_) {return iterator(p);}
    else if (p->pt.x > x_ and p->pt.y > y_) {
      return find(x_,y_,p->children[0]);
    }
    else if (p->pt.x < x_ and p->pt.y > y_) {
      return find(x_,y_,p->children[1]);
    }
    else if (p->pt.x > x_ and p->pt.y < y_) {
      return find(x_,y_,p->children[2]);
    }
    else if (p->pt.x < x_ and p->pt.y < y_) {
      return find(x_,y_,p->children[3]);
    }
    else {
      return iterator(NULL);
    }
  }

  std::pair<iterator,bool> insert(const Point<number_type> & pt, const label_type & l,
                                  Node<number_type,label_type>* & p, 
                                  Node<number_type,label_type>* & parent) {
    if (!p) { //bottom of tree
      p = new Node<number_type,label_type>(pt,l);
      size_++;
      p->parent = parent;
      return std::make_pair(iterator(p),true);
    }
    if (p->pt.x > pt.x and p->pt.y > pt.y) {
      return insert(pt,l,p->children[0],p);
    }
    else if (p->pt.x < pt.x and p->pt.y > pt.y) {
      return insert(pt,l,p->children[1],p);
    }
    else if (p->pt.x > pt.x && p->pt.y < pt.y) {
      return insert(pt,l,p->children[2],p);
    }
    else if (p->pt.x < pt.x && p->pt.y < pt.y) {
      return insert(pt,l,p->children[3],p);
    }
    else {
      return std::make_pair(iterator(p),false);
    }
  }

  int height(Node<number_type,label_type>* p, std::vector<int> & heights,int depth) {
    if (p->children[0]==NULL and p->children[1]==NULL and
        p->children[2]==NULL and p->children[3]==NULL) {
      heights.push_back(depth);
    }
    else {
      if (p->children[0]!=NULL) {
        height(p->children[0],heights,depth+1);
      }
      if (p->children[1]!=NULL) {
        height(p->children[1],heights,depth+1);
      }
      if (p->children[2]!=NULL) {
        height(p->children[2],heights,depth+1);
      }
      if (p->children[3]!=NULL) {
        height(p->children[3],heights,depth+1);
      }      
    }
    return 0;
  }

  bool sanity_check(Node<number_type,label_type>* p) const {
    if (p == NULL) return true;
    if (p->children[0] != NULL && p->children[0]->parent != p) {
      std::cout << "Error: this node's 0th child's parent should be this node!" << std::endl;
      return false;
    }
    if (p->children[1] != NULL && p->children[1]->parent != p) {
      std::cout << "Error: this node's 1st child's parent should be this node!" << std::endl;
      return false;
    }
    if (p->children[2] != NULL && p->children[2]->parent != p) {
      std::cout << "Error: this node's 2nd child's parent should be this node!" << std::endl;
      return false;
    }
    if (p->children[3] != NULL && p->children[3]->parent != p) {
      std::cout << "Error: this node's 3rd child's parent should be this node!" << std::endl;
      return false;
    }
    return sanity_check(p->children[0]) && sanity_check(p->children[1]) &&
           sanity_check(p->children[2]) && sanity_check(p->children[3]);
  }  
};

//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
//+*+*+**+*+*+*+*+*+*+ MY CODE END *+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
//+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+
#endif
