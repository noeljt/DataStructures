#include <iostream>

int main()
{
	unsigned int a[10] = {1,2,3,4,5,6,7,8,9,10};
	unsigned int *p;
	for (p=a;p<a+10;p++)
	{
		*p = *p*(*p);
		std::cout << "With asterik: " << *p*(*p) << '\n';
		std::cout << "No asterik: " << p << '\n';
	}
}
