// Strother Woog
// 1618221
// CMPS 101
// 5/9/19
// List ADT for a Doubly Linked List that stores Objects
// List.java

class List {

	private class Node {
		// Fields
		Object data;
		Node next;
		Node prev;
      
		// Constructor
		Node(Object data) { 
			this.data = data; 
			next = prev = null; 
		}
      
		// toString():  overrides Object's toString() method
		public String toString() { 
			return "" + this.data; 
		}
      
		// equals(): overrides Object's equals() method
		public boolean equals(Object x){
			boolean eq = false;
			Node that;
			if(x instanceof Node){
				that = (Node) x;
				eq = (this.data.equals(that.data));
			}
			return eq;
		}
	}

	// Fields
	private Node front;
	private Node back;
	private int length;
	private int cursor;

	// Constructor
	List() { 
		front = back = null; 
		length = 0; 
		cursor = -1;
	}

	// Access Functions --------------------------------------------------------

	// isEmpty()
	// Returns true if this List is empty, false otherwise.
	boolean isEmpty() { 
		return length == 0; 
	}

	int length() { 
		return length; 
	}
	
	int index() {
		if (cursor > -1 )//&& cursor > this.length())	
			return cursor;
		else
			return -1;
	}
	
	Object front() {
		if( this.isEmpty() ) {
			throw new RuntimeException(
				"List Error: front() called on empty List");
		}
		return front.data;
	}
	
	Object back() {
		if( this.isEmpty() ) {
			throw new RuntimeException(
				"List Error: back() called on empty List");
		}
		return back.data;
	}
	
	Object get() {
		if( this.index() == -1 || this.length() == 0 ) {
			throw new RuntimeException(
				"List Error: get() called on empty List");
		}
		else {
			int x = 0;
			Node n = front;
			while(x < this.index()) {
				x++;
				n = n.next;
			}
			return n.data;
		}
	}
	
	// Manipulation Procedures -------------------------------------------------

	void clear() {
		front = back = null; 
		length = 0; 
		cursor = -1;
	}
	
	void moveFront() {
		if( this.isEmpty() ) {
			throw new RuntimeException(
				"List Error: moveFront() called on empty List");
		}
		else {
			this.cursor = 0;
		}
	}
	
	void moveBack() {
		if( this.isEmpty() ) {
			throw new RuntimeException(
				"List Error: moveBack() called on empty List");
		}
		else {
			this.cursor = this.length() - 1;
		}
	}
	
	void movePrev() {
		if (this.index() == -1) {
			throw new RuntimeException(
				"List Error: movePrev() called on undefined cursor");
		}
		else {
			if(this.index() == 0) {
				cursor = -1;
			}
			else {
				cursor--;
			}
		}
	}
	
	void moveNext() {
		if (this.index() == -1) {
			throw new RuntimeException(
			"List Error: moveNext() called on undefined cursor");
		}
		else {
			if(this.index() == this.length - 1) {
				cursor = -1;
			}
			else {
				cursor++;
			}
		}
	}
	
	void prepend(Object data) {
		Node N = new Node(data);
		if( this.isEmpty() ) { 
			front = back = N;
		}
		else { 
			N.next = front; 
			front.prev = N; 
			front = N;
		}
		length++;
		if(cursor != -1)
			cursor++;
	}
   
	void append(Object data) {
		Node N = new Node(data);
		if( this.isEmpty() ) { 
			front = back = N;
		}
		else { 
			N.prev = back;
			back.next = N;
			back = N;
		}
		length++;
	}
	
	void insertBefore(Object data) {
		if( this.isEmpty() || this.index() < 0) {
			throw new RuntimeException(
            "List Error: Dequeue() called on empty List");
		}
		else {
			if(this.index() == 0) {
				this.prepend(data);
			}
			else {
				Node n = new Node(data);
				int x = 0;
				Node m = front;
				while(x < this.index()) {
					x++;
					m = m.next;
				}
				n.prev = m.prev;
				m.prev = n;
				n.next = m;
				n.prev.next = n;
				length++;
				cursor++;
			}
		}
	}
	
	void insertAfter(Object data) {
		if( this.isEmpty() || this.index() < 0) {
			throw new RuntimeException(
            "List Error: Dequeue() called on empty List");
		}
		else {
			if(this.index() == this.length() - 1) {
				this.append(data);
			}
			else {
				Node n = new Node(data);
				int x = 0;
				Node m = front;
				while(x < this.index()) {
					x++;
					m = m.next;
				}
				n.next = m.next;
				m.next = n;
				n.prev = m;
				n.next.prev = n;
				length++;
			}
		}
	}
	
	void deleteFront() {
		if( this.isEmpty() ) {
			throw new RuntimeException(
            "List Error: deleteFront() called on empty List");
		}
		if(this.length > 1) {
			front = front.next;
			front.prev = null;
			length--;
			if(cursor >= 0)
				cursor--;
		}
		else {
			this.clear();
		}
	}
   
	void deleteBack() {
		if( this.isEmpty() ) {
			throw new RuntimeException(
            "List Error: deleteBack() called on empty List");
		}
		if(this.length > 1) {
			back = back.prev;
			back.next = null;
			length--;
			if(cursor == length)
				cursor = -1;
		}
		else {
			this.clear();
		}
	}

	void delete() {
		if( this.isEmpty() || this.index() < 0) {
			throw new RuntimeException(
            "List Error: delete() called on undefined index");
		}
		if(this.length() < 1) {
			this.clear();
		}
		else if(this.index() == 0) {
			this.deleteFront();
		}
		else if(this.index() == this.length() - 1) {
			this.deleteBack();
		}
		else {
			Node n = front;
			int x = 0;
			while(x < this.index() - 1) {
				n = n.next;
				x++;
			}
			n.next = n.next.next;
			n.next.prev = n;
			
			length--;
			cursor--;
		}
	}

	// Other Functions ---------------------------------------------------------

	// toString()
	// Overides Object's toString() method.
    public String toString() {
		String sb = "";
		Node N = front;
		while(N != null) {
			sb = sb + " ";
			sb = sb + N.toString();
			N = N.next;
		}
		return sb;
	}

	// equals()
	// Overrides Object's equals() method.  Returns true if x is a List storing
	// the same integer sequence as this List, false otherwise.
	public boolean equals(Object x) {
		boolean eq  = false;
		List L;
		Node N, M;

		if(x instanceof List){
			L = (List)x;
			N = this.front;
			M = L.front;
			eq = (this.length == L.length);
			while(eq && N != null ) { 
				eq = N.equals(M);
				N = N.next;
				M = M.next;
			}
		}
		return eq;
	}
	
}
