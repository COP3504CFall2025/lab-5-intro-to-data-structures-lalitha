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
		for(size_t i = 0; i < getCount; i++) {
			cout << current->data << endl;
			current = current->next;
		}
	}
	void printReverse() const {
		Node* current = tail;
		for(size_t i = 0; i < getCount; i++) {
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
	void AddHead(const T& data) {
		//allocate data
		Node* newNode = new Node*;
		newNode->data = data;

		//new node points to old head
		newNode->next = head;

		//head points ot ts
		head = newNode;

		//update count
		count++;
	}
	void AddTail(const T& data) {
		Node* newNode = new Node*;
		newNode->data = data;

		newNode->prev = tail;

		tail = newNode;

		count++;
	}

	// Removal
	bool RemoveHead() {
		if(head = nullptr) {
			return false;
		}
		
		//w code
		Node* old = head;
		head = head->next;
		delete *old;
		old = nullptr;

		return true;

	}

	bool RemoveTail() {
		if(tail = nullptr) {
			return false;
		}
		
		//w code
		Node* old = tail;
		tail = tail->prev;
		delete *old;
		old = nullptr;

		return true;
	}
	void Clear() {
		while(count =! 0) {
			removeHead();
			count--;
		}
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if(this == &other) return *this;

		Node* temp = other.getHead();
		while(temp){
			addTail(other->data);
			temp = temp.next;
		}

		count = rhs->count;

		other.clear();

		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {

		if(this == &rhs) return *this;

		Node* temp = rhs.getHead();
		while(temp){
			addTail(rhs->data);
			temp = temp.next;
		}

		count = rhs->count;

		return *this;
	}

	// Construction/Destruction
	LinkedList() {
		head = new Node*;
		tail = new Node*;
		count = 0;

		head->next = tail;
		head->prev = nullptr;
		tail->prev = head;
		tail->next = nullptr;
	};

	LinkedList(const LinkedList<T>& list) {
		head = new Node*;
		tail = new Node*;
		tail = list->tail;		
		count = list->count;			
	}
	LinkedList(LinkedList<T>&& other) noexcept {
		head = list->head;
		tail = list->tail;	
		count = list->count;

		other->head = nullptr;
		other->tail	 = nullptr;
		other->count = 0;
	}
	~LinkedList() {
		while (getCount() > 0) removeHead();
		delete head;
		delete tail;
	};

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};