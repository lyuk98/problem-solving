#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <ranges>
#include <utility>
#include <vector>

auto distances(const auto& reachability, std::size_t from, std::size_t n)
{
    std::vector<std::uint_fast32_t> d(n, std::numeric_limits<std::uint_fast32_t>::max());

    using value_type = std::pair<std::uint_fast32_t, std::size_t>;
    std::priority_queue<value_type, std::vector<value_type>, std::greater<value_type>> queue;

    d[from] = 0;
    queue.emplace(0, from);

    while (!queue.empty())
    {
        auto [time, position] = queue.top();
        queue.pop();

        if (time > d[position])
            continue;

        for (auto [b, t] : reachability[position])
        {
            const auto next = std::make_pair(t + time, b);
            if (next.first < d[next.second])
            {
                queue.push(next);
                d[next.second] = next.first;
            }
        }
    }

    return d;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    constexpr auto max = std::numeric_limits<std::uint_fast32_t>::max();

    std::size_t n;
    std::size_t m;
    std::size_t x;

    std::cin >> n >> m >> x;

    [[assume(n >= 1 && n <= 1'000)]];
    [[assume(m >= 1 && m <= 100'000)]];
    [[assume(x >= 1 && x <= n)]];

    --x;

    std::vector<std::vector<std::pair<std::size_t, std::uint_fast32_t>>> reachability(n);
    std::vector<std::vector<std::pair<std::size_t, std::uint_fast32_t>>> reachability2(n);

    for (std::size_t i{}; i < m; ++i)
    {
        std::size_t a;
        std::size_t b;
        std::uint_fast32_t t;

        std::cin >> a >> b >> t;

        [[assume(a >= 1 && a <= n)]];
        [[assume(b >= 1 && b <= n)]];
        [[assume(t >= 1 && x <= 100)]];

        --a;
        --b;

        reachability[a].emplace_back(b, t);
        reachability2[b].emplace_back(a, t);
    }

    auto d = std::views::zip_transform(
        std::plus{}, distances(reachability, x, n), distances(reachability2, x, n)
    );

    std::println(std::cout, "{}", *std::ranges::max_element(d));

    return 0;
}
