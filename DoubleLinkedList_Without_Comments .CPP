#include <iostream.h>
#include <stdlib.h>
#include <conio.h>

// Linked list with all its functionalities

// Class Node
class Node {

public:

    int data;


    Node* prev;


    Node* next;



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


    LinkedList();



    ~LinkedList();



    Node* searchOnNode(int key);



    void appendNode(Node* element);



    void insertNode(Node* element);




    int deleteNode(int key);



    void freeList();



    int getSize();


    int isEmpty();



    Node* getFirst();



    Node* getLast();



    Node* peekFirst();



    Node* peekLast();


	void print();

};





LinkedList::LinkedList() {

    start = end = NULL;

    size = 0;

    cout << "Default constructor in LinkedList class." << endl;
}



LinkedList::~LinkedList() {

    cout << "Default destructor in LinkedList class." << endl;
}




Node* LinkedList::searchOnNode(int key) {


    Node* temp = start;



    if (start == NULL) { return NULL;}



    while ((temp) && (temp -> data != key)) {
            temp = temp -> next;
    }

    return temp;
}



void LinkedList::appendNode(Node* element) {


    if (start == NULL) {

        start = end = element;

    }

    else {

        element -> prev = end;

        end -> next = element;

        end = element;
    }

    size++;
}



void LinkedList::insertNode(Node* element) {

    Node* temp = start;



    while ((temp) && (temp -> data < element -> data)) {

        temp = temp -> next;

    }


    if (!temp) {

        appendNode(element);
        return;

    }


    else if (temp == start) {

        start -> prev = element;

        element -> next = start;

        start = element;
    }

    else {

        temp -> prev -> next = element;

        element -> prev = temp -> prev;

        temp -> prev = element;

        element -> next = temp;
    }

    size++;
}




int LinkedList::deleteNode(int key){

    Node* temp;

    if(!start) {return 0;}


    temp = searchOnNode(key);


    if (!temp) {return 0;}



    if (start == temp && end == temp) {

        start = end = NULL;
        delete temp;
    }

    else if (start == temp) {

        start = start -> next;

        start -> prev = NULL;

        delete temp;
    }


    else if (end == temp) {

        end = end -> prev;

        end -> next = NULL;

       delete temp;
    }

    else {


        temp -> prev -> next = temp -> next;

        temp -> next -> prev = temp -> prev;

        delete temp;
    }

    size--;

	return 1;

}



void LinkedList::freeList(){

    Node* temp = start;


    while (temp) {

        start = start -> next;

        delete temp;

        temp = start;
    }

    end = NULL;

    size = 0;

}



int LinkedList::getSize(){

    return size;
}



int LinkedList::isEmpty(){


	return (start == NULL && end == NULL);



Node* LinkedList::getFirst(){

    if (isEmpty()){

        return NULL;
    }


    Node* temp = start;


    start = start -> next;



    if (start) {

        start -> prev = NULL;

    } else {

        end = NULL;
    }


    temp -> prev = temp -> next = NULL;

    size--;

    return temp;

}


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

    Node* temp = new Node();

    temp -> data = start -> data;


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
