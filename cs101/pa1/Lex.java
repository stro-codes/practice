// Strother Woog
// 1618221
// CMPS 101
// 4/12/19
// Sorts an Array of Strings by InsertSort
// Lex.java

import java.io.*;
import java.util.Scanner;
   
class Lex {
	
	public static void main(String[] args) throws IOException {
		Scanner in = null;
		PrintWriter out = null;
		String line = null;
		int i, n, lineNumber = 0;

		if(args.length < 2){
			System.err.println("Usage: FileIO infile outfile");
			System.exit(1);
		}
		  
		in = new Scanner(new File(args[0]));
		out = new PrintWriter(new FileWriter(args[1]));

		// count number of lines
		while( in.hasNextLine() ){
			line = in.nextLine() + " ";
			lineNumber++;
		}
		
		Scanner in2 = new Scanner(new File(args[0]));
		String[] notes = new String[lineNumber];
		lineNumber = 0;
		
		// add lines to array
		while( in2.hasNextLine() ){
			String temp = in2.nextLine() + " ";
			notes[lineNumber] = temp;
			lineNumber++;			
		}
		
		// initialize list to be sorted
		List sorted = new List();
		sorted.prepend(0);
		sorted.moveFront();
		
		// insertion sort
		for(int j = 1; j < notes.length; j++) {
			String temp = notes[j];
			sorted.moveFront();
			while(sorted.index() < j - 1){
				sorted.moveNext();
			}
			while(notes[sorted.get()].compareTo(temp) > 0) {
				if(sorted.index() != 0)
					sorted.movePrev();
				else if(sorted.index() == 0)
					break;
			}
			if(notes[sorted.get()].compareTo(temp) < 0 ) {
				sorted.insertAfter(j);
			}
			else if(notes[sorted.get()].compareTo(temp) > 0 ) {
				sorted.insertBefore(j);
			}
			else {
				sorted.insertAfter(j);
			}
			sorted.moveBack();
		}
		
		// print string values of sorted list
		sorted.moveFront();
		while(sorted.index() < sorted.length() && sorted.index() != -1) {
			out.println(notes[sorted.get()]);
			if(sorted.index() != sorted.length() - 1)
				sorted.moveNext();
			else	
				sorted.delete();
		}
		out.println();
		
		// close sc
		in.close();
		in2.close();
		out.close();
		
		// testing	
		
	}
}