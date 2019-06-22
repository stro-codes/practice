// Strother Woog
// 1618221
// CMPS 101
// 5/9/19
// Sparse Program to handle input/output of files for making and manipulating Matricies
// Sparse.java

import java.io.*;
import java.util.Scanner;

class Sparse {
	
	public static void main(String[] args) throws IOException {
	
		Matrix A = null;
		Matrix B = null;
		Scanner in = null;
		PrintWriter out = null;
		int i = 0; 
		int n = 0;
		int a = 0;
		int b = 0;

		if(args.length < 2){
			System.err.println("Usage: FileIO infile outfile");
			System.exit(1);
		}
		  
		in = new Scanner(new File(args[0]));
		out = new PrintWriter(new FileWriter(args[1]));

		// count number of lines
		while(in.hasNext()) {
			if(i == 0) {
				n = in.nextInt();
				a = in.nextInt();
				b = in.nextInt();
				System.out.println(n + " " + a + " " + b);
				A = new Matrix(n);
				B = new Matrix(n);
			}
			else if(i > 1) {
				if(i < a + 2) {
					int row = in.nextInt();
					int col = in.nextInt();
					Double data = in.nextDouble();
					System.out.println(row + " " + col + " " +data);
					A.changeEntry(row, col, data);						
				}
				else if(i > a + 2) {
					int row = in.nextInt();
					int col = in.nextInt();
					Double data = in.nextDouble();
					System.out.println("B : " + row + " " + col + " " +data);
					B.changeEntry(row, col, data);
				}
			}
			i++;
		}
		
		// write to out file
		out.println("A has " + A.getNNZ() + " non-zero entries: ");
		out.println(A);
		out.println();
		
		out.println("B has " + B.getNNZ() + " non-zero entries: ");
		out.println(B);
		out.println();
		
		out.println("(1.5)*A = ");
		out.println(A.scalarMult(1.5));
		out.println();
		
		out.println("A+B = ");
		out.println(A.add(B));
		out.println();
		
		out.println("A+A = ");
		out.println(A.add(A));
		out.println();
		
		out.println("B-A = ");
		out.println(B.sub(A));
		out.println();
		
		out.println("A-A = ");
		out.println(A.sub(A));
		out.println();
		
		out.println("Transpose(A) = ");
		out.println(A.transpose());
		out.println();
		
		out.println("A*B = ");
		out.println(A.mult(B));
		out.println();
		
		out.println("B*B = ");
		out.println(B.mult(B));
		out.println();
		
		in.close();
		out.close();
	}
	
}