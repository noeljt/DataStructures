#include <iostream>
#include <cmath>

void compute_square(int a[], int b[], unsigned int n)
{
	int *pa, *pb;
	pa=a;
	pb=b;
	for (;pa<a+n;pa++,pb++)
	{
		*pb = *pa*(*pa);
	}
}

int main()
{
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	int b[10];
	compute_square(a,b,10);
	int *pb = b;
	for (pb=b;pb<b+10;pb++)
	{
		std::cout << *pb << std::endl;
	}

	int c[10] = {0,0,0,0,0,0,0,0,0,0};
	compute_square(c,b,10);
	for (pb=b;pb<b+10;pb++)
	{
		std::cout << *pb << std::endl;
	}
	int d[5] = {1,2,3,4,5};
	int e[5];
	compute_square(d,e,5);
	for (pb=e;pb<e+5;pb++)
	{
		std::cout << *pb << std::endl;
	}
	return 0;
}