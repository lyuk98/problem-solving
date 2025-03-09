#include <cstddef>
#include <algorithm>
#include <array>
#include <string_view>
#include <iostream>

template<std::ptrdiff_t n, std::size_t length>
consteval auto permutation_string()
{
	static_assert(n >= 1 && n <= 8);

	std::array<char, 8> sequence = {
		'1', '2', '3', '4', '5', '6', '7', '8'
	};
	std::array<char, length> data;
	auto s = sequence.data();
	auto e = s + n;
	auto i = data.data();

	do {
		for(auto it = s; it != e; ++it)
		{
			*i = *it;
			*(i + 1) = ' ';
			i += 2;
		}
		*(i++) = '\n';
	} while(std::next_permutation(s, e));

	return data;
};

int main()
{
	constexpr auto p1 = permutation_string<1, 3>();
	constexpr auto p2 = permutation_string<2, 10>();
	constexpr auto p3 = permutation_string<3, 42>();
	constexpr auto p4 = permutation_string<4, 216>();
	constexpr auto p5 = permutation_string<5, 1320>();
	constexpr auto p6 = permutation_string<6, 9360>();
	constexpr auto p7 = permutation_string<7, 75600>();
	constexpr auto p8 = permutation_string<8, 685440>();

	const std::array<std::string_view, 9> data = {
		std::string_view(),
		std::string_view(p1.cbegin(), p1.cend()),
		std::string_view(p2.cbegin(), p2.cend()),
		std::string_view(p3.cbegin(), p3.cend()),
		std::string_view(p4.cbegin(), p4.cend()),
		std::string_view(p5.cbegin(), p5.cend()),
		std::string_view(p6.cbegin(), p6.cend()),
		std::string_view(p7.cbegin(), p7.cend()),
		std::string_view(p8.cbegin(), p8.cend())
	};

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::size_t n;
	std::cin >> n;

	std::cout << data[n];

	return 0;
}
