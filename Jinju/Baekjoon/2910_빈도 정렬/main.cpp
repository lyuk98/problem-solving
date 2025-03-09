#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


int N, C;

struct Node {
	int value;
	int first;
	int count;

	// Members are initialized in the order of declaration,
	// not in the order in the constructor
	// In this case, `value` is initialized first, then `first` and `count` follows
	Node(int v = 0, int c = 0, int f = 0 ) : value(v), first(f), count(c) {}
};

// Referring to the following code:
/*
struct A {
    int i;
    int j;
    A() : j(0), i(j) {}
};
*/
// `i` is initialized first, which copies the value of `j`,
// but `j` was not initialized at this point so it copies the garbage data

int main() {
	map<int, Node> valueCount;

	cin >> N >> C;

	for (int i = 0; i < N; i++) {
		int value;
		cin >> value;
		if (valueCount.find(value) != valueCount.end()) {
			valueCount[value].count++;
		}
		else {
			valueCount[value] = Node(value, 1, i);
		}
	}

	vector<Node> hing;
	for (const auto& [key, node] : valueCount) {
		hing.push_back(node);
	}

	sort(hing.begin(), hing.end(), [](const Node& a, const Node& b) {
		if (a.count != b.count)
			return a.count > b.count;
		return a.first < b.first;
	});

	for (const auto& node : hing) {
		for (int i = 0; i < node.count; i++) {
			cout << node.value << " ";
		}
	}
}