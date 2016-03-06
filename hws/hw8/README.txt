HOMEWORK 8: QUAD TREES AND TREE ITERATION


NAME:  < Joseph Noel >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< cplusplus.com,
  Nathan Siviy >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 23 >



ORDER NOTATION ANALYSIS: 
Give the big O notation of each of the QuadTree operations and justify
your answer for the non trivial operations (please be concise!)
Analyze both the running time and the additional memory usage needed
(beyond the space allocated for the existing tree structure).  You may
assume that the tree is reasonably well balanced for all operations.


n = the number of elements in the tree
h = height of tree
L = # of leaves


size()
  running time: O(1)
  memory usage: n

insert()
  running time: O(log(n))
  memory usage: n

find()
  running time: O(log(n))
  memory usage: n

height()
  running time: O(n)
  memory usage: n+L
    -stores all depths to leaves in a vector, returns highest value

begin()
  running time: O(1)
  memory usage: n

end()
  running time: O(1)
  memory usage: n

bf_begin()
  running time: O(1)
  memory usage: n

bf_end()
  running time: O(1)
  memory usage: n

operator++()
  running time: O(h)
    -ideally it would be O(1), but in worst case it would travel all the way up
     the tree checking for possibilities
  memory usage: n

operator*()
  running time: O(1)
  memory usage: n

getLabel()
  running time: O(1)
  memory usage: n

getDepth()
  running time: O(h)
    -worst case scenario of it being furthest node from top
  memory usage: n

copy constructor
  running time: O(n)
    -has to run through entire tree
  memory usage: n+n
    -temporarily two trees

assignment operator
    -same as opy constructor
  running time: O(n)
  memory usage: n+n

destructor
  running time: O(n)
    -has to run through entire tree
  memory usage: n



EXTRA CREDIT:  TREE BALANCING
How does the point insertion order affect the shape of the resulting
QuadTree object? What are specific examples of the worst case and best
case?  Discuss your stratgy for reordering the input to rebalance the
tree.  Paste example output with and without your rebalancing.






MISC. COMMENTS TO GRADER:  
I use my desktop for this, if words appear to go off your window, they didn't on mine.