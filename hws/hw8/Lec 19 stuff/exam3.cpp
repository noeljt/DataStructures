#include <map>
#include <iostream>
#include <iomanip>

#include "ds_set_lec19.h"

void print_in_order(std::ostream & ostr, const TreeNode<int>* p) {
	if (p) {
		print_in_order(ostr, p->left);
		ostr << p->value << "\n";
		print_in_order(ostr, p->right);
	}
}

int main() {
	ds_set<int> holder;
	holder.insert(1);
	holder.insert(2);
	holder.insert(3);
	holder.insert(4);
	holder.insert(5);
	holder.insert(6);
	holder.insert(7);

	std::ostream ostr;

	print_in_order(ostr, *holder.begin());
	return 0;
}