#include "SequentialSearchST.h"
#include <iostream>
#include <string>

int main(int argc, char* arvg[]) {
	SequentialSearchST<std::string, int> st;
	std::string s;
	int N;
	std::cout << "Number of keys: ";
	std::cin >> N;
	for (int i = 0; i < N; i++) {
		std::cin >> s;
		st.put(s, i);
	}
	for (std::string k : st.keys())
		std::cout << k << " " << st.get(k) << std::endl;

	return 0;
}