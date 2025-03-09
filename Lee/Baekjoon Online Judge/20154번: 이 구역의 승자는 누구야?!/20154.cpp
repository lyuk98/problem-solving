#include <cstddef>
#include <iterator>
#include <algorithm>
#include <array>
#include <vector>
#include <string>
#include <iostream>

auto map(char c)
{
	static constexpr std::array<unsigned short int, 26> numbers = {
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

	while (scoreboard.size() > 1)
	{
		std::size_t in = 0;
		for (std::size_t i = 0; i + 1 < scoreboard.size(); i += 2)
		{
			scoreboard[in++] = (scoreboard[i] + scoreboard[i + 1]) % 10;
		}
		if (scoreboard.size() % 2 == 1)
		{
			scoreboard[in++] = scoreboard.back();
		}

		scoreboard.erase(
			std::next(std::begin(scoreboard), in),
			std::end(scoreboard)
		);
	}

	if (scoreboard.front() % 2 == 1)
	{
		std::cout << "I'm a winner!\n";
	}
	else
	{
		std::cout << "You're the winner?\n";
	}

	return 0;
}
