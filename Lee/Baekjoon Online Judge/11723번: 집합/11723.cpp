#include <cstddef>
#include <functional>
#include <ranges>
#include <algorithm>
#include <bitset>
#include <string>
#include <iostream>

template<std::ranges::input_range range_t>
constexpr auto sum(range_t&& range)
{
	using char_type = std::ranges::range_value_t<decltype(range)>;
	using int_type = typename std::char_traits<char_type>::int_type;

	return std::ranges::fold_left(
		range | std::views::transform(std::char_traits<char_type>::to_int_type),
		int_type{},
		std::plus{}
	);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::bitset<21> s;
	std::size_t m;

	std::cin >> m;
	[[assume(m >= 1 && m <= 3'000'000)]];

	for(auto throwaway : std::views::repeat(char{}, m))
	{
		std::string operation;
		std::size_t i;

		std::cin >> operation;

		switch(sum(operation))
		{
		case sum("add"):
			std::cin >> i;
			s.set(i);
			break;

		case sum("remove"):
			std::cin >> i;
			s.reset(i);
			break;

		case sum("check"):
			std::cin >> i;
			std::println(std::cout, "{}", s[i] ? '1' : '0');
			break;

		case sum("toggle"):
			std::cin >> i;
			s.flip(i);
			break;

		case sum("all"):
			s.set();
			break;

		case sum("empty"):
			s.reset();
			break;
		}
	}

	return 0;
}
