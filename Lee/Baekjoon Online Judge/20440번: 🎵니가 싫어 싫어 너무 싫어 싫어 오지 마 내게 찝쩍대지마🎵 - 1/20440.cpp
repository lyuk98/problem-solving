#include <algorithm>
#include <cstdint>
#include <generator>
#include <iostream>
#include <limits>
#include <ranges>
#include <utility>
#include <vector>

using time_type = std::uint_fast32_t;
using count_type = std::int_fast32_t;

struct timeline
{
private:
    std::vector<time_type> enters;
    std::vector<time_type> exits;

public:
    timeline(std::vector<time_type>&& enters, std::vector<time_type>&& exits)
        : enters(std::move(enters)), exits(std::move(exits))
    {}

    std::generator<std::pair<time_type, bool>> get()
    {
        auto s = std::cbegin(enters);
        auto f = std::cbegin(exits);

        while (f != std::cend(exits))
        {
            while (s != std::cend(enters))
            {
                if (*s < *f)
                    co_yield std::make_pair(*s++, true);
                else
                    break;
            }

            co_yield std::make_pair(*f++, false);
        }
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    count_type n;
    std::cin >> n;

    [[assume(n >= 1 && n <= 1'000'000)]];

    std::vector<time_type> enters;
    std::vector<time_type> exits;

    enters.reserve(n);
    enters.reserve(n);

    for (count_type m{}; m < n; ++m)
    {
        time_type enter;
        time_type exit;

        std::cin >> enter >> exit;

        enters.push_back(enter);
        exits.push_back(exit);
    }

    std::ranges::sort(enters);
    std::ranges::sort(exits);

    timeline t(std::move(enters), std::move(exits));

    auto max_time = std::make_pair(
        std::numeric_limits<time_type>::max(), std::numeric_limits<time_type>::max()
    );
    auto max = std::numeric_limits<count_type>::min();

    auto state = std::numeric_limits<time_type>::max();
    count_type delta{};
    std::pair<time_type, count_type> track;

    for (const auto [time, increasing] : t.get())
    {
        if (state == std::numeric_limits<time_type>::max()) [[unlikely]]
            state = time;

        if (state == time)
        {
            delta += (increasing ? 1 : -1);
        }
        else
        {
            if (delta != 0)
            {
                const auto count = track.second + delta;

                if (delta > 0)
                {
                    if (count > max)
                    {
                        max = count;
                        max_time.first = state;
                    }
                }
                else
                {
                    if (track.first == max_time.first)
                        max_time.second = state;
                }

                track.first = state;
                track.second = count;
            }

            delta = (increasing ? 1 : -1);
        }

        state = time;
    }

    if (delta != 0 && track.first == max_time.first)
        max_time.second = state;

    std::println(std::cout, "{}", max);
    std::println(std::cout, "{} {}", max_time.first, max_time.second);

    return 0;
}
