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
#include <queue>
#include <vector>



// ==============================================================
// ==============================================================
// A tiny templated class to store 2D coordinates.  This class works
// with number_type = int, float, double, unsigned char (a 1 byte=8
// bit integer), short (a 2 byte=16 bit integer).

template <class number_type>
class Point {
public:
  Point() : x(0), y(0)	{}
  Point(const number_type& x_, const number_type& y_) : x(x_),y(y_) {}
  // REPRESENTATION
  number_type x;
  number_type y;
};
// ==============================================================
// ==============================================================
// ----------------------------NODE------------------------------
template <class number_type, class label_type>
class Node{
public:
	Node<number_type,label_type>* children[4];
	Node() : parent(NULL)	{
		children[0] = NULL;
		children[1] = NULL;
		children[2] = NULL;
		children[3] = NULL;
	}
	Node(const Point<number_type>& init, const label_type& label_) : label(label_), pt(init), parent(NULL)	{
		children[0] = NULL;
		children[1] = NULL;
		children[2] = NULL;
		children[3] = NULL;
	}
	bool operator!=(const Node<number_type,label_type>* &p)	{
		return (pt != p->pt || label != p->label);
	}
	label_type label;
	Point<number_type> pt;
	Node<number_type,label_type>* parent;
	
};

template <class number_type, class label_type> class QuadTree;

template <class number_type,class label_type>
class DepthIterator{
public:
	DepthIterator() : ptr_(NULL), quad_(NULL)	{}
	DepthIterator(Node<number_type,label_type>* p, const QuadTree<number_type,label_type>* q) : ptr_(p), quad_(q)	{}
	// ------------------Dereferencing Operator-----------------
	const Point<number_type>& operator*() const { return ptr_->pt; }
	// ------------------Comparison Operator--------------------
	bool operator== (const DepthIterator& rgt)	{ return (quad_ == rgt.quad_ && ptr_ == rgt.ptr_);}
	bool operator!= (const DepthIterator& rgt)	{ return (quad_ != rgt.quad_ || ptr_ != rgt.ptr_);}
	// ------------------Increment Operators--------------------
	DepthIterator<number_type,label_type> & operator++()	{// Pre-increment, ++itr
		Node<number_type,label_type>* tmp = ptr_;
		depth_itrPlus(ptr_,tmp);
		return *this;
	}
	DepthIterator<number_type,label_type> operator++(int)	{// Post-increment, itr++
		DepthIterator<number_type,label_type> tmp(*this);
		++(*this);
		return tmp;
	}
	int getDepth() {
		if (this == NULL)	return -1;
		return PrivateGetDepth(this->ptr_);
	}
	label_type getLabel() const {
		return this->ptr_->label;
	}
private:
	Node<number_type,label_type>* ptr_;
	const QuadTree<number_type,label_type>* quad_;
	int PrivateGetDepth(Node<number_type,label_type>* &p)	{
		//if (!p) return 0;
		while (p->parent != NULL)	{
			return 1 + PrivateGetDepth(p->parent);
		}
		return 0;
	}
	void depth_itrPlus(Node<number_type,label_type>* &p, Node<number_type,label_type>* &prev)	{
		//if (!p)	return;
		// Try a while loop going up until it works;
		// This function will handel all things that have to go up to work;
		if (p->children[3] == NULL && p->children[2] == NULL && p->children[1] == NULL && p->children[0] == NULL)	{
			Node<number_type,label_type>* prev;
			while (p->parent != NULL)	{
				//std::cout << "HAS PARENTS" << std::endl;
				prev = p;
				p = p->parent;
				if (p->children[3] == prev)	{
					for (int i = 2; i >=0; i--)	{
						if (p->children[i] != NULL)	{
							p = p->children[i];
							return;
						}
					}
				}else if (p->children[2] == prev)	{
					for (int i = 1; i >=0; i--)	{
						if (p->children[i] != NULL)	{
							p = p->children[i];
							return;
						}
					}
				}else if (p->children[1] == prev)	{
					if (p->children[0] != NULL)	{
						p = p->children[0];
						return;
					}
				}else if(p->children[0] == prev)	{
					// This means that the prev pointer was the last
					// of the children. We'll have to go up further to ++
					continue;
				} else	{
					p = NULL;
					prev = NULL;
					return;
				}
			}
			p = NULL;
			return;
		}else if (p->children[3] != NULL)	{
			p = p->children[3];
		} else if (p->children[2] != NULL)	{
			p = p->children[2];
		} else if (p->children[1] != NULL)	{
			p = p->children[1];
		} else if (p->children[0] != NULL)	{
			p = p->children[0];
		} else	{
			p = NULL;
			prev = NULL;
		}
	}
	int treeHeight(Node<number_type,label_type>* &p)	{
		if (!p)	return 0;
		int nums[4];
		nums[0] = treeHeight(p->children[0]);
		nums[1] = treeHeight(p->children[1]);
		nums[2] = treeHeight(p->children[2]);
		nums[3] = treeHeight(p->children[3]);
		int max = nums[0];
		for (int i = 1; i < 4; i++)	{
			if (max > nums[i])	{
				max = nums[i];
			}
		}
		return 1 + max;
	}
};

