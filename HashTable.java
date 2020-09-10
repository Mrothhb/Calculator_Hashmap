/****************************************************************************

Matthew Roth, A15685519
CSE 12, Winter 2019
February 11, 2019
cs12xcm
Assignment 6

File Name:      HashTable.java
Description:    The HashTable class is a HashTable data structure implementation
*			memory will be allocated to an array which will hold the elements
*			of the table as 'Base' objects. Each Base object will contsain a
*			student name and number. The table will use a hashing alogrithm
*			to efficiently store and retreive data on the objects being 
*			stored in the table. The element requested will be located
*			and replaced, and if not found it will take an empty spot on
*			the table, or bump an object that has a lower search record. 
*			If the table is full the item will not be inserted, and an
*			error message will be returned. 
***************************************************************************/

/**
 *	The HashTable class is a HashTable data structure implementation.
 *	memory will be allocated to an array which will hold the elements
 *	of the table as 'Base' objects. Each Base object will contsain a
 *	student name and number. The table will use a hashing alogrithm
 *	to efficiently store and retreive data on the objects being 
 *	stored in the table. The element requested will be located
 *	and replaced, and if not found it will take an empty spot on
 *	the table, or bump an object that has a lower search record. 
 *	If the table is full the item will not be inserted, and an
 *	error message will be returned. 
 *
 * */
public class HashTable extends Base {

	private static int counter = 0;	// number of HashTables so far
	private static boolean debug;        // allocation of debug state

	// set in locate, last location checked in hash table 
	private int index = 0; 

	// set in insert/lookup, count of location in probe sequence
	private int count = 0;

	private int probeCount[];   // where we are in the probe sequence 
	private long occupancy;     // how many elements are in the Hash Table
	private int size;           // size of Hash Table
	private Base table[];       // the Hash Table itself ==> array of Base
	private int tableCount;     // which hash table it is

	// messages
	private static final String AND = " and ";
	private static final String DEBUG_ALLOCATE = " - Allocated]\n";
	private static final String DEBUG_LOCATE = " - Locate]\n";
	private static final String DEBUG_LOOKUP = " - Lookup]\n";
	private static final String BUMP = "[Bumping To Next Location...]\n";
	private static final String COMPARE = " - Comparing ";
	private static final String FOUND_SPOT = " - Found Empty Spot]\n";
	private static final String HASH = "[Hash Table ";
	private static final String HASH_VAL = "[Hash Value Is ";
	private static final String INSERT = " - Inserting ";
	private static final String PROCESSING = "[Processing ";
	private static final String TRYING = "[Trying Index ";


    /**
	 * This method will turn on debug
	 *
	 */
	public static void debugOn () {

		debug = true;

	}

	/**
	 * This method will turn off debug
	 *
	 **/
	public static void debugOff () {

		debug = false;
	}

	/**
	 * This method allocates and initializes the memory
	 * associated with a hash table.
	 *
	 * @param  sz   The number of elements for the table...MUST BE PRIME!!!
	 */
	public HashTable (int sz) {
		
		//global counter for HashTable count
		this.counter++;

		if(debug){
			System.err.print(HASH + this.counter + DEBUG_ALLOCATE);
		}

		//initialize the data fields for HashTable//
		this.size = sz;
		this.occupancy = 0;
		this.tableCount++;

		//Set the size of the arrays// 
		table = new Base[size];
		probeCount = new int[size];

		//initialize the table array and probe array to null values//
		for(int i =0; i<table.length; i++){
			table[i] = null;
			probeCount[i] = 0;
		}
	}


