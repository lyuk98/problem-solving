#include <algorithm>
#include <concepts>
#include <numeric>
#include <ranges>
#include <string>

template<std::ranges::input_range range_1, std::ranges::input_range range_2>
    requires std::same_as<std::ranges::range_value_t<range_1>, std::ranges::range_value_t<range_2>>
constexpr std::ranges::input_range auto gcd_r(range_1&& r1, range_2&& r2)
{
    if (!std::ranges::starts_with(r1, r2) && !std::ranges::starts_with(r2, r1))
        return r1 | std::views::take(0);

    const auto length = std::gcd(std::ranges::size(r1), std::ranges::size(r2));

    return r1 | std::views::take(length);
}

class Solution
{
public:
    std::string gcdOfStrings(std::string str1, std::string str2)
    {
        return gcd_r(str1, str2) | std::ranges::to<std::string>();
    }
};
