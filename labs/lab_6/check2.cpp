#include <iostream>
#include <list>

void reverse_list(std::list<int> & l) {
	unsigned int temp, i;
	unsigned int middle = l.size()/2;
	std::list<int>::iterator it = l.begin();
	std::list<int>::reverse_iterator rit = l.rbegin();
	for (i=0;i<middle;i++) {
		temp = *it;
		*it = *rit;
		*rit = temp;
		rit++, it++;
	}
}

int main() {
	std::list<int>::iterator it;

	//even sized test
	std::cout << "Even Test:" << std::endl;
	std::list<int> ints_even;
	for (unsigned int i=1; i<7;i++) { //6
		ints_even.push_back(i);
	}
	for (it=ints_even.begin();it!=ints_even.end();it++) {
		std::cout << *it << std::endl;
	}	
	reverse_list(ints_even);
	std::cout << "Reverse:" << std::endl;
	for (it=ints_even.begin();it!=ints_even.end();it++) {
		std::cout << *it << std::endl;
	}	

	//odd sized test
	std::cout << "Odd Test:" << std::endl;
	std::list<int> ints_odd;
	for (unsigned int i=1; i<6;i++) { //5
		ints_odd.push_back(i);
	}
	for (it=ints_odd.begin();it!=ints_odd.end();it++) {
		std::cout << *it << std::endl;
	}	
	reverse_list(ints_odd);
	std::cout << "Reverse:" << std::endl;
	for (it=ints_odd.begin();it!=ints_odd.end();it++) {
		std::cout << *it << std::endl;
	}	

	//empty test
	std::cout << "Empty Test:" << std::endl;
	std::list<int> ints_empty;
	reverse_list(ints_empty);
	for (it=ints_empty.begin();it!=ints_empty.end();it++) {
		std::cout << *it << std::endl;
	}	
}