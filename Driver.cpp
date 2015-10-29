/*
 * Adrienne Bouchie
 * March 11th, 2015
 *
 * Driver program that tests out the Array class template definition
 * Driver.cpp
 *
 */


#include "Array.h"
#include <iostream>
#include <string>
using namespace std;
using std::string;


// template function that tests the array of type F 
   template <typename F> 
   void testFunction ( Array<F> f ) {

	char answer; 
	
	cin >> f;
	cout << "Array1:" << endl;
	cout << f;

   	Array<F> array2;
	cin >> array2;   
	cout << "Array2:" << endl;
	cout << array2; 
   
	if ( f == array2 ) {
		cout << "Arrays are equal" << endl;
	}
	else {
		cout << "Arrays are not equal" << endl;
		cout << "Would you like to set array2 to be equal array1? (Y/N) " << endl;
		cin >> answer;
		if ( answer == 'Y' || answer == 'y' ) {
			array2 = f;
			cout << " Array2 now = " << endl; 
			cout << array2;
		}
		else 
			cout << "Okay goodbye!" << endl;
	}
		
   }


main() { 
 
	
	Array<int>::setDelim(-999);
	Array<double>::setDelim(-999);
	Array<char>::setDelim('*');
	Array<string>::setDelim( "----");

	Array<int> integers;	
	Array<double>dbl;
	Array<char>chr;
	Array<string>str;

	cout << "Testing array of INTEGERS " << endl;
	testFunction( integers );
	
	cout << "Testing array of DOUBLES " << endl;
	testFunction( dbl );

	cout << "Testing array of CHARS " << endl;
	testFunction( chr );

	cout << "Testing array of STRINGS " << endl;
	testFunction( str );	

}

