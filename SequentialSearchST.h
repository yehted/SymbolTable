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

	int size() { return N_; }

	bool isEmpty() { return N_ == 0; }

	bool contains(Key key) { return get(key) != NULL; }

	Value get(Key key) {
		for (Node* x = first_; x != NULL; x = x->next_)
			if (key == x->key_) return x->val_;
		return NULL;
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
		Node();
		Node(Key key, Value val, Node* next) : key_(key), val_(val), next_(next) {}
	
		Key key_;
		Value val_;
		Node* next_;
	};

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