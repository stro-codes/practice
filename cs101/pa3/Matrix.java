// Strother Woog
// 1618221
// CMPS 101
// 5/9/19
// Matrix ADT for Non-Zero Entries
// Matrix.java

class Matrix {

	private class Entry {
		
		// Fields
		double data;
		int column;
      
		// Constructor
		Entry(int column, double data) { 
			this.data = data; 
			this.column = column;
		}
      
		// toString():  overrides Object's toString() method
		public String toString() { 
			return "(" + this.column + ", " + this.data + ")"; 
		}
      
		// equals(): overrides Object's equals() method
		public boolean equals(Object x){
			boolean eq = false;
			Entry that;
			if(x instanceof Entry){
				that = (Entry) x;
				if(this.column == that.column)
					eq = (this.data == that.data);
			}
			return eq;
		}
	}

	// Fields
	int n;
	List[] array;
	
	// Constructor
	Matrix(int n) {
		if(n >= 1) {
			this.n = n;
			this.array = new List[n];
			for(int x = 0; x < n; x++) {
				this.array[x] = new List();
			}
		}
	}
	// Makes a new n x n zero Matrix. pre: n>=1

	// Access functions
	
	int getSize() {
		return this.n;
	}
	// Returns n, the number of rows and columns of this Matrix
	
	int getNNZ() {
		int result = 0;
		for(int x = 0; x < getSize(); x++) {
			result += array[x].length();
		}
		return result;
	}
	// Returns the number of non-zero entries in this Matrix
	
	public boolean equals(Object x) {	
		boolean eq  = false;
		Matrix M;
		List N, L;

		if(x instanceof Matrix){
			M = (Matrix) x;
			if(this.getSize() == M.getSize() && this.getNNZ() == M.getNNZ()) {				
				for(int i = 0; i < M.getSize(); i++) {
					N = this.array[i];
					L = M.array[i];
					if(N.equals(L)) {
						eq = true;
					}
					else {
						eq = false;
						break;
					}
				}
			}	
		}
		return eq;
	}
	// overrides Object's equals() method
	
	// Manipulation procedures
	
	
	void makeZero() {	
		for(int x = 0; x < this.getSize(); x++) {
			this.array[x].clear();
		}
	}
	// sets this Matrix to the zero state
	
	Matrix copy() {
		Matrix result = new Matrix(this.getSize());
		for(int x = 0; x < this.getSize(); x++) {
			List L = this.array[x];
			if(L.length() != 0)
				L.moveFront();
			while(L.index() != -1) {
				Entry E = (Entry) L.get();
				result.array[x].append(new Entry(E.column, E.data));
				L.moveNext();
			}
		}
		return result;
	}
	// returns a new Matrix having the same entries as this Matrix
	
	void changeEntry(int i, int j, double data) {
		if(  !(( 1 <= i && i <= this.getSize() ) && ( 1 <= j && j <= this.getSize() )) ) {
			throw new RuntimeException(
				"Matrix Error: add() called on mismatched Matrix size");
		}
		else {
			List L = this.array[i - 1];
			Entry E = new Entry(j, data);
			if(L.isEmpty()) {
				if(E.data != 0.0)
					L.prepend(E);
			}
			else {
				L.moveFront();
				while(L.index() != -1) {
					Entry F = (Entry) L.get(); 
					if(E.column == F.column) {
						if(E.data == 0.0)
							L.delete();
						else
							F.data = E.data;
						break;
					}
					else if(E.column < F.column) {
						if(E.data != 0.0)
							L.insertBefore(E);
						break;
					}
					else {
						L.moveNext();
					}
				}
				if(L.length() != 0) {
					Entry F = (Entry) L.back();
					if(E.column > F.column) {
						if(E.data != 0.0)
							L.append(E);
					}
				}
			}
		}
	}		
	// changes ith row, jth column of this Matrix to x
	// pre: 1<=i<=getSize(), 1<=j<=getSize()
	
	Matrix scalarMult(double x) {	
		Matrix result = new Matrix(this.getSize());
		for(int y = 0; y < this.getSize(); y++) {
			List L = this.array[y];
			if(L.length() != 0)
				L.moveFront();
			while(L.index() != -1) {
				Entry E = (Entry) L.get();
				Entry F = new Entry(E.column, E.data * x);
				result.array[y].append(F);
				L.moveNext();
			}
		}
		return result;
	}
	// returns a new Matrix that is the scalar product of this Matrix with x
	