template <class number_type,class label_type>
class BreadthIterator{
public:
	BreadthIterator() : ptr_(NULL), quad_(NULL)	{}
	BreadthIterator(Node<number_type,label_type>* p, const QuadTree<number_type,label_type>* q) : ptr_(p), quad_(q)	{}
	// ------------------Dereferencing Operator-----------------
	const Point<number_type>& operator*() const { return ptr_->pt; }
	// ------------------Comparison Operator--------------------
	bool operator== (const BreadthIterator& rgt)	{ return (quad_ == rgt.quad_ && ptr_ == rgt.ptr_);}
	bool operator!= (const BreadthIterator& rgt)	{ return (quad_ != rgt.quad_ || ptr_ != rgt.ptr_);}
	// ------------------Increment Operators--------------------
	/*
	BreadthIterator<number_type,label_type> & operator++()	{// Pre-increment, ++itr
		std::vector<Node<number_type,label_type>* > list;
		list.push_back(this->quad_->root_);
		breadth_itrPlus(this->quad_->root_, list);
		for (unsigned int i = 0; i < list.size()-1; ++i)	{
			//std::cout << list[i]->label <<std::endl;
			if (list[i] == ptr_)	{
				ptr_ = list[i+1];
			}
		}
		return *this;
	}	*/
	BreadthIterator<number_type,label_type> & operator++()	{
		std::queue<Node<number_type,label_type>* > q;
		q.push(quad_->root_);
		bool next = false;
		
		while (!q.empty())	{
			Node<number_type,label_type>* temp = q.front();
			if (next == true)	{
				ptr_ = temp;
				return *this;
			}
			q.pop();
			for (int j = 3; j >=0; j--)	{
				q.push(temp->children[j]);
			}
			if (temp == ptr_)	{
				next = true;
			}
		}
		return *this;
	}
	BreadthIterator<number_type,label_type>  operator++(int) 	{// Post-incriment
		BreadthIterator<number_type,label_type> tmp(*this);
		++(*this);
		return (tmp);
	}
	int getDepth() {
		if (this == NULL)	return -1;
		return PrivateGetDepth(this->ptr_);
	}
	label_type getLabel() const {
		return this->ptr_->label;
	}
private:
	Node<number_type,label_type>* ptr_;
	const QuadTree<number_type,label_type>* quad_;
	// =========================================================
	// Make a helper funtion that keeps track of the number of nodes
	int childCounter(Node<number_type,label_type>* const &p)	{
		// Count the number of non-null child nodes
		int count = 0;
		for (int i = 0; i <=3; i++)	{
			if (p->children[i] != NULL)	 count++;
		}
		return count;
	}
	
	// =========================================================
	int PrivateGetDepth(Node<number_type,label_type>* &p)	{
		if (!p) return 0;
		while (p->parent != NULL)	{
			return 1 + PrivateGetDepth(p->parent);
		}
		return 0;
	}
	// =============================================================
	
