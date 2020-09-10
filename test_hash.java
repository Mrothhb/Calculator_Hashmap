import java.io.EOFException;
import java.util.Arrays;
import java.lang.Object.*;
import java.util.Random;


/**
 * Private class for setting up the UCSDStudent object
 */
class UCSDStudent extends Base {
  private String name;
  private long Studentnum;

  /**
   * Creates a string representation of the object
   *
   * @return a string of the name and number
   */
  public String toString() {

    return "name: " + name + " Studentnum: " + Studentnum;
  }

  /**
   * Getter method for the name of the student
   *
   * @return the name
   */
  public String getName() {

    return this.name;
  }

  /**
   * Getter method for the number of the student
   *
   * @return the student's number
   */
  public long getStudentNum() {

    return this.Studentnum;
  }

  /**
   * Constructor. Two arguments
   *
   * @param name the name of the new student
   * @param Studentnum the number of the new student
   */
  public UCSDStudent(String name, long Studentnum) {

    this.name = new String(name);
    this.Studentnum = Studentnum;
  }

  /**
   * Constructor. Copy constructor using an existing student.
   *
   * @param student the pre-existing student
   */
  public UCSDStudent(UCSDStudent student) {

    this.name = new String(student.getName());
    this.Studentnum = student.getStudentNum();
  }

  /**
   * Checks for equality between students
   *
   * @param object object to compary
   * @return true or false
   */
  public boolean equals(Object object) {

    if(this == object) {

      return true;
    }

    if(object instanceof UCSDStudent) {

      // Cast object to a student type
      UCSDStudent otherStudent = (UCSDStudent)object;

      return name.equals(otherStudent.getName());
    }

    return false;
  }

  /**
   * Creates a hashcode of the object passed in
   *
   * @return a hashcode value
   */
  public int hashCode() {

    int returnVal = 0; // Return value
    int index = 0; // Used in while loop

    while(index != getName().length()) {

      returnVal += getName().charAt(index);
      index++;
    }

    return returnVal;
  }
}

public class test_hash {

  public static void main(String[] args) {

    HashTable.debugOff();

    /* check command line options */
    for(int index = 0; index < args.length; ++index) {

      if(args[index].equals("-x"))

        HashTable.debugOn();
    }

    /* The real start of the code */
    SymTab symtab = new SymTab(23321);
    String buffer = null;
    char command;
    long number = 0;

    System.out.print("Initial Symbol Table:\n" + symtab);

    String saltStr = "";
    for(int i = 0; i < 20000; i++) {

      String SALTCHARS = "abcdefghijk";
      StringBuilder salt = new StringBuilder();
      Random rnd = new Random();

      while(salt.length() < 5) { // length of the random string.

        int index = (int)(rnd.nextFloat() * SALTCHARS.length());
        salt.append(SALTCHARS.charAt(index));
      }

      saltStr = salt.toString();
      symtab.insert((new UCSDStudent(saltStr, 1)), 1);
    }

    while (true) {

      command = 0; // reset command each time in loop
      System.out.print("Please enter a command: ((l)ookup, (w)rite): ");

      try {

        command = MyLib.getchar();
        MyLib.clrbuf(command); // get rid of return

        switch(command) {

          case 'l': {

            Base found; // whether found or not

            System.out.print("Please enter UCSD Student name to lookup:  ");

            buffer = MyLib.getline();// formatted input

            UCSDStudent stu = new UCSDStudent(buffer, 0);
            found = symtab.lookup(stu);

            if(found != null) {

              System.out.println("Student found!!!");
              System.out.println(found);
            } else {

              System.out.println("Student " + buffer + " not there!");
            }

            break;
          }

          case 'w':

            System.out.print("The Symbol Table contains:\n" + symtab);
        }
      } catch(EOFException eof) {

        break;
      }
    }
  }
}
