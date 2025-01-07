#include <iostream.h>
#include <stdlib.h>
#include <conio.h>

// Linked list with all its functionalities

// Class Node
class Node {

public:

    int data;


    Node* prev; // previous pointer


    Node* next; // next pointer


    // Default constructor that initializes both pointer to NULL
    Node() {
        prev = next = NULL;

        cout << "Default constructor in Node class." << endl;
    }


    ~Node() {

        cout << "Default destructor in Node class." << endl;
    }

};



// Class Linked list that will use the Node class
class LinkedList{

private:

    Node* start;



    Node* end;



    int size;


public:

    // Default constructor
    LinkedList();


    // Destructor
    ~LinkedList();




    // Search method with key as parameter and return type Node pointer
    Node* searchOnNode(int key);


    // Add method with node pointer as parameter and void return type
    // Adds a node to the end of list
    void appendNode(Node* element);


    // Add(insert) method with node pointer as parameter and void return type
    // Adds a node at a specific place in the list
    void insertNode(Node* element);



    // Delete method with key as parameter and
    // return type of the data type stored in the list
    int deleteNode(int key);



    // Method to empty the list completely
    void freeList();


    // Method to get the size of the list
    int getSize();


    // Method to check whether the list is empty or not
    int isEmpty();


    // Method to return the first node + remove it.
    // Takes no parameters and returns a node pointer
    Node* getFirst();


    // Method to return the last node + remove it.
    // Takes no parameters and returns a node pointer
    Node* getLast();


    // Method to return the first node WITHOUT removing it.
    // Takes no parameters and returns a node pointer
    Node* peekFirst();


    // Method to return the last node WITHOUT removing it.
    // Takes no parameters and returns a node pointer
    Node* peekLast();

    // Method to print (to be used in main())
	void print();

};



// Implementation of the methods inside class LinkedList

LinkedList::LinkedList() {

    // Initialize an empty list
    start = end = NULL;

    size = 0;

    cout << "Default constructor in LinkedList class." << endl;
}



LinkedList::~LinkedList() {

    cout << "Default destructor in LinkedList class." << endl;
}




Node* LinkedList::searchOnNode(int key) {

    // temp variable used to traverse the list without modifying the start pointer
    /*
        - Why is start assigned to to temp?
            The search starts from the beginning of the list.
    */
    Node* temp = start;



    // Check if the list is empty.
    // If it is, no point in doing the search, so return NULL, meaning 'key not found'
    if (start == NULL) { return NULL;}


    // If list is not empty, start checking every node till you find key
    /*
        - while() has 2 conditions to check:

            * Condition 1: temp is not NULL: if it is NULL, it means we've
                           reached the end of the list

            * Condition 2: temp -> data is not the key we're searching for
                           if the data in the current node is indeed the key,
                           then we return temp, if not, temp is move to the
                           next node
    */
    while ((temp) && (temp -> data != key)) {
            temp = temp -> next;
    }

    return temp;
}



void LinkedList::appendNode(Node* element) {

    // If list is empty, then the element to append is the first and only
    // element that will exist in the list
    if (start == NULL) {

        start = end = element;

    }

    // If list is not empty
    /*
        1. The current end node will be the previous node of the node to be appended.
        2. The element to append will be the next node of the current end node.
        3. The element to append will be the end node.
    */
    else {

        element -> prev = end;

        end -> next = element;

        end = element;
    }

    size++;
}



void LinkedList::insertNode(Node* element) {

    Node* temp = start;


    /*
        - While loop checks for 2 conditions:
            1. temp is not NULL
            2. The data in the in the current temp node is less than
               the data in the node to be added

        - When does it end?
          * when the data in current node is greater than or equal to
          data in node to be added
    */
    while ((temp) && (temp -> data < element -> data)) {

        temp = temp -> next; // if both conditions are true, move to the next node

    }


    // Empty list or the new element has largest data
    /*
        - If temp is NULL, which happens in 2 cases:
           1. List is empty
           2. The while loop has traversed all the nodes, but none had data
              greater than the data of the element to be inserted

         -> result: add the element to the end of list
    */
    if (!temp) {

        appendNode(element);
        return; // added to avoid incrementing size again as insertNode() already does

    }

    // If temp remains pointing to start node
    /*
        If temp is not NULL.
        +
        After the while loop has finished its traversal, the temp is still
        pointing to start node as defined at the start [Node* temp = start].

        -> result: The data of element to be added is smaller than data of the
                   current first node.
    */
    else if (temp == start) {

        start -> prev = element; // prev of current start will point to element to bed added

        element -> next = start; // next of element to be added is current start

        start = element; // element to be added will be the new start of the list
    }
    /*
        - General case: inserting the node between 2 nodes before temp

        - The while loop move temp till it stands at a node whose data is greater
          than the data of element to be added
          while ((temp) && (temp -> data < element -> data))

            * Thus, new node is inserted before temp
    */
    else {

        temp -> prev -> next = element; // next element to temp prev is new element

        element -> prev = temp -> prev; // prev of new element is the prev of temp

        temp -> prev = element; // element will be positioned before temp

        element -> next = temp; // next of new element will be temp
    }

    size++;
}




