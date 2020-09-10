/****************************************************************************

Matthew Roth, A15685519
CSE 12, Winter 2019
February 11, 2019
cs12xcm
Assignment 6

File Name:      Driver.java
Description:    The Driver is designed to be a runner program for the
*		implementation of the HashTable. The Driver contains a UCSDStudent class
*		and a Driver class which contains main to execute the program. 
***************************************************************************/

import java.io.EOFException;

/**
 * The UCSDStudent class will extend the Base abstract class
 * and inherit all the declared methods and data public fields.
 * This class is designed to create a student object that will
 * contain a name as a string, and a student number as long.
 * The hashcode for calculating the sum of the ASCII codes
 * for the name will be contained in this class as a void
 * function call. 
 */ 
class UCSDStudent extends Base {
	
	//the name and the student number 
	private String name;
	private long Studentnum;

	/**
	 * constructor taking a String and a long 
	 * as a name and a student number respectively
	 *
	 * @param nm the student name 
	 * @param stuNum the student number 
	 */ 
	public UCSDStudent(String nm, long stuNum){
		this.name = new String(nm);
		this.Studentnum = stuNum;
	}
	
	/**
	 * the copy constructor 
	 *
	 * @param ucsdStu the UCSDStudent obj
	 */
	public UCSDStudent(UCSDStudent ucsdStu){
		
		//set this name to the incoming parameter
		this.name = new String(ucsdStu.name);
		//set this student number to the incoming param
		this.Studentnum = ucsdStu.Studentnum;

	}
	/**
	 * this method will return the name 
	 * of the UCSDStudent 
	 */
	public String getName(){

		return name;
	}
	
	/**
	 * the equals method will compare two objects 
	 * of the UCSDStudent type to check for 
	 * equality.
	 *
	 * @param the object to check 
	 * @return true or false 
	 */
	public boolean equals  (Object other){
		
		//check this object with the parameter 
		if(this == other){
			return true;
		}
		
		//using instanceof for casting pre check 
		if(!(other instanceof UCSDStudent)){
			return false;
		}	
		//cast to a UCSDStudent to return to caller
		UCSDStudent otherStu = (UCSDStudent)other;

		return name.equals (otherStu.getName());
	}
	
	/**
	 * the to string method the return a 
	 * String representation of the student name
	 * and number
	 * @return name and number 
	 */
	public String toString () {

		return "name: " + name + " Studentnum: " + Studentnum;
	}

	/**
	 * this method will calculate the ASCII sum 
	 * of the name.
	 *
	 * @return retval the ascii sum
	 */
	public int hashCode () {

		//local variables to hold the return value and index
		int retval = 0;
		int index = 0;
		
		//get each char in the string and add to the sum 
		while (index != name.length ()) {
			retval += name.charAt (index);
			index ++;
		}

		return retval;
	}
	
	/**
	 * This method will assign a student 
	 * number.
	 *
	 * @param val the student number
	 * @return retval the number of student
	 */ 
	public UCSDStudent assign (long val) {

		UCSDStudent retval;        // return value

		// give variable its value
		this.Studentnum = val;
		retval = new UCSDStudent(this);

		return retval;
	}

}

/**
 *	PROVIDED CODE
 */
public class Driver {

	public static void main (String [] args) {

		/* initialize debug states */
		HashTable.debugOff();

		/* check command line options */
		for (int index = 0; index < args.length; ++index) {
			if (args[index].equals("-x"))
				HashTable.debugOn();
		}

		/* The real start of the code */
		SymTab symtab = new SymTab (5);
		String buffer = null;
		char command;
		long number = 0;

		System.out.print ("Initial Symbol Table:\n" + symtab);

		while (true) {
			command = 0;    // reset command each time in loop
			System.out.print ("Please enter a command:  "
					+ "((i)nsert, (l)ookup, (w)rite):  ");

			try {
				command = MyLib.getchar ();
				MyLib.clrbuf (command); // get rid of return

				switch (command) {
					case 'i':
						System.out.print (
								"Please enter UCSD Student name to insert:  ");
						buffer = MyLib.getline ();// formatted input

						System.out.print (
								"Please enter UCSD Student number:  ");

						number = MyLib.decin ();
						MyLib.clrbuf (command); // get rid of return

						// create Student and place in symbol table
						if(!symtab.insert (
									new UCSDStudent (buffer, number), 1)){

							System.out.println("Couldn't insert " + 
									"student!!!"); 
						}
						break;

					case 'l': {
								  Base found;     // whether found or not

								  System.out.print (
										  "Please enter UCSD Student name to lookup:  ");

								  buffer = MyLib.getline ();// formatted input

								  UCSDStudent stu = new UCSDStudent (buffer, 0);
								  found = symtab.lookup (stu);

								  if (found != null) {
									  System.out.println ("Student found!!!");
									  System.out.println (found);
								  }
								  else
									  System.out.println ("Student " + buffer
											  + " not there!");
							  }
							  break;

					case 'w':
							  System.out.print (
									  "The Symbol Table contains:\n" + symtab);
						
				}
			}
			catch (EOFException eof) {
				break;
			}
		}

		System.out.print ("\nFinal Symbol Table:\n" + symtab);
	}
}
