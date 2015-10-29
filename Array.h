/*
 * Adrienne Bouchie
 * March 11th, 2015
 *
 * Array.h
 * File that includes the class definitons and impementation for the array template class
 *
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>
#include <typeinfo>
using namespace std;
using std::string;


template< typename T > class Array;
template< typename T > istream &operator>> ( istream & input, Array<T> & a);
template< typename T > ostream &operator<< ( ostream & output, const Array<T> & a );


template < typename T >
class Array {


	friend istream &operator>> <>( istream &, Array<T> & );
	friend ostream &operator<< <>( ostream &, const Array<T> & );
     

   public:
        Array();
        Array ( int );
        Array( const Array<T> & );

        void displayElements();
        int getPhysicalSize() const;
        void setPhysicalSize( int );
	static void setDelim( T );
	T getDelim();   
            
        Array<T> &operator =( Array<T> & );
        bool operator ==( const Array<T> & ) const;
        bool operator !=( const Array<T> &right ) const;
        int &operator []( int );
        int operator []( int ) const;
        
        void input(); 
	void testFunction();

   private: 
	static T iVal; 	 
	static T Delim;
	static const int DEFAULT_SIZE = 10;
	int physicalSize;
        T *arr;
};



/*
 * Class Definitions for Array Class Template 
 */

template <typename T> T Array<T>::iVal;
template <typename T> T Array<T>::Delim;


// function that overloads the cin operator
   template < typename T >
   istream &operator>> ( istream &input, Array<T> &a ) {

	a.input();

	return( input );
   }


// function that overloads the cout operator  
   template <typename T>
   ostream &operator<< ( ostream &output, const Array<T> &a ) {

        int i = 0;

        for ( i = 0; i < a.physicalSize; i++ ) {
                output << a.arr[i];

                if ( (i + 1) % 4 == 0 ) {
                        output << endl;
                }
        }
        cout << endl;
        return ( output );
   }


// default constructor that initializes object of class array
   template < typename T > 
   Array<T>::Array() {

        physicalSize = DEFAULT_SIZE;
        arr = new T[physicalSize];
	
        for ( int i = 0; i < physicalSize; i++ ) {
                arr[i] = iVal;
        }

   }     
  

// constructor that takes in an int size and allocates memory of that size for array<T>
   template < typename T >
   Array<T>::Array( int size ) {

	arr = new T[size];
        setPhysicalSize( size );


        for ( int i = 0; i < size; i++ ) {
                arr[i] = iVal;
        }
	

   }


// copy constructor that copy's the array<T> passed as a parameter to the array<T> the function is called on
   template < typename T >
   Array<T>::Array( const Array<T> &arrayToCopy ) {

         if ( arrayToCopy.physicalSize > DEFAULT_SIZE ) {

                arr = new T[arrayToCopy.physicalSize];

        }

        else {
                arr = new T[DEFAULT_SIZE];
        }

        for ( int i = 0; i < arrayToCopy.physicalSize; i++ ) {
                arr[i] = arrayToCopy.arr[i];
        }

        setPhysicalSize( arrayToCopy.physicalSize );

   }



// function that displays the elements in array<T>
   template < typename T >
   void Array<T>::displayElements() {

        for ( int i = 0; i < physicalSize; i++ ) {

                cout << arr[i];
        }

        cout << endl;

   }


// function to return the physical size of array<T>
   template < typename T >
   int Array<T>::getPhysicalSize() const {

        return( physicalSize );
   }


// function to set the physical size of array<T>
   template < typename T >
   void Array<T>::setPhysicalSize( int size ) {

        physicalSize = size;

   }


// function that sets the Delimeter of the array
   template < typename T > 
   void Array<T>::setDelim( T t ) {

	Delim = t;


   }

// function that returns the Delimeter of the array
   template < typename T >
   T Array<T>::getDelim() {
	
	return( Delim );

   }

