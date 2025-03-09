#include <cstddef>
#include <cstdint>
#include <tuple>
#include <iterator>
#include <ranges>
#include <algorithm>
#include <vector>
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::ptrdiff_t n;
	std::vector<std::int_fast32_t> a;

	std::cin >> n;
	[[assume(n >= 1 && n <= 2'000)]];

	a.reserve(n);
	std::copy_n(
		std::istream_iterator<decltype(a)::value_type>(std::cin),
		n,
		std::back_inserter(a)
	);
	std::ranges::sort(a);

	std::uint_fast16_t good {};

	for(auto const [i, value] : a | std::views::enumerate | std::views::as_const)
	{
		[[assume(value <= 1'000'000'000)]];

		auto const begin = a | std::views::enumerate | std::views::as_const;
		auto const end = a | std::views::enumerate | std::views::reverse | std::views::as_const;

		auto first = std::ranges::cbegin(begin);
		auto last = std::ranges::cbegin(end);

		while(std::get<0>(*first) < std::get<0>(*last))
		{
			if(std::get<0>(*first) == i)
			{
				++first;
				continue;
			}
			if(std::get<0>(*last) == i)
			{
				++last;
				continue;
			}

			[[assume(std::get<1>(*first) <= 1'000'000'000)]];
			[[assume(std::get<1>(*last) <= 1'000'000'000)]];

			const auto cmp = (std::get<1>(*first) + std::get<1>(*last)) <=> value;
			if(cmp == 0)
			{
				++good;
				break;
			}
			else if(cmp < 0) ++first;
			else ++last;
		}
	}

	std::println(std::cout, "{}", good);

	return 0;
}
