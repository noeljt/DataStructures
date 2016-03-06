HOMEWORK 7: WORD FREQUENCY MAPS


NAME:  < Joseph Noel >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Nathan Siviy,
  cppreference.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 9 >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

n = total number of words in the sample text file
m = number of unique words in the file
w = width of the sequencing window
p = average number of words observed to follow a particular word

	Since we have to write the order notation later in this file, I won't put it here...
As for the performance of my algorithm(s), they all run near instantly in the tests I did, at most still under 1 second of run time.  There is room for improvement though, it would just have required me to re-write the entire program once I went from two window to three.  The idea of making it work for any size window is still difficult for me though, would required an unspecified number of nested maps... fun stuff. 

How much memory will the map data structure require, in terms of n, m,
w, and p (order notation for memory use)?

O( m * p ^ (w-1) )

What is the order notation for performance (running time) of each of
the commands?

Load (win2) 									O(n)
Load (win3) 									O(n)

Print (win2) 									O(log(m)+(p+p))
Print (win3 - 1 word) 							O(log(m)+(p+p)+(p*p+p))
Print (win3 - 2 word)							O(log(m)+(p*p+p))

L = length specified

Generate (win2)									O(l*(log(m)+p))
Generate (win3 - 1 word - common)				O(log(m)+(p*p)+(l*(log(m)+log(p)+p)))
Generate (win3 - 2 word - common)				O(l*(log(m)+log(p)+p))
Generate (win3 - 1 word - random)				O(log(m)+(p*p)+(l*(log(m)+log(p)+p)))
Generate (win3 - 2 word - random)				O(l*(log(m)+log(p)+p))


EXTRA CREDIT
Parsing & using punctuation data, implementation supports *any*
window size, new test cases (describe & summarize performance, but
don't include large datasets with submission).

N/A

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


