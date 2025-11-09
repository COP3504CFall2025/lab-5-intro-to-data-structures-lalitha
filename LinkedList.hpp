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
		Node* newNode = new Node{data, nullptr, head};

		//check null
		if(head != nullptr) {
			head->prev = newNode; //head poiint at ts
			head = newNode;
		} else { //empty
			head = newNode;
			tail = newNode;
		}

		//update count
		count++;
	}
	void addTail(const T& data) {
		Node* newNode = new Node{data, tail, nullptr};

		if(tail != nullptr) {
			tail->next = newNode; //head poiint at ts
			tail = newNode;
		} else { //empty
			head = newNode;
			tail = newNode;
		}

		count++;
	}


	// Removal
	bool removeHead() {
		if(head == nullptr) {
			return false;
		} else if(count == 1) {
			head = nullptr;
			tail = nullptr;
			count = 0;
		}

		count--;
		
		//w code
		Node* old = head;
		head = head->next;
		head->prev = nullptr;
		delete old;

		return true;

	}

	bool removeTail() {
		if(tail == nullptr) {
			return false;
		} else if(count == 1) {
			head = nullptr;
			tail = nullptr;
			count = 0;
		}

		count--;
		
		//w code
		Node* old = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete old;

		return true;
	}
	void clear() {
		while(count != 0) {
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
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;

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
			addTail(temp->data);
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
			addTail(temp->data);
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
		clear();
		delete head;
		delete tail;
	};

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;
};