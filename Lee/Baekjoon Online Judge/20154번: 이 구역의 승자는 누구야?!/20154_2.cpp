#include <cstddef>
#include <cstdint>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <array>
#include <vector>
#include <string>
#include <iostream>

inline auto map(char c)
{
	static constexpr std::array<std::uint_fast32_t, 26> numbers = {
		3, 2, 1, 2, 3, 3, 3, 3, 1, 1, 3, 1, 3,
		3, 1, 2, 2, 2, 1, 2, 1, 1, 2, 2, 2, 1
	};

	return numbers[static_cast<std::size_t>(c - 'A')];
}

int main()
{
	std::string line;
	std::getline(std::cin, line);

	std::vector<unsigned short int> scoreboard;
	scoreboard.reserve(line.length());

	std::transform(
		std::cbegin(line),
		std::cend(line),
		std::back_inserter(scoreboard),
		map
	);

	const auto sum = std::reduce(
		std::cbegin(scoreboard),
		std::cend(scoreboard),
		std::uint_fast32_t{}
	);

	if (sum % 2 == 1)
		std::cout << "I'm a winner!\n";
	else
		std::cout << "You're the winner?\n";

	return 0;
}
