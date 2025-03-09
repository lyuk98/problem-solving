#include <cstddef>
#include <iterator>
#include <algorithm>
#include <array>
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::array<char, 8> sequence = {
		'1', '2', '3', '4', '5', '6', '7', '8'
	};

	std::ptrdiff_t n;
	std::cin >> n;
	const auto end = std::next(sequence.begin(), n);

	auto it = std::ostream_iterator<char>(std::cout, " ");

	do {
		std::copy(sequence.begin(), end, it);
		std::cout.put('\n');
	} while(std::next_permutation(sequence.begin(), end));

	return 0;
}