	Matrix add(Matrix M) {
		// check if same size
		if(getSize() != M.getSize()) {
			throw new RuntimeException(
				"Matrix Error: add() called on mismatched Matrix size");
		}
		// M + M = 2M
		else if(this.equals(M)) {
			return (M.copy()).scalarMult(2.0);
		}
		// M - M = 0
		else if(this.equals(M.scalarMult(-1.0))) {
			return new Matrix(M.getSize());
		}
		// A + B
		else {
			Matrix result = new Matrix(this.getSize());
			for(int x = 0; x < this.getSize(); x++) {
				List L = this.array[x];
				List N = M.array[x];
				List temp = new List();
				// Check List length
				if(L.length() != 0)
					L.moveFront();
				// Add elements from A to new Matrix
				for(int y = 0; y < L.length(); y++) {
					Entry E = (Entry) L.get();
					temp.append(new Entry(E.column, E.data));
					if(y != L.length() - 1)
						L.moveNext();
				}
				// Check List length
				if(N.length() != 0)
					N.moveFront();
				if(temp.length() != 0)
					temp.moveFront();				
				// Add data from B to new Matrix
				for(int y = 0; y < N.length(); y++) {
					Entry E = (Entry) N.get();
					if(temp.index() != -1) {
						Entry F = (Entry) temp.get();
						if(E.column == F.column) {
							F.data = E.data + F.data;
							if(F.data == 0.0) {
								temp.delete();
								N.moveNext();
							}
							else {
								temp.moveNext();
								N.moveNext();
							}
						}
						else if(E.column < F.column) {
							temp.insertBefore(E);
							N.moveNext();
						}
						else {
							temp.moveNext();
							y--;
						}
					}
					else {
						temp.append(new Entry(E.column, E.data));
						N.moveNext();
					}
				}
				result.array[x] = temp;
			}
			return result;
		}
	}
	//*/
	// returns a new Matrix that is the sum of this Matrix with M
	// pre: getSize()==M.getSize()
	
	Matrix sub(Matrix M) {
		// prereq error check
		if( getSize() != M.getSize() ) {
			throw new RuntimeException(
				"Matrix Error: add() called on mismatched Matrix size");
		}
		// M - M = 0
		else if(this.equals(M)) {
			return new Matrix(M.getSize());
		}
		// A - B
		else {
			Matrix result = new Matrix(this.getSize());
			for(int x = 0; x < this.getSize(); x++) {
				List L = this.array[x];
				List N = M.array[x];
				List temp = new List();
				
				if(L.length() != 0)
					L.moveFront();

				for(int y = 0; y < L.length(); y++) {
					Entry E = (Entry) L.get();
					temp.append(new Entry(E.column, E.data));
					if(y != L.length() - 1)
						L.moveNext();
				}
				
				if(N.length() != 0)
					N.moveFront();
				if(temp.length() != 0)
					temp.moveFront();				
				
				for(int y = 0; y < N.length(); y++) {
					Entry E = (Entry) N.get();
					if(temp.index() != -1) {
						Entry F = (Entry) temp.get();
						if(E.column == F.column) {
							F.data = F.data - E.data;
							if(F.data == 0.0) {
								temp.delete();
								N.moveNext();
								if(temp.index() == -1 && temp.length() != 0)
									temp.moveFront();
							}
							else {
								temp.moveNext();
								N.moveNext();
							}
						}
						else if(E.column < F.column) {
							temp.insertBefore(new Entry(E.column, -1*E.data));
							N.moveNext();
						}
						else {
							temp.moveNext();
							y--;
						}
					}
					else {
						temp.append(new Entry(E.column, -1*E.data));
						N.moveNext();
					}
				}
				
				result.array[x] = temp;
			}
			return result;
		}
	}
	// returns a new Matrix that is the difference of this Matrix with M
	// pre: getSize()==M.getSize()
	
	Matrix transpose() {
			Matrix result = new Matrix(this.getSize());
			for(int x = 0; x < this.getSize(); x++) {
				List L = this.array[x];
				if(L.length() != 0)
					L.moveFront();
				while(L.index() != -1) {
					Entry E = (Entry) L.get();
					result.array[E.column - 1].append(new Entry(x + 1, E.data));
					L.moveNext();
				}
			}
			return result;
	}
	// returns a new Matrix that is the transpose of this Matrix
	
	 double dot(List L, List R) {
		double result = 0.0;
		if(L.length() == 0 || R.length() == 0)
			return 0.0;
		else {
			if(L.length() != 0)
				L.moveFront();
			if(R.length() != 0)
				R.moveFront();
			while(L.index() != -1 && R.index() != -1) {
				Entry E = (Entry) L.get();
				Entry F = (Entry) R.get();
				if(E.column == F.column) {
					result = result + (E.data * F.data);
					L.moveNext();
					R.moveNext();
				}
				else if(E.column < F.column) {
					L.moveNext();
				}
				else {
					R.moveNext();
				}
			}
		}
		return result;
	}
	
	Matrix mult(Matrix M) {
		if( getSize() != M.getSize() ) {
			throw new RuntimeException(
				"Matrix Error: add() called on mismatched Matrix size");
		}
		else {
			Matrix result = new Matrix(M.getSize());
			Matrix tran = M.transpose();
			for(int x = 0; x < M.getSize(); x++) {
				List L = this.array[x];
				for(int y = 0; y < M.getSize(); y++) {
					List R = tran.array[y];
					if(dot(L, R) != 0.0) {
						result.array[x].append(new Entry(y + 1 , dot(L, R)));
					}
				}
			}
			return result;
		}
	}
	// returns a new Matrix that is the product of this Matrix with M
	// pre: getSize()==M.getSize()

	// Other functions
	
	public String toString() {
		String result = "";
		for(int x = 0; x < this.n; x++) {
			if(this.array[x].length() > 0)
				result = result + (x + 1) + ":" + this.array[x] + "\n";
		}
		return result;
	}
	// overrides Object's toString() method

}