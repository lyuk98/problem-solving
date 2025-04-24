#include <cmath>
#include <concepts>
#include <print>
#include <ranges>
#include <string>

void print(std::ranges::input_range auto&& r)
{
    for (const auto& i : r)
        std::print("{} ", i);
    std::println();
}

constexpr const char* ordinal(std::integral auto n)
{
    if constexpr (std::signed_integral<decltype(n)>)
    {
        if (n < decltype(n){})
            return ordinal(std::abs(n));
    }

    switch (n % 100)
    {
    case 11:
    case 12:
    case 13:
        return "th";
    default:
        switch (n % 10)
        {
        case 1:
            return "st";
        case 2:
            return "nd";
        case 3:
            return "rd";
        default:
            return "th";
        }
    }
}

int main()
{
    // 1, 2, 3, 4, 5
    constexpr auto numbers = std::views::iota(1, 6);
    print(numbers);

    // 4, 5, 6, 7, 8
    constexpr auto add_three_to_numbers = numbers | std::views::transform([](auto n) { return n + 3; });
    print(add_three_to_numbers);

    // 6, 7, 8
    constexpr auto skip_two = add_three_to_numbers | std::views::drop(2);
    print(skip_two);

    // 1st, 2nd, 3rd, 4th, 5th
    const auto ordinals = numbers | std::views::transform([](auto n) { return std::to_string(n) + ordinal(n); });
    print(ordinals);

    return 0;
}
