/**********************************************************************
* The SequentialSearchST class represents an (unordered) symbol table
* of generic key-value pairs.
* It supports the usual put, get, contains, delete, size, and is-empty
* methods. It also provides a keys method for iterating over all of the keys.
* A symbol table implements the associative array abstraction: when 
* associating a value with a key that is already in the symbol table, the
* convention is to replace the old value with the new value.
* Values are allowed to be 0 in this implementation.
*
* This implementation uses a singly-linked list and sequential search. It
* relies on the equals() method to test whether two keys are equal. It does 
* not call either the compareTo() or hashCode() method.
* The put and delete operatiosn take linear time; the get and contains 
* operations takes linear time in the worst case. The size and is-empty
* operations take constant time. Construction takes constant time.
*
* For additional documentation, see Section 3.1 of Algorithms, 4th edition,
* by Robert Sedgewick and Kevin Wayne
*************************************************************************/
#ifndef SEQUENTIALSEARCHST_H
#define SEQUENTIALSEARCHST_H

#include <Bag\Bag\Bag.h>

template <class Key, class Value>
class SequentialSearchST {
public:
	SequentialSearchST() : first_(NULL), N_(0) {}

	~SequentialSearchST() {
		Node* current = first_;
		while (current != NULL) {
			first_ = first_->next_;
			delete current;
			current = first_;
		}
	}

	SequentialSearchST(const SequentialSearchST& other) : N_(other.N_) {
		Node* current = other.first_;
		Node* temp = NULL;
		while (current != NULL) {
			Node* node = new Node(current->key_, current->val_, NULL);
			if (temp == NULL)
				first_ = node;
			else
				temp->next_ = node;
			temp = node;
			current = current->next_;
		}
	}

	SequentialSearchST& operator=(const SequentialSearchST& other) {
		if (&other == this) return *this;
		
		// Free existing memory
		Node* current = first_;
		while (first_ != NULL) {
			current = first_->next_;
			delete first_;
			first_ = current;
		}

		// Allocate new memory and copy elements
		N_ = 0;
		current = other.first_;
		Node* temp = NULL;
		while (current != NULL) {
			Node* node = new Node(current->key_, current->val_, NULL);
			if (temp == NULL)
				first_ = node;
			else
				temp->next_ = node;
			temp = node;
			current = current->next_;
			N_++;
		}

		if (N_ != other.N_) printf("Copying error\n");
		return *this;
	}

	int size() { return N_; }

	bool isEmpty() { return N_ == 0; }

	bool contains(Key key) { return find(key) != NULL; }

	Value get(Key key) {
		Node* x = find(key);
		if (x == NULL) throw std::out_of_range("Key not found");
		return x->val_;
	}

	void put(Key key, Value val) {
//		if (val == NULL) { erase(key); return; }
		for (Node* x = first_; x != NULL; x = x->next_) {
			if (key == x->key_) {
				x->val_ = val;
				return;
			}
		}
		first_ = new Node(key, val, first_);
		N_++;
	}

	void erase(Key key) {
		first_ = erase(first_, key);
	}

	Bag<Key> keys() {
		Bag<Key> bag;
		for (Node* x = first_; x != NULL; x = x->next_)
			bag.add(x->key_);
		return bag;
	}

private:
	class Node {
	public:
		Node() {}
		Node(Key key, Value val, Node* next) : key_(key), val_(val), next_(next) {}
	
		Key key_;
		Value val_;
		Node* next_;
	};

	Node* find(Key key) {
		for (Node* x = first_; x != NULL; x = x->next_)
			if (key == x->key_) return x;
		return NULL;
	}

	Node* erase(Node* x, Key key) {
		if (x == NULL) return NULL;
		if (key == x->key_) { N_--; return x->next_; }
		x->next_ = erase(x->next_, key);
		return x;
	}

	int N_;
	Node* first_;
};
#endif // !SEQUENTIALSEARCHST_H