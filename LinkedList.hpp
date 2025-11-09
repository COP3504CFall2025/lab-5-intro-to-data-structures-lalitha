#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
	
	struct Node {
		T data;
		Node* prev;
		Node* next;
	};

public:
	// Behaviors
	void printForward() const {
		Node* current = head;
		for(size_t i = 0; i < getCount(); i++) {
			cout << current->data << endl;
			current = current->next;
		}
	}
	void printReverse() const {
		Node* current = tail;
		for(size_t i = 0; i < getCount(); i++) {
			cout << current->data << endl;
			current = current->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}
	Node* getHead() {
		return head;
	}
	const Node* getHead() const {
		return head;
	}
	Node* getTail() {
		return tail;
	}
	const Node* getTail() const {
		return tail;
	}

	// Insertion
	void addHead(const T& data) {
		//allocate data
		Node* newNode = new Node;
		newNode->data = data;

		//new node points to old head
		newNode->next = head;
		newNode->prev = nullptr;

		//head points ot ts
		head = newNode;

		//update count
		count++;
	}
	void addTail(const T& data) {
		Node* newNode = new Node;
		newNode->data = data;

		newNode->prev = tail;
		newNode->next = nullptr;

		tail = newNode;

		count++;
	}


	// Removal
	bool removeHead() {
		if(head == nullptr || count == 1) {
			return false;
		}

		count--;
		
		//w code
		Node* old = head;
		head = head->next;
		head->prev = nullptr;
		delete old;
		old = nullptr;

		return true;

	}

	bool removeTail() {
		if(tail == nullptr || count == 1) {
			return false;
		}

		count--;
		
		//w code
		Node* old = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete old;
		old = nullptr;

		return true;
	}
	void clear() {
		while(count =! 0) {
			removeHead();
			count--;
		}
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		//ts points to other shit
		if(this == &other) return *this;

		head = other.head;
		tail = other.tail;
		count = other.count;

		other.clear();

		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		//makes a copy
		if(this == &rhs) return *this;

		//temp 
		Node* temp = rhs.head;
		if(head) {
			addHead(temp->data);
		}
		while(temp){
			addTail(rhs.data);
			temp = temp->next;
		}

		count = rhs.count;

		return *this;
	}

	// Construction/Destruction
	LinkedList() {
		count = 0;
		head = nullptr;
		tail = nullptr;
	};

	LinkedList(const LinkedList<T>& list) {
		head = list.head;		
		count = list.count;
		
		Node* temp = head;
		while(temp) {
			addTail(list.data);
			temp = temp->next;
		}

		count = list.count;
	}
	LinkedList(LinkedList<T>&& other) noexcept {
		head = other.head;
		tail = other.tail;	
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList() {
		while (getCount() > 0) {
			removeHead();
			count--;
		}
		delete head;
		delete tail;
	};

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;
};