#include <iostream>
#include <vector>



void reverse_vector(std::vector<int> & v) {
	if (v.size()!=0) { //not empty
		unsigned int temp, middle;
		if (v.size()%2!=0) { //odd size
			middle = (v.size()-1)/2;
			for (unsigned int i=0;i<middle;i++) {
				temp = v[i];
				v[i] = v[v.size()-(i+1)];
				v[v.size()-(i+1)] = temp;
			}
		}
		else { //even size
			middle = (v.size()/2);
			for (unsigned int i=0;i<middle;i++) {
				temp = v[i];
				v[i] = v[v.size()-(i+1)];
				v[v.size()-(i+1)] = temp;
			}
		}
	}
}

int main() {
	//even sized test
	std::cout << "Even Test:" << std::endl;
	std::vector<int> ints_even;
	for (unsigned int i=1; i<7;i++) { //6
		ints_even.push_back(i);
	}
	for (unsigned int i=0;i<ints_even.size();i++) {
		std::cout << ints_even[i] << std::endl;
	}	
	reverse_vector(ints_even);
	std::cout << "Reverse:" << std::endl;
	for (unsigned int i=0;i<ints_even.size();i++) {
		std::cout << ints_even[i] << std::endl;
	}

	//odd sized test
	std::cout << "Odd Test:" << std::endl;
	std::vector<int> ints_odd;
	for (unsigned int i=1; i<6;i++) { //5
		ints_odd.push_back(i);
	}
	for (unsigned int i=0;i<ints_odd.size();i++) {
		std::cout << ints_odd[i] << std::endl;
	}	
	reverse_vector(ints_odd);
	std::cout << "Reverse:" << std::endl;
	for (unsigned int i=0;i<ints_odd.size();i++) {
		std::cout << ints_odd[i] << std::endl;
	}

	//empty test
	std::cout << "Empty Test:" << std::endl;
	std::vector<int> ints_empty;
	reverse_vector(ints_empty);
	for (unsigned int i=0;i<ints_empty.size();i++) {
		std::cout << ints_empty[i] << std::endl;
	}	
}