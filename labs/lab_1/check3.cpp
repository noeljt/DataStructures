#include <iostream>

int main()
{
	std::cout << "Please enter number of values in sequence: ";
	int length;
	std::cin >> length;
	float Numbers[length];
	std::cout << "Please enter floats in sequence: ";

	for (int i = 0; i<length; i++)
	{
		float number;
		std::cin >> number;
		Numbers[i] = number;
	}

	float sum = 0;
	for (int i = 0; i<length; i++)
	{
		sum += Numbers[i];
	}

	float average = (sum/length);
	std::cout << "Average: " << average << std::endl;
	std::cout << "Floats greater than average: " << std::endl;

	for (int i = 0; i<length; i++)
	{
		if (Numbers[i]>average)
		{
			std::cout << Numbers[i] << std::endl;
		}
	}
	return 0;
}