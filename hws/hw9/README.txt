HOMEWORK 9: DISTANCE FIELDS & FAST MARCHING METHOD


NAME:  < Joseph Noel >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Nathan Siviy >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 >



NAIVE ALGORITHM:

Order Notation: O((w*h)^(w*h))

Timing Experiment Data:

Note: all done w/ rainbow

5x5
	real    0m0.010s
	user    0m0.000s
	sys     0m0.000s

10x10
	real    0m0.020s
	user    0m0.000s
	sys     0m0.000s

30x30
	real    0m0.031s
	user    0m0.000s
	sys     0m0.000s

100x100
	real    0m1.421s
	user    0m0.015s
	sys     0m0.000s


300x300
	real    3m29.540s
	user    0m0.000s
	sys     0m0.000s

1000x1000

	Took too long (>10 minutes), aborted program.

Discussion:

	Straightforward but extremely expensive in bigger images.

IMPROVED ALGORITHM:

Order Notation: O((w*h)+(w*h)^p)

Timing Experiment Data:

5x5
	real    0m0.029s
	user    0m0.000s
	sys     0m0.016s

10x10
	real    0m0.090s
	user    0m0.000s
	sys     0m0.000s

30x30
	real    0m0.050s
	user    0m0.000s
	sys     0m0.000s

100x100
	real    0m0.260s
	user    0m0.000s
	sys     0m0.000s

300x300
	real    0m53.009s
	user    0m0.000s
	sys     0m0.000s

1000x1000

	Took too long (>7 minutes), aborted program.

Discussion:

	Slower in smaller images due to extra run through to find black pixels, faster in larger images.

FAST MARCHING METHOD (with a map):

Order Notation: O((w*h)+(w*h))

5x5
	real    0m0.022s
	user    0m0.000s
	sys     0m0.000s

10x10
	real    0m0.028s
	user    0m0.000s
	sys     0m0.015s

30x30
	real    0m0.030s
	user    0m0.015s
	sys     0m0.000s

100x100
	real    0m0.107s
	user    0m0.000s
	sys     0m0.000s

300x300
	real    0m1.019s
	user    0m0.000s
	sys     0m0.000s

1000x1000
	real    0m14.367s
	user    0m0.000s
	sys     0m0.000s

Timing Experiment Data:

Discussion:

Drastically improved runtime, only has to run through entire board twice, once to initialize, and then
another time to add values as it progresses.

DISTANCE FIELD VISUALIZATIONS FOR EXTRA CREDIT:




FAST MARCHING METHOD (with a hash table) FOR EXTRA CREDIT:

Order Notation:

Timing Experiment Data:

Discussion:



MISC. COMMENTS TO GRADER:  
Big monitors, all text fit in my half-windows.






