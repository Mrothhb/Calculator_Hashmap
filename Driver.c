//==========================================================================
// cs12xcm                         Homework 6             Matt Roth 
//
// February 11 2019	
//--------------------------------------------------------------------------
// File: Driver.c
//
// Description:		The Driver is designed to be a runner program for the
//		implementation of the HashTable. The Driver contains a UCSDStudent class
//		and a Driver class which contains main to execute the program. 
//==========================================================================

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <getopt.h>
#include <iostream>
#include "Base.h"
#include "SymTab.h"
using namespace std;

#ifdef NULL
#undef NULL
#define NULL 0
#endif

//=========================================================================
// class UCSDStudent 
//
// Description:		This class will initialize and hold the data for the 
// UCSDStudent, which will be used in the HashTable.
// 
// Data Fields:
//     name (char *)  - name of the student 
//     studentnum (long *)  - student number
//
// Public functions:
//					UCSDStudent - constructor(s) for initialization
//					~UCSDStudent - destructor 
//					operator char * - overload operator for name 
//					operator long - overload operator for hash code 
//					ostream & Write - the to string function 
//==========================================================================
class UCSDStudent : public Base {

	//name of the student and number for student 
	char * name;
	long studentnum;

public:
/***************************************************************************
% Routine Name : UCSDStudent (public)
% File :         Driver.c
% 
% Description :  Constructors that will initialize the name and number
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% nm				the name of the student 
% sn				the student number 	
***************************************************************************/
	UCSDStudent (char * nm, long sn) :
		name (strdup (nm)), studentnum (sn) {}

/***************************************************************************
% Routine Name : ~UCSDStudent (public)
% File :         Driver.c
% 
% Description :  The destructor for UCSDStudent

% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% void.  	
***************************************************************************/
	~UCSDStudent (void) {
		free(name);
	}

/***************************************************************************
% Routine Name : UCSDStudent (public)
% File :         Driver.c
% 
% Description :  Constructors that will initialize the name and number
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% ucsdStu			the UCSDStudent object  	
***************************************************************************/
	UCSDStudent(UCSDStudent & ucsdStu){

		name = strdup (ucsdStu.name);
		studentnum = ucsdStu.studentnum;
	}

/***************************************************************************
% Routine Name : operator char * (public)
% File :         Driver.c
% 
% Description :  overloads the operator for the (char *) type 
%
% Parameters descriptions :
% 
% name               description
% ------------------ -----------------------------------------------------
% name				the name of student  	
***************************************************************************/
	operator char * (void) {
		return name;
	}

/***************************************************************************
% Routine Name : operator long (public)
% File :         Driver.c
% 
% Description :  overload to the equals method 
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% name, base		 the true or false value of equality  	
***************************************************************************/
	operator long (void);
	long operator == (Base & base) {
		return ! strcmp (name, base);
	}

/***************************************************************************
% Routine Name : ostream & Write (public)
% File :         Driver.c
% 
% Description :  The toString method 
%
% Parameters descriptions : 
% 
% name               description
% ------------------ ------------------------------------------------------
% stream			 the stream to output the student name and number 
***************************************************************************/
	ostream & Write (ostream & stream) {
		return stream << "name: " << name
			<< " Studentnum: " << studentnum;
	}

};

/***************************************************************************
% Routine Name : UCSDStudent :: operator (public)
% File :         Driver.c
% 
% Description :  This function will calculate the ASCII SUM on the name 
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% <return>           the sum 
***************************************************************************/
UCSDStudent :: operator long (void) {

	long sum = 0;
	
	for (long index = 0; name[index]; index++)
		sum += name[index];

	return sum;
}

//PROVIDED CODE 
int main (int argc, char * const * argv) {
	SymTab ST (5);
	char buffer[128];
	char command;
	long number;
	char option;

	/* initialize debug variable */
	HashTable::Set_Debug(0);

	 /* check command line options for debug display */
	 while ((option = getopt (argc, argv, "x")) != EOF) {

		 switch (option) {
			 case 'x': HashTable::Set_Debug(1);
				 break;
		 	}
	} 

	ST.Write (cout << "Initial Symbol Table:\n");
	while (cin) {
		command = NULL;	// reset command each time in loop
		cout << "Please enter a command:  ((i)nsert, (l)ookup, (w)rite):  ";
		cin >> command;

		switch (command) {
		case 'i':
			cout << "Please enter UCSD student name to insert:  ";
			cin >> buffer;	// formatted input

			cout << "Please enter UCSD student number:  ";
			cin >> number;

			// create student and place in symbol table
			if(!ST.Insert (new UCSDStudent (buffer, number))){

				ST.Write (cout << "\nFinal Symbol Table:\n");
				exit (0);
			}
			break;

		case 'l': {
			Base * found;	// whether found or not

			cout << "Please enter UCSD student name to lookup:  ";
			cin >> buffer;	// formatted input

			UCSDStudent stu (buffer, 0);
			found = ST.Lookup (& stu);
			
			if (found)
				found->Write (cout << "Student found!!!\n") << "\n";
			else
				cout << "Student " << buffer << " not there!\n";
			}
			break;

		case 'w':
			ST.Write (cout << "The Symbol Table contains:\n");
		}
	}
	ST.Write (cout << "\nFinal Symbol Table:\n");
}

