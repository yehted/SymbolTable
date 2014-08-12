#ifndef SEPARATECHAININGHASHST_H
#define SEPARATECHAININGHASHST_H

#include "SequentialSearchST.h"
#include <Deque\Deque\Deque.h>
#include <functional>

template <class Key, class Value>
class SeparateChainingHashST {
public:
	SeparateChainingHashST() : SeparateChainingHashST(INIT_CAPACITY) {}
	
	SeparateChainingHashST(int M) : N_(0), M_(M), st_(new SequentialSearchST<Key, Value>[M]) {}

	~SeparateChainingHashST() {
		printf("Deleting SeparateChainingHashST\n");
		delete[] st_;
	}

	SeparateChainingHashST(const SeparateChainingHashST& other) : N_(other.N_), M_(other.M_), st_(new SequentialSearchST<Key, Value>[other.M_]) {
		printf("Copying SeparateChainingHashST\n");
		for (int i = 0; i < M_; i++)
			st_[i] = other.st_[i];
	}

	SeparateChainingHashST& operator=(const SeparateChainingHashST& other) {
		printf("Assigning SeparateChainingHashST\n");
		if (&other == this) return *this;
		delete[] st_;
		SequentialSearchST<Key, Value>* temp = new SequentialSearchST<Key, Value>[other.M_];
		for (int i = 0; i < M_; i++)
			temp[i] = other.st_[i];

		M_ = other.M_;
		N_ = other.N_;
		st_ = temp;
		return *this;
	}

	void resize(int chains) {
		printf("Resizing hash ST\n");
	//	SeparateChainingHashST<Key, Value>* temp = new SeparateChainingHashST<Key, Value>(chains);
		SequentialSearchST<Key, Value>* temp = new SequentialSearchST<Key, Value>[chains];
		for (int i = 0; i < M_; i++) {
			for (Key key : st_[i].keys()) {
	//			temp->put(key, st_[i].get(key));
				int x = hash(key, chains);
				int y = hash(key, M_);
				temp[x].put(key, st_[y].get(key));
			}
		}
		delete[] st_;
		M_ = chains;
		st_ = temp;
	}

	int size() { return N_; }

	bool isEmpty() { return N_ == 0; }

	bool contains(Key key) { 
		int i = hash(key, M_);
		return st_[i].contains(key);
	}

	Value get(Key key) {
		int i = hash(key, M_);
		return st_[i].get(key);
	}

	void put(Key key, Value val) {
//		if (val == NULL) { erase(key); return; }

		// double table size if average length of list >= 10
		if (N_ >= 10 * M_) resize(2 * M_);

		int i = hash(key, M_);
		if (!st_[i].contains(key)) N_++;
		st_[i].put(key, val);		
	}

	void erase(Key key) {
		int i = hash(key);
		if (st_[i].contains(key)) N_--;
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
	int hash(Key key, int M) {
		std::hash<Key> h;
		return (h(key) & 0x7fffffff) % M;
	}

	static const int INIT_CAPACITY = 4;
	int N_;										// number of key-value pairs
	int M_;										// hash table size
	SequentialSearchST<Key, Value>* st_;		// array of unordered_map symbol tables
};
#endif // !SEPARATECHAININGHASHST_H