int LinkedList::deleteNode(int key){

    Node* temp;

    if(!start) {return 0;} // Case 1: start is NULL, then list is empty and no deletion happens


    temp = searchOnNode(key); // to delete a node, we must find it first


    if (!temp) {return 0;} // Case 2: if element is not found, then no deletion happens


    // Case 3: start and end are the same, so list has 1 element
    if (start == temp && end == temp) {

        start = end = NULL; // Make them both NULL
        //free(temp); // Free memory where temp resided
        delete temp;
    }

    // Case 4: element searched (and to be deleted) is the start
    else if (start == temp) {

        start = start -> next; // new start will be the next of current start

        start -> prev = NULL; // prev of new start is NULL since it is first element now

        //free(temp);
        delete temp;
    }

    // Case 5: element searched (and to be deleted) is the end
    else if (end == temp) {

        end = end -> prev; // prev of current end becomes new end

        end -> next = NULL; // next of new end is NULL since it is now last element

       // free(temp);
       delete temp;
    }

    // Case 6: General case: element searched (and to be deleted) is between 2 elements
    else {

        // the next of the prev of current node will point to the next of current node,
        // skipping the current node which will be deleted
        temp -> prev -> next = temp -> next;

        // the prev of the next of current node will point to the prev of current node
        temp -> next -> prev = temp -> prev;

        //free(temp);
        delete temp;
    }

    size--; // if deletion happens, decrement size

	return 1; // return 1 to convey success (true)

}



void LinkedList::freeList(){

    Node* temp = start;


    while (temp) {

        start = start -> next;

        //free(temp);
        delete temp;

        temp = start;
    }

    end = NULL;

    size = 0; // after deleting all elements, size will be 0

    /*
     Or

     while (start) {
        deleteNode(start -> data);
     }
    */

}



int LinkedList::getSize(){

    return size; // simply return size
}



int LinkedList::isEmpty(){

    /*
        If you're to check for end as well, writing it as start == end == NULL
        will give weird behavior. Instead, it should be
    */
	return (start == NULL && end == NULL); // return true when both start and end are NULL
}



Node* LinkedList::getFirst(){

    if (isEmpty()){

        return NULL; // if list is empty, there's no first to get and remove
    }

    // store start in pointer temp so we can return it later
    // and not lose it when it gets deleted
    Node* temp = start;


    start = start -> next; // update start to the next element which now becomes the head


    // check if the new start is not NULL
    // if it were, then it means list had only 1 element and now it's empty
    if (start) {

        start -> prev = NULL; // if indeed something exists, its prev must be NULL

    } else {

        end = NULL; // if new start turns out to be NULL, then end is NULL as well to indicate list is empty
    }

    // temp, which is removed and to be returned is now completely unlinked, both its prev and next are NULL
    temp -> prev = temp -> next = NULL;

    size--; // we get AND remove, so size is decremented

    return temp;

}


// Same logic as getFirst()
Node* LinkedList::getLast(){

    if (isEmpty()) {return NULL;}


    Node* temp = end;


    end = end -> prev;


    if (end) {

        end -> next = NULL;

    } else {

        start = NULL;

    }

    temp -> prev = temp -> next = NULL;

    size--;

    return temp;
}



Node* LinkedList::peekFirst(){

    if (isEmpty()) {return NULL;}

    Node* temp = new Node(); // create a new node that will copy the data of the current start node

    temp -> data = start -> data;

    // the new node has nothing to do with the original list we have
    // it shouldn't have any links whatsoever
    temp -> prev = temp -> next = NULL;

    return temp;

}



Node* LinkedList::peekLast(){

    if (isEmpty()) {return NULL;}


    Node* temp = new Node();


    temp -> data = end -> data;

    temp -> prev = temp -> next = NULL;

    return temp;

}

void LinkedList::print() {

    if (start == NULL) {
        cout << "List is empty." << endl;
        return;
    }

    Node* currentNode = start;


    while (currentNode != NULL) {

		cout << currentNode -> data << "\t";

        currentNode = currentNode -> next;

	}

	cout << endl;

}


LinkedList* getData() {

    int i;
	LinkedList* doubleLinkedList = new LinkedList();

    int size;
    cout << "How many elements do you want in the list? ";
    cin >> size;
    cout << endl;

    for (i = 0; i < size; i++) {
        Node* newNode = new Node();
        cout << "Enter data for Node #" << i+1 << ": ";
        cin >> newNode -> data;
        doubleLinkedList->appendNode(newNode);
        cout << endl;
    }

    return doubleLinkedList;

}




