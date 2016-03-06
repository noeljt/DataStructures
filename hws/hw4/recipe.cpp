//File: Recipe.cpp
//Purpose: Recipe class implementation File

#include <iostream>
#include <iomanip>
#include <list>
#include <fstream>
#include <string>
#include <algorithm>

#include "recipe.h"

Recipe::Recipe(std::string _name) {
	name = _name;
}

void Recipe::addIngredient(std::string ingredient, unsigned int amt) {
	for (unsigned int i=0;i<amt;i++) {
		ingredients.push_back(ingredient);
	}
}

void Recipe::print(std::ostream & ostr) const {
	std::list<std::string> l;
	std::list<std::string>::const_iterator it;
	int count;
	for (it=ingredients.begin();it!=ingredients.end();it++) { //copy ingredient list
		l.push_back(*it);
	}
	l.sort();
	l.unique(); //removes duplicates (unique list)
	ostr << "To make " << name << ", mix together:" << std::endl;
	for (it = l.begin();it!=l.end();it++) {
		count = std::count(ingredients.begin(),ingredients.end(),*it); //amount of ingredient
		if (count==1) { //singular
			ostr << "  1 unit of " << *it << std::endl;
		}
		else { //plural
			ostr << std::right << std::setw(3) << count;
			ostr << " units of " << *it << std::endl;
		}
	}
}