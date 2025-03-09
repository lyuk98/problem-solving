#include <functional>
#include <vector>
#include <queue>
#include <algorithm>

// Custom compare type returning
// if left-hand side is greater than right-hand side
template<typename T>
struct my_greater {
	bool operator()(const T& lhs, const T& rhs) {
		return lhs > rhs;
	}
};

// Custom compare function returning lhs < rhs
constexpr bool cmp(int lhs, int rhs) {
	return lhs > rhs;
}

int main() {
	// Initialize priority_queue with default settings,
	// using compare type provided by the standard library
	std::priority_queue<int/*, std::vector<int>, std::less<int>*/> max_heap;

	// Initialize priority_queue with default container and custom compare type
	std::priority_queue<int, std::vector<int>, my_greater<int>> min_heap;

	// Initialize a vector with numbers
	std::vector<int> ints {1, 2, 3, 4, 5};

	// Sort the numbers in increasing order
	std::sort(
		ints.begin(),
		ints.end()
	);

	// Sort the numbers in decreasing order by using a custom function
	std::sort(
		ints.begin(),
		ints.end(),
		cmp
	);

	// Sort the numbers in decreasing order by using a lambda function
	std::sort(
		ints.begin(),
		ints.end(),
		[](int lhs, int rhs) {
			return lhs > rhs;
		}
	);

	// Sort the numbers in increasing order
	// by using an instance of a compare type from the standard library
	std::sort(
		ints.begin(),
		ints.end(),
		std::less<int>{}
	);

	// Sort the numbers in decreasing order
	// by using an instance of a custom compare type
	std::sort(
		ints.begin(),
		ints.end(),
		my_greater<int>{}
	);

	return 0;
}
