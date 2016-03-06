//
// PROVIDED CODE FOR HOMEWORK 4: GROCERY LISTS
// 
// You may use none, a little, or all of this, as you choose, but we
// strongly urge you to examine it carefully.  You may modify this
// code as you wish to complete the assignment.
//


#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <list>
#include <fstream>
#include <string>
#include <algorithm>

#include "recipe.h"
#include "kitchen.h"


// Helper functions
void readRecipe(std::istream &istr, std::ostream &ostr, Kitchen & kitchen);
void addIngredients(std::istream &istr, std::ostream &ostr, Kitchen &kitchen);
void printRecipe(std::istream &istr, std::ostream &ostr, const Kitchen & kitchen);
void makeRecipe(std::istream &istr, std::ostream &ostr, Kitchen &kitchen);
void recipeSuggestions(std::ostream &ostr, const Kitchen &kitchen);

// The main loop parses opens the files for I/O & parses the input
int main(int argc, char* argv[]) {

  // Check the number of arguments.
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " in-file out-file\n";
    return 1;
  }
  // Open and test the input file.
  std::ifstream istr(argv[1]);
  if (!istr) {
    std::cerr << "Could not open " << argv[1] << " to read\n";
    return 1;
  }
  // Open and test the output file.
  std::ofstream ostr(argv[2]);
  if (!ostr) {
    std::cerr << "Could not open " << argv[2] << " to write\n";
    return 1;
  }

  // the kitchen & recipe list
  Kitchen kitchen;

  // some variables to help with parsing
  char c;
  while (istr >> c) {
    if (c == 'r') {
      // READ A NEW RECIPE
      readRecipe(istr,ostr,kitchen);

    } else if (c == 'a') {
      // ADD INGREDIENTS TO THE KITCHEN
      addIngredients(istr,ostr,kitchen);
      
    } else if (c == 'p') {
      // PRINT A PARTICULAR RECIPE
      printRecipe(istr,ostr,kitchen);

    } else if (c == 'm') {
      // MAKE SOME FOOD
      makeRecipe(istr,ostr,kitchen);

    } else if (c == 'k') {
      // PRINT THE CONTENTS OF THE KITCHEN
      kitchen.printIngredients(ostr);

    } else if (c == 's') {
      // SUGGEST ALL RECIPES THAT CAN BE MADE INDIVIDUALLY FROM THE
      //   CURRENT CONTENTS OF THE KITCHEN
      recipeSuggestions(ostr,kitchen);

    } else if (c == 'd') {
      // EXTRA CREDIT: SUGGEST THE COLLECTION OF RECIPES THAT CAN BE
      // MADE TOGETHER THAT USE THE MAXIMUM NUMBER OF UNITS OF
      // INGREDIENTS
    } else {
      std::cerr << "unknown character: " << c << std::endl;
      exit(0);
    }
  }  
}


void readRecipe(std::istream &istr, std::ostream &ostr, Kitchen & kitchen) {
  int units;
  std::string name, name2;  
  istr >> name;
  // build the new recipe
  Recipe r(name);
  while (1) {
    istr >> units;
    if (units == 0) break;
    assert (units > 0);
    istr >> name2;
    r.addIngredient(name2,units);
  }
  // add it to the list
  kitchen.addRecipe(ostr,r);
}


void addIngredients(std::istream &istr, std::ostream &ostr, Kitchen &kitchen) {
  int units;
  std::string name;
  unsigned int count = 0;
  while (1) {
    istr >> units;
    if (units == 0) break;
    assert (units > 0);
    istr >> name;
    // add the ingredients to the kitchen
    kitchen.addIngredient(name,units);
    count++;
  }
  if (count>1) {
    ostr << count << " ingredients added to kitchen" << std::endl;
  }
  else if (count==1) {
    ostr << count << " ingredient added to kitchen" << std::endl;
  }
}


void printRecipe(std::istream &istr, std::ostream &ostr, const Kitchen & kitchen) {
  std::string name;
  istr >> name;
  std::list<Recipe> recipes = kitchen.getRecipes();
  std::list<Recipe>::const_iterator it;
  bool found = false;
  for (it=recipes.begin();it!=recipes.end();it++) { //find correct recipe
    if ((*it).getName()==name) {
      (*it).print(ostr); //print it
      found = true;
      break;
    }
  }
  if (found==false) {
    ostr << "No recipe for " << name << std::endl;
  }
}


void makeRecipe(std::istream &istr, std::ostream &ostr, Kitchen &kitchen) {
  std::string name;
  istr >> name;
  std::list<Recipe> recipes = kitchen.getRecipes();
  std::list<Recipe>::const_iterator it;
  bool found = false;
  for (it=recipes.begin();it!=recipes.end();it++) { //find correct recipe
    if ((*it).getName()==name) {
      kitchen.makeRecipe(*it, ostr); //make it
      found = true;
      break;
    }
  }
  if (found==false) {
    ostr << "Don't know how to make " << name << std::endl;
  }
}


void recipeSuggestions(std::ostream &ostr, const Kitchen &kitchen) {
  std::list<Recipe> recipes = kitchen.getRecipes();
  std::list<std::string> names;
  std::list<std::string>::iterator name_it;
  std::list<Recipe>::const_iterator it;
  for (it=recipes.begin();it!=recipes.end();it++) {
    if (kitchen.canMake(ostr,*it)==true) {
      names.push_back((*it).getName());
    }
  }
  names.sort();
  if (names.size()>1) {
    ostr << "Recipes that can be prepared:" << std::endl;
    for (name_it=names.begin();name_it!=names.end();name_it++) {
      ostr << "  " << *name_it << std::endl;
    }
  }
  else if (names.size()==1) {
    ostr << "Recipe that can be prepared:" << std::endl;
    for (name_it=names.begin();name_it!=names.end();name_it++) {
      ostr << "  " << *name_it << std::endl;
    }   
  }
  else {
    ostr << "No recipes can be prepared" << std::endl;
  }
}
