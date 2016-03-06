//File: recipe.h
//Purpose: Recipe class header File
#include <iostream>
#include <iomanip>
#include <list>
#include <fstream>
#include <string>
#include <algorithm>

#ifndef __recipe_h_
#define __recipe_h_

class Recipe {
public:
	Recipe(std::string _name);

	//Accessors
	std::string getName() const {return name;}
	void print(std::ostream & ostr) const;
	std::list<std::string> getIngredients() const {return ingredients;}

	//Modifiers
	void addIngredient(std::string ingredient,unsigned int amt);

	//Other

private:
	std::string name;
	std::list<std::string> ingredients;
};
#endif