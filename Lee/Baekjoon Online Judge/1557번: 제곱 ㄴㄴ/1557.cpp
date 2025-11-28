#include <cstddef>
#include <cstdint>
#include <limits>
#include <numeric>
#include <concepts>
#include <iterator>
#include <algorithm>
#include <array>
#include <vector>
#include <iostream>

using uint_type = std::uint_fast64_t;

namespace prime
{
	constexpr std::array<uint_type, 10> small_primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
	constexpr std::array<uint_type, 8> offset = { 6, 4, 2, 4, 2, 4, 6, 2 };
	constexpr std::array<uint_type, 8> indices = { 1, 7, 11, 13, 17, 19, 23, 29 };
}

constexpr bool is_prime(uint_type n)
{
	if(n < prime::small_primes.front()) return false;

	for(const auto p : prime::small_primes)
	{
		const auto q = n / p;
		if(q < p) return true;
		if(q * p == n) return false;
	}

	for(uint_type p = prime::small_primes.back() + prime::offset.back();;)
	{
		for(const auto o : prime::offset)
		{
			const auto q = n / p;
			if(q < p) return true;
			if(q * p == n) return false;
			p += o;
		}
	}
}

constexpr uint_type next_prime(uint_type n)
{
	if(n <= prime::small_primes.back())
		return *std::lower_bound(std::cbegin(prime::small_primes), std::cend(prime::small_primes), n);
	constexpr uint_type l = 30;

	auto k = n / l;
	auto it = std::lower_bound(std::cbegin(prime::indices), std::cend(prime::indices), n - (k * l));
	n = (l * k) + *it;

	while(!is_prime(n))
	{
		if(++it == std::cend(prime::indices))
		{
			++k;
			it = std::cbegin(prime::indices);
		}
		n = l * k + *it;
	}

	return n;
}

template<typename iterator>
	requires
		std::forward_iterator<iterator> &&
		std::integral<typename std::iterator_traits<iterator>::value_type>
constexpr auto count_sqnn(
	iterator first,
	iterator last,
	typename std::iterator_traits<iterator>::value_type n,
	typename std::iterator_traits<iterator>::value_type current
)
{
	if(first == last) return decltype(n){};

	const auto square = *first * *first;
	const auto next_current = square * current;

	if(next_current > n) return decltype(n){};

	auto count = n / next_current;

	count += count_sqnn(std::next(first), last, n, current);
	count -= count_sqnn(std::next(first), last, n, next_current);

	return count;
}

template<typename iterator>
	requires
		std::forward_iterator<iterator> &&
		std::integral<typename std::iterator_traits<iterator>::value_type>
constexpr auto count_sqnn(
	iterator first,
	iterator last,
	typename std::iterator_traits<iterator>::value_type n
)
{
	return count_sqnn(first, last, n, decltype(n){1});
}

uint_type nth_sqnn(uint_type n)
{
	constexpr uint_type limit = UINT64_C(1) << UINT64_C(32);

	std::vector<uint_type> primes;
	primes.reserve(6542);

	for(uint_type n = 2; n * n < limit; n = next_prime(n + 1))
		primes.push_back(n);

	uint_type first = 1;
	for(uint_type last = limit; first < last;)
	{
		const auto mid = std::midpoint(first, last);

		auto count = mid - count_sqnn(std::cbegin(primes), std::cend(primes), mid);

		if(count < n) first = mid + 1;
		else last = mid;
	}

	return first;
}

int main()
{
	uint_type k;
	std::cin >> k;
	std::cout << nth_sqnn(k) << '\n';

	return 0;
}
