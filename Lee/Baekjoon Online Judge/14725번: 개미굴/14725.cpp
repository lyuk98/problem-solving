#include <cstddef>
#include <utility>
#include <iterator>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <iostream>

template<std::size_t depth>
struct nest
{
	using value_type = std::map<std::string, nest<depth + 1>>;

	value_type value;

	auto operator[](const std::string& key) { return value[key]; }
	auto operator[](std::string&& key) { return value[std::move(key)]; }
};

template<>
struct nest<15> {};

template<std::size_t depth>
std::ostream& operator<<(
	std::ostream& os,
	const std::map<std::string, nest<depth>>& n
)
{
	for(const auto& child : n)
	{
		std::fill_n(
			std::ostreambuf_iterator<char>(os),
			2 * depth,
			'-'
		);
		os << child.first << '\n';

		if constexpr(depth < 15)
			os << child.second.value;
	}

	return os;
}

template<std::size_t depth>
void insert(
	std::map<std::string, nest<depth>>& n,
	std::vector<std::string>&& to_insert
)
{
	auto& item = n[std::move(to_insert[depth])];

	if(depth + 1 < to_insert.size())
		insert(item.value, std::move(to_insert));
}

template<>
void insert(
	std::map<std::string, nest<15>>& n,
	std::vector<std::string>&& to_insert
)
{
	n[std::move(to_insert[15])];
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::size_t n;
	std::cin >> n;

	std::map<std::string, nest<0>> paths;
	std::vector<std::string> words;
	words.reserve(15);

	for(decltype(n) i{}; i < n; ++i)
	{
		std::size_t k;
		std::cin >> k;

		words.clear();
		std::copy_n(
			std::istream_iterator<std::string>(std::cin),
			k,
			std::back_inserter(words)
		);

		insert(paths, std::move(words));
	}

	std::cout << paths;

	return 0;
}