	// =============================================================
	void breadth_itrPlus(Node<number_type,label_type>* const &p, std::vector<Node<number_type,label_type>* > &list)	{
		//if (!p) return;
		if (p->children[3] != NULL)	{
			list.push_back(p->children[3]);
		}else if (p->children[2] != NULL)	{
			list.push_back(p->children[2]);
		}else if (p->children[1] != NULL)	{
			list.push_back(p->children[1]);
		}else if (p->children[0] != NULL)	{
			list.push_back(p->children[0]);
		}
		if (p->children[3] != NULL)	{
			breadth_itrPlus(p->children[3],list);
		}else if (p->children[2] != NULL)	{
			breadth_itrPlus(p->children[2],list);
		}else if (p->children[1] != NULL)	{
			breadth_itrPlus(p->children[1],list);
		}else if (p->children[0] != NULL)	{
			breadth_itrPlus(p->children[0],list);
		}
	}
	int treeHeight(Node<number_type,label_type>* &p)	{
		if (!p)	return 0;
		int nums[4];
		nums[0] = treeHeight(p->children[0]);
		nums[1] = treeHeight(p->children[1]);
		nums[2] = treeHeight(p->children[2]);
		nums[3] = treeHeight(p->children[3]);
		int max = nums[0];
		for (int i = 1; i < 4; i++)	{
			if (max > nums[i])	{
				max = nums[i];
			}
		}
		return 1 + max;
	}
	
	
};



template <class number_type, class label_type>
class QuadTree{
public:
	QuadTree() : root_(NULL), size_(0)	{}
	QuadTree(const QuadTree<number_type,label_type> &old) : size_(old.size_)	{
		root_ = this->copy(old.root_,NULL); 
	}
	QuadTree& operator=(const QuadTree<number_type,label_type>& old)	{
		if (&old != this)	{
			this->destroy(root_);
			root_ = this->copy(old.root_,NULL);
			size_ = old.size_;
		}
		return *this;
	}
	~QuadTree()	{
		this->destroy(root_);
		root_ = NULL;
	}
	
	typedef DepthIterator<number_type,label_type> iterator;
	friend class DepthIterator<number_type,label_type>;
	
	typedef BreadthIterator<number_type,label_type> bf_iterator;
	friend class BreadthIterator<number_type,label_type>;
	// bf_begin() && bf_end()
	bf_iterator bf_end() const	{
		return bf_iterator(NULL,this);
	}
	bf_iterator bf_begin() const{
		if (!root_) return bf_iterator(NULL,this);
		return bf_iterator(root_,this);
	}
	// ACCESSORS
	int size() const {return size_;}
	bool operator==(const QuadTree<number_type,label_type>& old) const {
		return (old.root_ == this->root_);
	}
	// begin() && end()
	iterator begin() const {
		if (!root_) return iterator(NULL,this);
		return iterator(root_,this);
	}
	iterator end() const {
		return iterator(NULL,this);
	}
	// HEIGHT
	int height() {
		if (root_ == NULL)	return -1;
		return treeHeight(this->root_);
	}
	// Find && Insert
	iterator find(int xval, int yval)	{ return find(xval,yval,this->root_); }
	std::pair<iterator, bool> insert(Point<number_type> pt, label_type id)	{
		return privateInsert(pt,root_,NULL,id);
	}
	
	// =================================================================
	// Below in public functions are the functions provides in the file.
	// =================================================================
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
		assert ((int)board.size() >= y_max);
		assert ((int)board[0].size() >= x_max);
		// verify that the point stored at this node fits on the board
		assert (p->pt.y >= 0 && p->pt.y < (int)board.size());
		assert (p->pt.x >= 0 && p->pt.x < (int)board[0].size());
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
		plot(p->children[3],board,x_min ,p->pt.x-1,y_min ,p->pt.y-1,draw_lines);
		plot(p->children[2],board,p->pt.x+1,x_max ,y_min ,p->pt.y-1,draw_lines);
		plot(p->children[1],board,x_min ,p->pt.x-1,p->pt.y+1,y_max ,draw_lines);
		plot(p->children[0],board,p->pt.x+1,x_max ,p->pt.y+1,y_max ,draw_lines);
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
		print_sideways(p->children[3],indent+"  ");
		print_sideways(p->children[2],indent+"  ");
		print_sideways(p->children[1],indent+"  ");
		print_sideways(p->children[0],indent+"  ");
	}
