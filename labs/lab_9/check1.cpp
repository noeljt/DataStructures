#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

std::map<std::string, int> from_file(char* & f_name ) {
	std::string s;
	std::ifstream f(f_name);
	std::map<std::string, int> sequence;
	if (!f.good()) {
		std::cerr << "Can't open " << f_name << " to read.\n";
		exit(1);
	}
	else if (f.is_open()) {
		while (f >> s) {
			++sequence[s];
		}
	}
	return sequence;
}

std::map<std::string, int> from_cin() {
	std::string s;
	std::map<std::string, int> sequence;
	std::cout << "Enter sequence, enter e to exit." << std::endl;
	while (std::cin >> s) {
		if (s=="e") {
			break;
		}
		++sequence[s];
	}
	return sequence;
}

std::vector<std::pair<std::string, int> > find_modes(std::map<std::string, int> & sequence) {
	std::vector<std::pair<std::string, int> > modes;
	std::map<std::string, int>::const_iterator it;
	for (it=sequence.begin();it!=sequence.end();it++) {
		if (it==sequence.begin()) {
			modes.push_back(*it);
		}
		else {
			if (it->second>modes[0].second) {
				modes.clear();
				modes.push_back(*it);
			}
			else if(it->second==modes[0].second) {
				modes.push_back(*it);
			}
		}
	}
	return modes;
}

int main(int argc, char* argv[]) {
	std::map<std::string, int> sequence;
	if (argc>1) {
		sequence = from_file(argv[1]);
	}
	else {
		sequence = from_cin();
	}
	std::vector<std::pair<std::string,int> > modes = find_modes(sequence);

	std::vector<std::pair<std::string, int> >::const_iterator it;
	if (modes.size()==1) {
		std::cout << "The mode is:" << std::endl;
		std::cout << modes[0].first << ", which occured " << modes[0].second << " times." << std::endl;
	}
	else {
		std::cout << "The modes are:" << std::endl;
		for (it=modes.begin();it!=modes.end();it++) {
			std::cout << it->first << ", which occured " << it->second << " times." << std::endl;
		}
	}
	return 0;
}