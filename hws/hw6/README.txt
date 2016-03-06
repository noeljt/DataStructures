HOMEWORK 6: CARCASSONNE RECURSION


NAME:  < Joseph Noel >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Nathan Siviy, Zev Beigel, Joe Horne, cplusplus.com, previous labs/homeworks>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 40 >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)
The dimensions of the board (h and w)? 
The number of tiles (t)? 
The number of road (r) and city (c) edges? 
The number of duplicate tiles?
Whether rotations are allowed?  
Etc. 

O((t*4)^4^t)
My current algorithm is extremely expensive, and is probably the most brute-force method that exists, but it's too late to turn around now. My method goes through every possibility... EVERY. Every peice, every rotation, and every possible place it can fit, only quiting when pieces are pushed off the board or if the resulting peices on the board are not a valid solution. While I acknowledge this is far from the only way to go about doing this, it does work, albeit with an outrageous amount of time required.


SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles with various command line arguments.

(SOLUTIONS, SECONDS)
							    (both)
Puzzle Dimensions No Args All_s All_rot no dimensions
1	   6 6        (1,0)   (1,0) (1,0)   (1,0)
2 	   6 6        (1,1)   (1,1) N/A     N/A
3	   6 6        (0,0)   (0,0) (1,0)   (1,0)
4      6 6        (1,0)   (1,0) (4,2)   (4,2)
5	   6 6        (1,0)   (1,0) (1,4)   (1,6)
6      6 6        (1,0)   (4,0) (7,41)  (7,35)
7	   6 6        (1,0)   (8,0) N/A     N/A
8	   6 6        (1,0)   (1,0) (23,77) (23,88)
9      6 6        (1,0)   (1,0) N/A     N/A


MISC. COMMENTS TO GRADER:  
I cried.