private:
	Node<number_type,label_type>* root_;
	int size_;
	Node<number_type,label_type>* copy(Node<number_type,label_type>* old_root, Node<number_type,label_type>* the_parent)	{
		if (old_root == NULL)	{
			return NULL;
		}
		Node<number_type,label_type>* answer = new Node<number_type,label_type>();
		answer->pt = old_root->pt;
		answer->label = old_root->label;
		answer->children[0] = copy(old_root->children[0],answer);
		answer->children[1] = copy(old_root->children[1],answer);
		answer->children[2] = copy(old_root->children[2],answer);
		answer->children[3] = copy(old_root->children[3],answer);
		answer->parent = the_parent;
		return answer;
	}
	void destroy(Node<number_type,label_type>* p)	{
		if (!p) return;
		destroy(p->children[0]);
		destroy(p->children[1]);
		destroy(p->children[2]);
		destroy(p->children[3]);
		delete p;
	}
	int treeHeight(Node<number_type,label_type>* &p)	{
		if (p == NULL)	return -1;
		int nums[4];
		nums[0] = treeHeight(p->children[0]);
		nums[1] = treeHeight(p->children[1]);
		nums[2] = treeHeight(p->children[2]);
		nums[3] = treeHeight(p->children[3]);
		int max = nums[0];
		for (int i = 0; i <= 3; i++)	{
			if (max < nums[i])	{
				max = nums[i];
			}
		}
		return 1+max;
	} 
	iterator find(const int xval,const int yval,Node<number_type,label_type>* p)	{
		if (!p)	return end();
		// Try switching the children around
		if (p->pt.x > xval && p->pt.y > yval)	{
			if (p->children[3] != NULL)
				return find(xval,yval,p->children[3]);
		}else if (p->pt.x < xval && p->pt.y > yval)	{
			if (p->children[2] != NULL)
				return find(xval,yval,p->children[2]);
		}else if (p->pt.x > xval && p->pt.y < yval)	{
			if (p->children[1] != NULL)
				return find(xval,yval,p->children[1]);
		}else if (p->pt.x < xval && p->pt.y < yval)	{
			if (p->children[0] != NULL)
				return find(xval,yval,p->children[0]);
		}else	{
			return iterator(p,this);
		}
		return end();
		
	}
	std::pair<iterator,bool> privateInsert(const Point<number_type> &pnt, Node<number_type,label_type>* &p, Node<number_type,label_type>* theParent, label_type &label)	{
		if (!p)	{
			// This is for when it reaches the bottom of the tree. It finally
			// needs to be inserted.
			p = new Node<number_type,label_type>(pnt,label);
			p->parent = theParent;
			this->size_++;
			return std::pair<iterator,bool>(iterator(p,this),true);
		}else if (p->pt.x > pnt.x && p->pt.y > pnt.y)	{
			return privateInsert(pnt,p->children[3],p,label);
		}else if (p->pt.x < pnt.x && p->pt.y > pnt.y)	{
			return privateInsert(pnt,p->children[2],p,label);
		}else if (p->pt.x > pnt.x && p->pt.y < pnt.y)	{
			return privateInsert(pnt,p->children[1],p,label);
		}else if (p->pt.x < pnt.x && p->pt.y < pnt.y)	{
			return privateInsert(pnt,p->children[0],p,label);
		}else	{
			return std::pair<iterator,bool>(iterator(p,this), false);
		}
		
	}
	
};




// a helper function to print Points to STL output stream
template <class number_type>
inline std::ostream& operator<<(std::ostream &ostr, const Point<number_type> &pt) {
  ostr << "(" << pt.x << "," << pt.y << ")";
  return ostr;
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


// ==============================================================
// ==============================================================


#endif
