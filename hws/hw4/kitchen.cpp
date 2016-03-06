//File: kitchen.cpp
//Purpose: kitchen class implementtion

#include <iostream>
#include <iomanip>
#include <list>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cstdlib>

#include "recipe.h"
#include "kitchen.h"

Kitchen::Kitchen() {}

void Kitchen::printIngredients(std::ostream & ostr) const {
	std::list<std::string> l;
	std::list<std::string>::const_iterator it;
	std::list<std::string>::iterator it_2;
	int temp;
	int count;

	for (it = ingredients.begin();it!=ingredients.end();it++) { //copy ingredient list
		l.push_back(*it);
	}
	l.sort();
	l.unique(); //list of unique ingredient names, removes duplicates
	for (it_2=l.begin();it_2!=l.end();it_2++) {
		std::ostringstream ss;
		count = std::count(ingredients.begin(),ingredients.end(),*it_2);
		ss << (*it_2) << " " << count;
		(*it_2) = ss.str();
	}
	l.sort(compare_amt);
	for (it_2=l.begin();it_2!=l.end();it_2++) {
		temp = (*it_2).find(' ');
		(*it_2) = (*it_2).substr(0,temp);
	}
	ostr << "In the kitchen:" << std::endl;
	for (it = l.begin();it!=l.end();it++) {
		count = std::count(ingredients.begin(),ingredients.end(),*it); //amount of ingredient
		if (count==1) { //singular
			ostr << "  1 unit of " << *it << std::endl;
		}
		else { //plural
			ostr << "  " << count << " units of " << *it << std::endl;
		}
	}
}

void Kitchen::addIngredient(std::string ingredient, unsigned int amt) {
	for (unsigned int i=0;i<amt;i++) {
		ingredients.push_back(ingredient);
	}
}

void Kitchen::addRecipe(std::ostream & ostr, Recipe & r) {
	std::list<Recipe>::iterator it;
	bool found = false;
	for (it=recipes.begin();it!=recipes.end();it++) {
		if ((*it).getName()==r.getName()) {
			found = true;
		}
	}
	if (found==false) {
		recipes.push_back(r);
		ostr << "Recipe for " << r.getName() << " added" << std::endl;
	}
	else {
		ostr << "Recipe for " << r.getName() << " already exists" << std::endl;
	}
}

void Kitchen::makeRecipe(const Recipe & r, std::ostream & ostr) {
	std::list<std::string> needed = r.getIngredients();
	needed.sort();
	std::list<std::string> needed_unique = needed;
	needed_unique.unique();
	bool enough = true;
	std::list<std::string>::iterator it;
	unsigned int count_k, count_r;
	for (it=needed.begin();it!=needed.end();it++) { //are there enough ingredients
		count_r = std::count(needed.begin(),needed.end(),*it);
		count_k = std::count(ingredients.begin(),ingredients.end(),*it);
		if (count_r>count_k) {
			enough = false;
			break;
		}
	}
	if (enough==true) { //yes, remove ingredients used
		for (it=needed_unique.begin();it!=needed_unique.end();it++) {
			count_r = std::count(needed.begin(),needed.end(),*it);
			for (unsigned int i=0; i<count_r;i++) {
				ingredients.erase(std::find(ingredients.begin(),ingredients.end(),*it));
			}
		}
		ostr << "Made " << r.getName() << std::endl;
	}
	else { //no, report what ingredients are lacking
		ostr << "Cannot make " << r.getName() << ", need to buy:" << std::endl;
		for (it=needed_unique.begin();it!=needed_unique.end();it++) {
			count_r = std::count(needed.begin(),needed.end(),*it);
			count_k = std::count(ingredients.begin(),ingredients.end(),*it);
			if (count_r>count_k) {
				ostr << "  " << (count_r-count_k);
				if ((count_r-count_k)>1) {
					ostr << " units of " << *it << std::endl;
				}
				else {
					ostr << " unit of " << *it << std::endl;
				}
			}
		}	
	}
}

bool Kitchen::canMake(std::ostream & ostr, const Recipe & r) const {
	std::list<std::string> needed = r.getIngredients();
	needed.sort();
	std::list<std::string> needed_unique = needed;
	needed_unique.unique();
	bool enough = true;
	std::list<std::string>::iterator it;
	unsigned int count_k, count_r;
	for (it=needed.begin();it!=needed.end();it++) { //are there enough ingredients
		count_r = std::count(needed.begin(),needed.end(),*it);
		count_k = std::count(ingredients.begin(),ingredients.end(),*it);
		if (count_r>count_k) {
			enough = false;
			break;
		}
	}
	if (enough==true) { //yes
		return true;
	}
	else {
		return false; //not quite
	}
}

bool compare_amt(const std::string & in1, const std::string & in2) { //for sorting by amount
	int amt1;
	std::string ingredient1;
	int amt2;
	std::string ingredient2;
	unsigned int temp;
	std::string temp_s;

	temp = in1.find(' ');
	temp_s = in1.substr(temp+1);
	ingredient1 = in1.substr(0,temp-1);
	amt1 = std::atoi(temp_s.c_str());

	temp = in2.find(' ');
	temp_s = in2.substr(temp+1);
	ingredient2 = in2.substr(0,temp-1);
	amt2 = std::atoi(temp_s.c_str());

	if (amt1==amt2) {
		return (ingredient1<ingredient2);
	}
	else {
		return (amt1<amt2);
	}

}