//File: kitchen.h
//Purpose: Kitchen class header file

#include <iostream>
#include <iomanip>
#include <list>
#include <fstream>
#include <string>
#include <algorithm>

#include "recipe.h"

#ifndef __kitchen_h_
#define __kitchen_h_

 class Kitchen {
 public:
 	Kitchen();

 	//Accessors
 	void printIngredients(std::ostream & ostr) const;
 	std::list<Recipe> getRecipes() const {return recipes;}

 	//Modifiers
 	void addIngredient(std::string ingredient, unsigned int amt);
 	void addRecipe(std::ostream & ostr, Recipe & r);
 	void makeRecipe(const Recipe & r, std::ostream & ostr);
 	
 	//Other
 	bool canMake(std::ostream & ostr, const Recipe & r) const;

 private:
 	std::list<std::string> ingredients;
 	std::list<Recipe> recipes;
 };

 bool compare_amt(const std::string & in1, const std::string & in2);
 #endif