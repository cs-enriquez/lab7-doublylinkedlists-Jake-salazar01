	#include "StudentList.h"

	// Define a constructor to initialize the list. The list starts with no Students
    StudentList::StudentList() {
		head = nullptr;
		tail = nullptr;
		numStudents = 0;
	}

	// return the number of students currently in the list
	int StudentList::listSize() {
		return numStudents;
	}

	//add a Node with a student to the front (head) of the list.
	void StudentList::addFront(Student s) {
		if (numStudents == 0){
			head = new Node(s);
			tail = head;
			numStudents++;
			return;
		}
		head -> prev = new Node(s);
		head -> prev -> prev = nullptr;
		head -> prev -> next = head;
		head = head -> prev;
		numStudents++;
		
	}

	//add a Node with a student to the back (tail) of the list.
	void StudentList::addBack(Student s) {
		if(numStudents == 0){
			tail = new Node(s);
			head = tail;
			numStudents++;
			return;
		}
		tail -> next = new Node(s);
		tail -> next -> next = nullptr;
		tail -> next -> prev = tail;
		tail = tail -> next;
		numStudents++;
		
	}

	//Print out the names of each student in the list.
	void StudentList::printList() {
		Node* point = head;
    while (point != nullptr) {
        cout << point->data.name << endl;
        point = point->next;
    }
	}

	// Remove the Node with the student at the back (tail) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popBack() {
		if(numStudents == 0){
        	cout << "ERROR" << endl;
        	return; 
    	}
    	Node *point7 = tail;
    	tail = tail->prev;
    	delete point7;
    	if (tail == nullptr){
        	head = nullptr;
    	}
		else{
        	tail->next = nullptr;
    	}
    	numStudents--;
	}

	// Remove the Node with the student at the front (head) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popFront() {
		if(numStudents == 0){
        	cout << "EMPTY" << endl;
        	return;
    	}
    	Node *point8 = head;
    	head = head->next;
    	delete point8;

    	if (head == nullptr){
        	tail = nullptr;
    	}
		else{
        	head->prev = nullptr;
		}
	}

	//insert a student at the position "index".
	// for this list, count head as index 0
	// if index is outside of current list range, 
	// print a message and insert the student at the back of the list
	// the previous Node at your target index should be moved forward. "For exampe, Node with student at index i, becomes index i+1" 
	// Remember that you already have methods that can add students to the front or back of list if needed! Don't repeat this code.
	void StudentList::insertStudent(Student s, int index) {
		 if(index >= numStudents){
        	cout << "can't put student!" << endl;
        	addBack(s);
        	return;
    	} 
		else if (index == 0){
        	addFront(s);
        	return;
    	}
    	Node *newNode = new Node(s);
    	Node *point2 = head;
    	for(int i = 0; i < index; i++){
        	point2 = point2->next;
    	}
    	newNode->prev = point2->prev;
    	newNode->next = point2;
    	if(point2->prev != nullptr){
        	point2->prev->next = newNode;
    	}
    	point2->prev = newNode;
    	if(newNode->prev == nullptr){
        	head = newNode;
    	}
    	numStudents++;
	}

	//find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idNum) {
		if(numStudents == 0){
			Student fixthis;
			return fixthis;
		}
		Node *point4 = head;
		while(point4 -> next != nullptr){
			if(point4 ->data.id == idNum){
				return point4->data;
			}
			point4 = point4 -> next;
		}
		if (point4 ->data.id == idNum){
			return point4 -> data;
		}

		Student fixthis;
		return fixthis;
	}

	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
	void StudentList::removeStudentById(int idNum){
		if(numStudents == 0){
        	cout << "nothing to remove!" << endl;
        	return;
    	}
    	Node *point5 = head;
    	while(point5 != nullptr){
        	if(point5->data.id == idNum){
            	if (point5 == head){
                	popFront();
                	return;
            	}
				else if (point5 == tail){
                	popBack();
                	return;
            	}
				else{
                	point5->prev->next = point5->next;
                	point5->next->prev = point5->prev;
                	delete point5;
                	numStudents--;
                	return;
            	}
        	}
        	point5 = point5->next;
    	}
    	cout << "Found Nothing" << endl;
	}

	//Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idNum, float newGPA) {
		Node *point6 = head;
		while(point6 != nullptr){
			if(point6 -> data.id == idNum){
				point6->data.GPA = newGPA;
			}
			point6 = point6 -> next;
		}
	}

	//Add all students from otherList to this list.
	//otherlist should be empty after this operation.
	/*
	For example, if the list has 3 students:
	s1 <-> s2 <-> s3
	and otherList has 2 students
	s4 <-> s5
	then after mergeList the currently list should have all 5 students
	s1 <-> s2 <-> s3 <-> s4 <-> s5
	and otherList should be empty and have zero students.
	*/
	void StudentList::mergeList(StudentList &otherList) {
		if(otherList.head == nullptr){
			cout << "Nothing " << endl;
			return;
		}
		if(head == nullptr){
			head = otherList.head;
			tail = otherList.tail;
		}
		else{
			tail->next = otherList.head;
			otherList.head->prev = tail;
			tail = otherList.tail;
		}
		numStudents += otherList.numStudents;
		otherList.head = nullptr;
		otherList.tail = nullptr;
		otherList.numStudents = 0;
	}

	//create a StudentList of students whose gpa is at least minGPA.
	//Return this list.  The original (current) list should
	//not be modified (do not remove the students from the original list).
	StudentList StudentList::honorRoll(float minGPA) {
		StudentList Max;
		Node * currentHead = head;
		while(currentHead != nullptr){
			if(currentHead->data.GPA >= minGPA){
				Max.addBack(currentHead->data);
			}
			currentHead = currentHead->next;
		}
		return Max;
	}