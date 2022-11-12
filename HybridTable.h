#ifndef HYBRIDTABLE_H_
#define HYBRIDTABLE_H_

#include <string>
using std::string;

class Node {

	int index_;  // index of this node
	int val_;    // value corresponding to this index
	Node* next_; // pointer to next node in the list

	// even constructors are private!
	// so only HybridTable can access them

	// Constructor initialising the node with an index and its
	// corresponding value, with the next_ pointer set to nullptr
	Node(int index, int val);

	// Constructor initialising the node with an index, its
	// corresponding value, and the next node pointer
	Node(int index, int val, Node* next);

	// Destructor
	~Node();

friend class HybridTable; // allow HybridTable to access private members
};

class HybridTable {

public:
	// Constructor. Constructs an empty HybridTable with array part of
	// size INITIAL_ARRAY_SIZE, and empty list part.
	// All entries in the array part initialised to 0.
	HybridTable();

	// Parameterised constructor. Constructs a HybridTable with array
	// part of size n, and an empty list part.
	// arr is assumed to have size n, and the entries in the array part
	// are initialised with arr[0] to arr[n-1].
	HybridTable(const int* arr, int n);

	// Destructor. It should release all memory used by this HybridTable.
	~HybridTable();

	// Copy constructor.
	HybridTable(const HybridTable& other);

	// Copy assignment operator.
	HybridTable& operator=(const HybridTable& other);

	// Returns the value corresponding to index i.
	// If index i is not present in the HybridTable, return 0.
	int get(int i) const;

	// Sets the value corresponding to index i to val.
	// Resizing of the array part, if required, should also happen here.
	void set(int i, int val);

	// Returns a string representation of the HybridTable, as described
	// in the assignment webpage.
	// Note that it does not actually print anything to the screen.
	// To pass the test cases you must make sure that even the
	// white spaces are correct.
	string toString() const;

	// Returns the number of entries of the array part. In other words,
	// the array part indices are [0..getArraySize()-1].
	int getArraySize() const;

	// Returns the total number of elements in the array part and
	// the list part.
	int getTotalSize() const;

	// We didn't explain what static and constexpr are, but you can just
	// use them in HybridTable.cpp just like normal constants
	// DO NOT CHANGE, MOVE OR REMOVE IT
	static constexpr int INITIAL_ARRAY_SIZE = 4; // default array part size

private:

	int* array_; // pointer to array part
	Node* list_; // pointer to head of list part

	// add other member variables if required

    int total_array_size = 0; // To keep track of current array size

	// add other member functions if required

    // Hybrid Table helper functions

    // checks if the index is available in the list and the array
    // replaces the value of it with new value returns true
    // or else return false
    bool findAndReplace(int index, int val);

    // returns a new array size if the array can be expanded
    // or else returns the current array size
    int calcNewArraySize();

    // calculates the new possible array size int powers of 2
    int nextPossibleArraySize(int size);

    // resizes the whole array and the list with the new size
    void resizeArray(int size);

    // Array helper functions

    // initializes array_ and copies the values of other array_ to this array_
    void createAndCopyArray(const int* otherArray, int otherArraySize);


    // Linked List Helper Functions

    // copies the whole list from other hybrid table list
    // Note: do only use to copy values of whole linked list
    void copyWholeList(Node* otherList);

    // returns the total number of elements in the list part
    int getListLength() const;

    // finds a node in the list using index
    Node* getNode(int index) const;

    // inserts a node at the start of the list
    void insertHead(int index, int val);

    // inserts node after the given node
    void insertNodeAfter(Node* location, int index, int val);

    // inserts a node into the list using index
    void insertNodeAtIndex(int index, int val);

    // deletes node after a given node
    void removeNodeAfter(Node* node);

    // deletes the given node
    void removeNode(Node* node);

    // deletes the head node
    void removeHeadNode();

    // finds the previous node of the given node
    Node* findPreviousNode(Node* node);

    // deletes all nodes in the list (kin of a destructor for the whole list)
    void deleteAllNodes();

    // returns the list part as string
    string listAsString() const;


    // General helper function
    float calcPercent(int num1, int num2);

};

#endif /* HYBRIDTABLE_H_ */