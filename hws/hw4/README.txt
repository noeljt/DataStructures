HOMEWORK 4: GROCERY LISTS


NAME:  < Joseph Noel >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Nathan Siviy, cplusplus.com,  stackoverflow.com>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 6 >



ORDER NOTATION:
For each request/command,

i = # of different ingredients in the kitchen
u = maximum units of a single ingredient in the kitchen
r = # of different recipes
k = maximum # of different ingredients in a single recipe
v = maximum units of single ingredient in a single recipe
a = maximum # of different ingredients added with a single ’a’ command 
w = maximum units of a single ingredient added with a single ’a’ command


command 'r' / add a recipe: O(k+r)

command 'a' / add ingredients to the kitchen: O(a)

command 'p' / print a recipe: O(3r+rlogr)

command 'm' / make a recipe: O(r+ilogi+3i)

command 'k' / print the contents of the kitchen: O(4i+3(ilogi))

command 's' / suggest recipes: O(r*(klogk+2k)+rlogr+r)


(extra credit) command 'd' / suggest dinner menu:



EXTRA CREDIT:
Describe your implementation of the "suggest dinner menu" option.



MISC. COMMENTS TO GRADER:  
Hope you're happy.


