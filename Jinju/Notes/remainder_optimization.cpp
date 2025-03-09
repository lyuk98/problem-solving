#include <utility>
#include <array>
#include <iostream>
using namespace std;

int main()
{
	cout << boolalpha;

	// Perhaps (just a little) faster way to calculate
	// if a number is divisible by another number

	// Examples
	array<pair<int, int>, 3> examples = {
		make_pair(9, 3),
		make_pair(17, 3),
		make_pair(256, 8)
	};

	for(size_t i = 0; i < examples.size(); ++i) {
		const auto& a = examples[i].first;
		const auto& b = examples[i].second;

		// 1: Using % operator
		{
			cout << i + 1 << "-1: Is " << a << " divisible by " << b << "? - ";
			cout << (a % b == 0) << '\n';
		}

		// 2: Dividing and multiplying again
		{
			cout << i + 1 << "-2: Is " << a << " divisible by " << b << "? - ";
			cout << ((a / b * b) == a) << '\n';
		}
	}

	return 0;
}