int main() {


	system("cls");

	int i;
	int keyToSearch;
	int keyToAppend;
	int keyToInsert;
	int keyToDelete;


	LinkedList* doubleLinkedList = getData();

	cout << "Elements in double linked list are: " << endl;
	doubleLinkedList->print();
	cout << endl;



	cout << "Trying out all operations on doubleLinkedList..." << endl << endl;


    cout << "Enter data to search for: ";
	cin >> keyToSearch;


    // searchOnNode() returns a pointer to Node
	Node* nodeSearched = doubleLinkedList->searchOnNode(keyToSearch);
	if (nodeSearched) {
		cout << "Node with data " << keyToSearch << " is found." << endl << endl;
	} else {
		cout << "Node with data " << keyToSearch << " doesn't  exist." << endl << endl;
	}


	// Getting size of linked list
	cout << "Size of linked list: " << doubleLinkedList->getSize() << endl << endl;



    // Appending a node to the linked list
    cout << "Enter data to append: ";
	cin >> keyToAppend;
    Node* nodeToAppend = new Node();
    nodeToAppend -> data = keyToAppend;
	doubleLinkedList->appendNode(nodeToAppend);
	cout << "Node appended with data: " << nodeToAppend -> data << endl << endl;


    // Getting size after appending an element
	cout << "Size after appending: " << doubleLinkedList->getSize() << endl;


	getch();


    system("cls");


    cout << "Enter data to insert: ";
	cin >> keyToInsert;
	Node* nodeToInsert = new Node();
	nodeToInsert -> data = keyToInsert;
	doubleLinkedList->insertNode(nodeToInsert);


	cout << "Node inserted with data: " << nodeToInsert->data << endl << endl;


    // Getting size after inserting an element
    cout << "Size after inserting: " << doubleLinkedList->getSize() << endl << endl;



    // Deleting a node
    cout << "Enter data to delete: ";
	cin >> keyToDelete;

	int resultDeletion = doubleLinkedList->deleteNode(keyToDelete);

	if (resultDeletion) {

        cout << "Node with data " << keyToDelete << " successfully deleted." << endl << endl;

	} else {

        cout << "No deletion happened!" << endl << endl;
	}


    // Getting size after deleting an element
    cout << "Size after deleting: " << doubleLinkedList->getSize() << endl << endl;



	// Checking if list is empty
	int isEmpty = doubleLinkedList->isEmpty();
    if (isEmpty) {

        cout << "List is empty." << endl << endl;

	} else {

            // Printing the list so far
            cout << "Elements in double linked list after checking if it's empty are: " << endl;
            doubleLinkedList->print();
            cout << endl;
	}



	// Getting and removing the first element
	Node* firstNode = doubleLinkedList->getFirst();
	if (firstNode) {
        cout << "Here is the first node with data " << firstNode->data << endl << endl;
        delete firstNode;

	}



	// Printing the list after removing the first node
    cout << "Elements in double linked list after removing first node: " << endl;
    doubleLinkedList->print();
    cout << endl;



	// Getting and removing the last element
    Node* lastNode = doubleLinkedList->getLast();
	if (lastNode) {
        cout << "Here is the last node with data " << lastNode->data << endl << endl;
        delete lastNode;

	}


	// Printing the list after removing the last node
    cout << "Elements in double linked list after removing last node: " << endl;
    doubleLinkedList->print();
    cout << endl;

    getch();


    system("cls");

    // Peeking the first node
    Node* firstNodePeeked = doubleLinkedList->peekFirst();
    if (firstNodePeeked) {
        cout << "Here is the first peeked node with data " << firstNodePeeked->data << endl << endl;
        delete firstNodePeeked;

	}


    // Printing the list after peeking the first node
    cout << "Elements in double linked list after peeking first node: " << endl;
    doubleLinkedList->print();
    cout << endl;



    // Peeking the last node
    Node* lastNodePeeked = doubleLinkedList->peekLast();
    if (lastNodePeeked) {
        cout << "Here is the last peeked node with data " << lastNodePeeked->data << endl << endl;
        delete lastNodePeeked;

	}


    // Printing the list after peeking the first node
    cout << "Elements in double linked list after peeking last node: " << endl;
    doubleLinkedList->print();
    cout << endl;


    // Getting the size after removing first and last and peeking
    cout << "Size after removing and peeking: " << doubleLinkedList->getSize() << endl << endl;



	// Freeing the list
	doubleLinkedList->freeList();
	cout << "Elements in double linked list after freeing it are: " << endl;
    doubleLinkedList->print(); // prints "List is empty" according to logic in print()
	cout << endl;


    // Getting the size after freeing the list
    cout << "Size after freeing the list: " << doubleLinkedList->getSize() << endl << endl;


    delete doubleLinkedList;

    getch();
    return 0;
}
