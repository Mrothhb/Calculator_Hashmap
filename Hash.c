//==========================================================================
// cs12xcm                         Homework 6             Matt Roth 
//
// February 11 2019	
//--------------------------------------------------------------------------
// File: Hash.c
//
// Description:		The Hash will use a Hash Table style data structure to 
//		efficiently store the data element (Objects of UCSDStudent in this case)
//		in an array of a specified length. Elements will be able to be inserted
//		into the list at empty locations, or in an occupied location, as long as
//		the current element in the occupied location has a lower precedence
//		(search) time than the incoming element. The table can be searched for a
//		specific name as well. Once the table becomes full, no new elements can
//		be inserted and the output will display an error message to indicate 
//		such a condition. 
//==========================================================================
#include <cstdlib>
#include <string>
#include "Hash.h"

using namespace std;

//=========================================================================
// class Hash
//
// Description:			The HashTable class is a HashTable data structure 
//		implementation. memory will be allocated to an array which will hold the
//		elements of the table as 'Base' objects. Each Base object will contsain 
//		a student name and number. The table will use a hashing alogrithm
//		to efficiently store and retreive data on the objects being 
//		stored in the table. The element requested will be located
//		and replaced, and if not found it will take an empty spot on
//		the table, or bump an object that has a lower search record. 
//		If the table is full the item will not be inserted, and an
//		error message will be returned. 	
//  
// Data Fields:
//     debug - turn on or off the debug  
//     counter - The variable to hold the count for probe sequence 
//
// Public functions:
//					HashTable - constructor(s) for initialization
//					~HashTable - destructor 
//					Insert - insert an element in the table  
//					Locate - locate an element in the table  
//					Lookup - search for an element in the table 
//					Write - toString method 
//==========================================================================

//static debug constants for debug messages
static const char AND[] = " and ";
static const char DEBUG_ALLOCATE[] = " - Allocated]\n";
static const char DEBUG_DEALLOCATE[] = " has been deallocated]\n";
static const char DEBUG_LOCATE[] = " - Locate]\n";
static const char DEBUG_LOOKUP[] = " - Lookup]\n";
static const char BUMP[] = "[Bumping To Next Location...]\n";
static const char COMPARE[] = " - Comparing ";
static const char FOUND_SPOT[] = " - Found Empty Spot]\n";
static const char HASH[] = "[Hash Table ";
static const char HASH_VAL[] = "[Hash value is: ";
static const char INSERT[] = " - Inserting ";
static const char PROCESSING[] = "[Processing ";
static const char TRYING[] = "[Trying index ";

//debug initialize
bool HashTable :: debug = 0;
int HashTable :: counter = 0;

void HashTable :: Set_Debug (int option)
/***************************************************************************
% Routine Name : HashTable :: Set_Debug (public)
% File :         hash.c
% 
% Description :  This function sets debug mode on or off
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% option             true should set debug mode on, false should set debug
%                    mode off.
***************************************************************************/
{
	//set the debug accordingly from incoming parameter 
	if(option){
		debug = 1;
	}else{
		debug = 0;
	}
}

HashTable :: HashTable (int sz) : size (sz),
	table_count(++counter), occupancy (0), table (new Base *[sz]), 
	probeCount (new int[sz])
/***************************************************************************
% Routine Name : HashTable :: HashTable (public)
% File :         hash.c
% 
% Description :  This function allocates an initializes the memory
%                associated with a hash table.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% size               The number of elements for the table...MUST BE PRIME!!!
***************************************************************************/
{

	//initialize the table array and probe array to null values
	for(int i =0; i<this->size; i++){
		table[i] = NULL;
		probeCount[i] = 0;
	}

}	/* end: HashTable */

HashTable :: ~HashTable (void)
/***************************************************************************
% Routine Name : HashTable :: ~HashTable  (public)
% File :         hash.c
% 
% Description :  deallocates memory associated with the Hash Table.  It
%                will also delete all the memory of the elements within
%                the table.
***************************************************************************/
{
	//delete all the table elements manually
	for(int i = 0; i<size; i++){

		if(table[i]){

			delete table[i];
		}

		table[i] = NULL;
	}
	
	//delete the array containing the probe counts 
	delete[] probeCount;
	
	//delete the entire table 
	delete[] table;
	
	if(debug){

		cerr<<(const char*)HASH<<table_count<<
		(const char*)DEBUG_DEALLOCATE<<"\n";
	}

	
}	/* end: ~HashTable */