// overloaded assignment operator to set the array<T> passed to the array<T> the function is called on
   template < typename T >
   Array<T> &Array<T>::operator =(  Array<T> &a ) {

        if ( a.physicalSize > physicalSize ) {

                int arrayPhysicalSize = a.physicalSize;
                T *oldArray =  new T[arrayPhysicalSize];

                for ( int i = 0; i < arrayPhysicalSize; i++ ) {
                        if ( i < physicalSize ) {
                                oldArray[i] = arr[i];
                        }
                        else {
                                oldArray[i] = iVal;
                        }
                }

                delete [] arr;
                arr = oldArray;
                setPhysicalSize( arrayPhysicalSize );
        }

        else {

                for ( int i = 0; i < physicalSize; i++ ) {
                        arr[i] = iVal;
                }
        }


        for ( int i = 0; i < a.physicalSize; i++ ) {
                arr[i] = a.arr[i];
        }

        return ( *this );
   }


// overloaded equality operator to that returns a boolean variable to state whether 2 objects of array<T> are equal
   template < typename T >
   bool Array<T>::operator ==( const Array<T> &a ) const {

        bool isEqual = true;

        if ( physicalSize != a.physicalSize ) {
                isEqual = false;
        }

        else {
                for ( int i = 0; i < physicalSize; i++ ) {
                        if ( arr[i] != a.arr[i] ) {
                                isEqual = false;
                                break;
                        }
                }
        }

        return( isEqual );
   }




// function that overloads the != operator and returns a boolean variable to state whether 2 objects of array<T> are not equal
   template < typename T >
   bool Array<T>::operator !=( const Array<T> &a ) const {


        return ! ( *this == a );

   }


// function that overloads the [] operator and returns and lvalue
   template < typename T >
   int &Array<T>::operator []( int subscript ) {

        if ( subscript < 0 ) {
                cout << "Error! Subscript " << subscript << " is out of range. Defaulting to 0. Program terminating" << endl;
        	subscript = 0;	 
	       
        }

        else if ( subscript > physicalSize ) {

                int arrayPhysicalSize = 2*physicalSize;
                T *oldArray =  new T[arrayPhysicalSize];
                for ( int i = 0; i < arrayPhysicalSize; i++ ) {
                        oldArray[i] = arr[i];
                }

                delete [] arr;
                arr = oldArray;

        }

        return ( arr[subscript] );

   }


// function that overloads the [] and returns an rvalue
   template < typename T >
   int Array<T>::operator []( int subscript ) const {

        if ( subscript < 0 || subscript > physicalSize ) {
                cout << "Error! Subscript " << subscript << " is out of range. Defaulting to 0. Program terminating" << endl;
                subscript = 0;
        }

        return( arr[subscript] );

   }


// function that takes in input from the user and stores it in the array<T>
   template < typename T >
   void Array<T>::input() {

        int arrayPhysicalSize = physicalSize;
	int counter = 0;
	int size = 0;
 	

	cout << "Enter a size for your array: " << endl;
	cin >> size;    
	

	// declare array of type T based on size entered by user
	T numberEntered[size] = {iVal};

	for ( int i = 0; i < size; i++ ) {
		cout << "Enter an element or " << Delim << " to stop: " << endl;   
		cin >> numberEntered[i];
		if ( numberEntered[i] == Delim ) {
			break;
		}
		counter = i+1;
	}
	

	// memory allocation for input 
	arrayPhysicalSize = counter;
	T * oldArray;
        oldArray = new T[arrayPhysicalSize];


	// copy contents of arr to oldArray
        for ( int i = 0; i < arrayPhysicalSize; i++ ) {
        	if( i < physicalSize){
                	oldArray[i] = arr[i];
                } else {
                        oldArray[i] = iVal;
                }
        }


	// deallocate memory that arr was pointing to and assign old array to arr
       	delete [] arr;
       	arr = oldArray;
        setPhysicalSize( arrayPhysicalSize );
        cout << "physical size = " << arrayPhysicalSize << endl;

	// copies contents of numberEntered into arr	
	for ( int i = 0; i < arrayPhysicalSize; i++ ) {
                arr[i] = numberEntered[i];
        }
	
   
   }

