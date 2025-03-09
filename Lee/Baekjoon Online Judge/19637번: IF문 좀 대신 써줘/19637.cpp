#include <cstddef>
#include <cstdint>
#include <iterator>
#include <ranges>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

struct skill
{
	std::uint_fast32_t power;
	std::string name;
};

constexpr auto operator==(const skill& s1, const skill& s2)
{
	return s1.power == s2.power;
}
constexpr auto operator<=>(const skill& s1, const skill& s2)
{
	return s1.power <=> s2.power;
}
std::ostream& operator<<(std::ostream& o, const skill& s)
{
	return o << s.name;
}
std::istream& operator>>(std::istream& i, skill& s)
{
	i >> s.name;
	i >> s.power;
	return i;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::size_t n, m;
	std::cin >> n >> m;

	std::vector<skill> skills;
	skills.reserve(n);

	std::copy_n(
		std::istream_iterator<skill>(std::cin),
		n,
		std::back_inserter(skills)
	);

	for(
		auto s
		: std::views::iota(std::size_t{}, m)
		| std::views::transform(
			[](auto throwaway) {
				decltype(skill::power) p;
				std::cin >> p;
				return skill{p};
			}
		)
	)
	{
		auto find = std::ranges::lower_bound(skills, s);
		std::cout << *find << '\n';
	}

	return 0;
}