bool HashTable :: Insert (Base * element, int initialCount)
/***************************************************************************
% Routine Name : HashTable :: Insert (public)
% File :         hash.c
% 
% Description : This function will insert the element in the hash table.
%		If the element cannot be inserted, false will be returned.
%		If the element can be inserted, the element is inserted
%		and true is returned.  Duplicate insertions will
%		cause the existing element to be deleted, and the duplicate
%		element to take its place.
%
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% element            The element to insert.
% recursiveCall      Whether or not we are entering from recursion
% <return>           true or false indicating success or failure of insertion
***************************************************************************/
{
	//set the global count to the incoming param (1 if start)
	this->count = initialCount;

	//local probe count tracker
	int oldProbeCount = 0;
	
	//pointer to hold the temp data for bumping an element 
	void * bump;

	if(debug){
		cerr<<(const char *)HASH<<(long)table_count<<(const char *)INSERT<<
		(char *)*element<<"]"<<"\n";
	}

	//if the table is full return false - no more elements please!
	if(this->occupancy >= this->size){

		cerr<<"The table is full!";
		return false;

	}

	//call to Locate() and if the element is found at index return true 
	if(Locate(element)){
		
		//update the probe count at index and insert the element
		probeCount[index] = count;
		table[index] = element;

		return true;
	}
	
	//if an empty spot is found return true 
	if(table[index] == NULL){

		if(debug){

			cerr<<(const char *)HASH<<(long)table_count<<
				(const char *)FOUND_SPOT<<"\n";
		}
		
		//update the probe count at index and insert the element 
		probeCount[index] = count;
		table[index] = element;

		//increase the occupancy 
		this->occupancy++;

		return true;
	
	//the element was not located and there was not an empty spot
	}else{ 
		
		if(debug){
			cerr<<(const char *)BUMP<<"\n";
		}
		
		//store the element at the index in pointer
		bump = table[index];
		
		//store the bumped element probe count 
		oldProbeCount = probeCount[index];
		
		//insert the parameter element at index 
		table[index] = element;
		
		//update the probe count 
		probeCount[index] = count;
		
		//recursive call to insert with the bumped element - go find a new spot 
		Insert((Base *)bump, ++oldProbeCount);
	}

	return true;

}

bool HashTable :: Locate (Base * element)
/**********************************************************************
% Routine Name : HashTable :: Locate (private)
% File :         HashTable.c
% 
% Description : This function will locate the location in the
%               table for the insert or lookup.
%
% Parameters descriptions :
%  
% name               description
% ------------------ -------------------------------------------------
% element            The element needing a location.
% <return>           true if item found, or false if not found
**********************************************************************/
{
	//initialized local variable for locate hash
	long ASCII_SUM = (long)*element;
	int TABLE_SIZE = this->size;
	int INC_MOD = 4;
	int BY_ONE = 1;
	int initLocation = 0;
	int increment = 0;
	int currentIndex = 0;

	if(debug){

		cerr<<(const char *)HASH<<table_count<<(const char *)DEBUG_LOCATE<<"\n";

		cerr<<(const char *)PROCESSING<<(char *)*element<<"]"<<"\n";

		cerr<<(const char *)HASH_VAL<<(long)ASCII_SUM<<"]"<<"\n";


	}

	//check for null parameter
	if(element == NULL){

		cerr<<"Error - Null element";
		return false;
	}
	
	//calculate the initial location 
	initLocation = ASCII_SUM % TABLE_SIZE;
	
	//calculate the increment 
	increment = (ASCII_SUM % (TABLE_SIZE - BY_ONE))+ BY_ONE;
	
	//calculate the current index - may change from recurse 
	currentIndex = (initLocation + (count-BY_ONE)*increment)% TABLE_SIZE;

	//search the table for our element (parameter)
	for(int i = 0; i<TABLE_SIZE; i++){
		
		//set the index to the current index 
		this->index = currentIndex;
	
		if(debug){
			cerr<<(const char *)TRYING<<(long)currentIndex<<"]"<<"\n";
		}
		
		//if the index is empty return false, empty spot
		if(table[currentIndex] == NULL){

			return false;
		}
		
		//if the element is found return true 
		if(table[currentIndex] == element){

			return true;
		}

		if(debug){

			cerr<<(const char *)HASH<<(long)table_count<<(const char *)
				COMPARE<<(char *)*element<<(const char *)AND<<(char *)*
				table[currentIndex]<<"]"<<"\n";
		}
		
		//if the probecount for the checking element is less than the count 
		if(this->probeCount[currentIndex] < this->count){

			return false;
		}

		//set the new current index to the incremented mod value//
		currentIndex = (currentIndex + increment) % TABLE_SIZE;
		++count;

	}

	//return false when table is full 
	return false;

}

Base * HashTable :: Lookup (Base * element)
/***************************************************************************
% Routine Name : HashTable :: Lookup (public)
% File :         hash.c
% 
% Description : This function will lookup the element in the hash table.  If
%               found a pointer to the element ip"@]s returned.  If the element
%               is not found, NULL will be returned to the user.
%
% Parameters descriptions :
%  
% name               description
% ------------------ ------------------------------------------------------
% element            The element to insert or to lookup.
% <return>           A pointer to the element if found, else NULL
***************************************************************************/
{
	//set the global count to one 
	this->count = 1;
	
	if(debug){

		cerr<<(const char *)HASH<<(long)table_count<<
		(const char *)DEBUG_LOOKUP<<"\n";
	}
	
	//make a call to Locate with the element parameter 
	if(Locate(element)){	
		
		//if the element is found return it 
		return table[index];
	}
	
	//the element was not found here 
	return NULL;


}

ostream & HashTable :: Write (ostream & stream)
/***************************************************************************
% Routine Name : HashTable :: Write (public)
% File :         hash.c
% 
% Description : This funtion will output the contents of the hash table
%               to the stream specificed by the caller.  The stream could be
%               cerr, cout, or any other valid stream.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% stream             A reference to the output stream.
% <return>           A reference to the output stream.
***************************************************************************/
{
	stream << "Hash Table " << table_count << ":\n"
		<< "size is " << size << " elements, "
		<< "occupancy is " << occupancy << " elements.\n";

	/* go through all table elements */
	for (int index = 0; index < size; index++)
		if (table[index])
			table[index]->Write(stream << "at index "
					<< index << ": ") << " with probeCount: "
				<< probeCount[index] << "\n";
	return stream;
}	/* end: Write */
