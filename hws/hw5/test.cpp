#include <iostream>
#include <vector>

int main() {
	std::vector<int> v;
	v.push_back(5);
	v.push_back(4);
	v.push_back(57);	
	v.push_back(9);
	v.push_back(34);
	v.push_back(67);

	v.sort();
	std::cout << v[0] << std::endl;
}