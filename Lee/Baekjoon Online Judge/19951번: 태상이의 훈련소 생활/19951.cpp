#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::size_t n;
    std::uint_fast32_t m;
    std::vector<std::int_fast32_t> h;

    std::cin >> n >> m;

    [[assume(n >= 1 && n <= 100'000)]];
    [[assume(m >= 1 && m <= 100'000)]];

    h.reserve(n + 1);

    {
        h.push_back(0);
        std::copy_n(
            std::istream_iterator<decltype(h)::value_type>(std::cin), n, std::back_inserter(h)
        );

        decltype(h) d;
        d.reserve(n);

        for (auto i = std::cbegin(h) + 1; i != std::cend(h); ++i)
            d.push_back(*i - *(i - 1));

        std::swap(h, d);
    }

    for (decltype(m) i{}; i < m; ++i)
    {
        std::size_t a, b;
        std::int_fast32_t k;

        std::cin >> a >> b >> k;

        [[assume(a >= 1)]];
        [[assume(b >= a && b <= n)]];

        h[a - 1] += k;
        if (b < n)
            h[b] -= k;
    }

    {
        decltype(h)::value_type p{};
        for (auto i : h)
            std::print(std::cout, "{} ", (p += i));
        std::println(std::cout);
    }

    return 0;
}
