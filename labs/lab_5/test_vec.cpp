#include <iostream>
#include <cmath>
using namespace std;

#include "vec.h"

int main() {

  // ---------------------------------------------------
  // initialize v1 with 10 values...  the multiples of 5
  Vec<int> v1( 10, 0 );
  Vec<int>::size_type i;
  for ( i = 0; i < v1.size(); i++) {
    v1[i] = 5 * i;
  }
  cout << "v1.size() = " << v1.size() << ".  Should be 10.\n";
  cout << "Contents of v1 (multiples of 5):";
  for ( i = 0; i<v1.size(); ++i ) {
    cout << " " << v1[i];
  }
  cout << endl;

  // --------------------------------------------------------------------------
  // make v2 be a copy of v1, but then overwrite the 2nd half with the 1st half
  Vec<int> v2( v1 );
  v2[ 9 ] = v2[ 0 ];
  v2[ 8 ] = v2[ 1 ];
  v2[ 7 ] = v2[ 2 ];
  v2[ 6 ] = v2[ 3 ];
  v2[ 5 ] = v2[ 4 ];
  cout << "Contents of v1 (still multiples of 5):";
  for ( i = 0; i<v1.size(); ++i )
    cout << " " << v1[i];
  cout << endl;
  cout << "Contents of v2 (now palindrome):";
  for ( i = 0; i<v2.size(); ++i )
    cout << " " << v2[i];
  cout << endl;

  // ------------------------------------------
  // make v3 be a copy of v2, but then clear it
  Vec<int> v3;
  v3 = v2;
  v3.clear();
  cout << "\nAfter copying v2 to v3 and clearing v3,  v2.size() = "
       << v2.size() << " and v3.size() = " << v3.size() << endl;
  cout << "Contents of v2 (should be unchanged):";
  for ( i = 0; i<v2.size(); ++i ) {
    cout << " " << v2[i];
  }
  cout << endl;

  // --------------
  // test push back
  cout << "\nNow testing push_back.  Adding 3, 6, 9 to v2:\n";
  v2.push_back( 3 );
  v2.push_back( 6 );
  v2.push_back( 9 );
  cout << "v2 is now: \n";
  for ( i = 0; i<v2.size(); ++i ) {
    cout << " " << v2[i];
  }
  cout << endl;

  // -----------
  // test resize
  v1.resize(20,100);
  cout << "\nNow testing resize.  Resizing v1 to have 20 elements and v2 to have 2 elements\n";
  cout << "v1 is now (should have 100s at the end): \n";
  for ( i = 0; i<v1.size(); ++i )
    cout << " " << v1[i];
  cout << endl;
  v2.resize(2,100);
  cout << "v2 is now: \n";
  for ( i = 0; i<v2.size(); ++i )
    cout << " " << v2[i];
  cout << endl;

  // ------------------------
  // test of a vec of doubles
  cout << "\nStarting from an empty vector, z,  of doubles and doing\n"
       << "5 push_backs\n";
  Vec<double> z;
  for ( i = 0; i<5; ++i )
    z.push_back( sqrt( double(10*(i+1)) ));
  cout << "Contents of vector z: ";
  for ( Vec<double>::size_type j = 0; j < z.size(); j++ )
    cout << " " << z[j];
  cout << endl;



  // ADD MORE TEST CASES HERE
  typename Vec<int>::iterator it;

  //first value test, just once
  int a1[10] = {1,2,3,4,5,6,5,4,3,2};
  Vec<int> v10;
  for (i=0;i<10;i++)
  {
    v10.push_back(a1[i]);
  }
  v10.print();
  std::cout<<"\nTesting remove_matching_element first value: " << std::endl;
  std::cout<< "Should be 1: " << remove_matching_elements(v10,1) << std::endl;
  std::cout<< "Should have no 1's:";
  for (it=v10.begin();it!=v10.end();it++)
  {
    std::cout << ' ' << *it; 
  }
  v10.print();
  //remove multiple
  std::cout << "Remove 5's:\n";
  std::cout << "Should be 2: " << remove_matching_elements(v10,5);
  std::cout << "\nShould have no 5's:";
  for (it=v10.begin();it!=v10.end();it++)
  {
    std::cout << ' ' << *it;
  }  
  std::cout << "\n\nm_alloc should change to 8...";
  v10.print();

  //remove last value
  std::cout << "\nShould have no 2's:";
  remove_matching_elements(v10,2);
  for (it=v10.begin();it!=v10.end();it++)
  {
    std::cout << ' ' << *it; 
  }

  //remove no value
  std::cout << "\nShould remain unchanged:";
  remove_matching_elements(v10,10);
  for (it=v10.begin();it!=v10.end();it++)
  {
    std::cout << ' ' << *it; 
  }

  //double type
  std::cout << "\nShould all be 1.1: ";
  Vec<double> new_v(5,1.1);
  for (i=0;i<new_v.size();i++)
  {
    std::cout << ' ' << new_v[i];
  }
}
