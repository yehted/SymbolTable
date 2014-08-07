#include "SequentialSearchST.h"
#include <Deque\Deque\Deque.h>

template <class Key, class Value>
class SeparateChainingHashST {
public:
	SeparateChainingHashST() : SeparateChainingHashST(INIT_CAPACITY) {}
	
	SeparateChainingHashST(int M) : M_(M), st_(new SequentialSearchST<Key, Value>[M]) {}

	void resize(int chains) {
		SeparateChainingHashST temp(chains);
		for (int i = 0; i < M_; i++) {
			for (Key key : st_[i].keys()) {
				temp.put(key, st_[i].get(key));
			}
		}
		M_ = temp.M_;
		N_ = temp.N_;
		st_ = temp.st_;
	}

	int size() { return N_; }

	bool isEmpty() { return N_ == 0; }

	bool contains(Key key) { return get(key) != NULL; }

	Value get(Key key) {
		int i = hash(key);
		return st_[i].get(key);
	}

	void put(Key key, Value val) {
		if (val == NULL) { erase(key); return; }

		// double table size if average length of list >= 10
		if (N_ >= 10 * M_) resize(2 * M_);

		int i = hash(key);
		if (!st_[i].contains(key)) N_++;
		st_[i].put(key, val);

		
	}

	void erase(Key key) {
		int i = hash(key);
		if (st_[i].contains(key)) N--;
		st_[i].erase(key);

		// halve table size if average length of list <= 2
		if (M_ > INIT_CAPACITY && N_ <= 2 * M_) resize(M_ / 2);
	}

	Deque<Key> keys() {
		Deque<Key> deque;
		for (int i = 0; i < M_; i++) {
			for (Key key : st_[i].keys())
				deque.addLast(key);
		}
		return deque;
	}

private:
	int hash(Key key) {
		
	}

	static const int INIT_CAPACITY = 4;
	int N_;									// number of key-value pairs
	int M_;									// hash table size
	SequentialSearchST<Key, Value>* st_;		// array of unordered_map symbol tables
};