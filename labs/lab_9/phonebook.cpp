// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// add a number, name pair to the phonebook
void add(map<int,string> &phonebook, int number, string const& name) { //O(log(n))
  phonebook.insert(make_pair(number, name));
}

// given a phone number, determine who is calling
void identify(map<int,string> & phonebook, int number) { //O(log(n))
  if (phonebook.find(number)==phonebook.end()) 
    cout << "unknown caller!" << endl;
  else 
    cout << phonebook[number] << " is calling!" << endl;
}


int main() { //O(nlog(n))
  // create the phonebook; initially all numbers are unassigned
  map<int,string> phonebook; //O(1)

  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 4444);
}


/*
For Vectors:

RunTime:
add is O(1)
identify is O(1)
vector is O(N)
main is O(n)

Memory is O(N)

Changing to 7 or 10 digit number would increase memory N,
since the numbers are stored as the index and vectors being
blocks of memory will take as many blocks in a row as it needs.


Part 2:
Vector implimentation has better runtime, but maps use less memory.
*/