	/**
	 * This method will insert the element in the hash table.
	 * If the element cannot be inserted, false will be returned.
	 * If the element can be inserted, the element is inserted
	 * and true is returned.  Duplicate insertions will
	 * cause thefull list is existing element to be deleted, and the duplicate
	 * element to take its place.
	 *
	 * @param   element       The element to insert.
	 * @param   initialCount  Where to start in probe seq (recursive calls) 
	 * @return  true or false indicating success or failure of insertion
	 */
	public boolean insert (Base element, int initialCount) {
		
		//set the count to the parameter 
		this.count = initialCount;
	
		//old probeCount temp placeholder for bump
		int oldProbeCount = 0;
		
		//holder for the bumped element
		Base bump;

		if(debug){
			System.err.println(HASH + this.tableCount + INSERT
					+ element.getName() + "]");
		}
		
		//if full table 
		if(this.occupancy >= this.size){

			System.err.println("The table is full!");
			return false;

		}
		
		//if the element is found in table
		if(locate(element)){
			probeCount[index] = count;
			//insert the parameter element into the index
			table[index] = element;
			return true;
		}
		
		//if the table index is null
		if(table[index] == null){

			if(debug){

				System.err.println(HASH + tableCount + FOUND_SPOT);
			}
			//set the probecount to match with index
			probeCount[index] = count;
			//insert the element into the empty spot
			table[index] = element;
			//increase the occupancy 
			this.occupancy++;

			return true;
		//the index is occupied with another element 	
		}else{ 

			System.err.println(BUMP);	
			
			//bump the element from the table 
			bump = table[index];
			
			//track the probe count 
			oldProbeCount = probeCount[index];
			
			//insert the parameter element 
			table[index] = element;
	
			//reset the probe count 
			probeCount[index] = count;
			
			//recursive call to insert with bumped element 
			insert(bump, ++oldProbeCount);
		}

		return true;
	}

	/**
	 * This method will locate the location in the
	 * table for the insert or lookup.
	 *
	 * @param   element  The element needing a location.
	 * @return  true if item found, or false if not found
	 */
	private boolean locate (Base element) {

		//initialized local variable for locate hash//
		int ASCII_SUM = element.hashCode();
		int TABLE_SIZE = this.size;
		int INC_MOD = 4;
		int BY_ONE = 1;
		int initLocation = 0;
		int increment = 0;
		int currentIndex = 0;

		if(debug){

			System.err.println(HASH + tableCount + DEBUG_LOCATE);
			System.err.println(PROCESSING + element.getName() + "]");
			System.err.println(HASH_VAL + ASCII_SUM + "]");
		}

		//check for null parameter
		if(element == null){

			System.err.println("Error - Null element");
			return false;
		}
		
		//get the initial location from ASCII SUM and size 
		initLocation = ASCII_SUM % TABLE_SIZE;
		
		//increment the index
		increment = (ASCII_SUM % (TABLE_SIZE - BY_ONE))+ BY_ONE;
		
		//reset the current index
		currentIndex = (initLocation + (count-BY_ONE)*increment)% TABLE_SIZE;
		
		//check the table for parameter element 
		for(int i = 0; i<TABLE_SIZE; i++){

			this.index = currentIndex;

			if(debug){
				System.err.println(TRYING + currentIndex + "]");
			}
			
			//if the index is empty 
			if(table[currentIndex] == null){

				return false;
			}
			
			//if the index contains the parameter element 
			if(table[currentIndex].equals(element)){

				return true;
			}

			if(debug){

				System.err.println(HASH + tableCount + COMPARE 
						+ element.getName() +
						AND + table[currentIndex].getName() + "]");
			}
			
			//if the containing index has a less than probe count 
			if(this.probeCount[currentIndex] < count){

				return false;
			}

			//set the new current index to the incremented mod value//
			currentIndex = (currentIndex + increment) % TABLE_SIZE;
			++count;

		}

		//if the table is full
		return false;
	}

	/**
	 * This method will lookup the element in the hash table.  If
	 * found a pointer to the element is returned.  If the element
	 * is not found, NULL will be returned to the user.
	 *
	 * @param   element  The element to look up.
	 * @return  A pointer to the element if found, else NULL
	 */
	public Base lookup (Base element) {
		
		//reset the count to one 
		this.count = 1;

		if(debug){
			System.err.println(HASH + counter + DEBUG_LOOKUP);
		}
		
		//if the element is at thb index 
		if(locate(element)){

			return table[index];
		}

		return null;
	}

	/**
	 * Creates a string representation of the hash table. The method 
	 * traverses the entire table, adding elements one by one ordered
	 * according to their index in the table. 
	 *
	 * @return  String representation of hash table
	 */
	public String toString () {
		String string = "Hash Table " + tableCount + ":\n";
		string += "size is " + size + " elements, "; 
		string += "occupancy is " + occupancy + " elements.\n";

		/* go through all table elements */
		for (int index = 0; index < size; index++) {

			if (table[index] != null) {
				string += "at index " + index + ": ";
				string += "" + table[index];
				string += " with probeCount: "; 
				string += probeCount[index] + "\n";
			}
		}

		return string;
	}
}
