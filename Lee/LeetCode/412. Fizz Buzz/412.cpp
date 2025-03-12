#include <ranges>
#include <string>
#include <vector>

inline std::string fizzbuzz_string(int n)
{
    using namespace std::string_literals;

    const auto fizz = n / 3 * 3;
    const auto buzz = n / 5 * 5;

    if (n == fizz && n == buzz)
        return "FizzBuzz"s;
    else if (n == fizz)
        return "Fizz"s;
    else if (n == buzz)
        return "Buzz"s;

    return std::to_string(n);
}

class Solution
{
public:
    std::vector<std::string> fizzBuzz(int n)
    {
        return std::views::iota(1, n + 1) | std::views::transform(fizzbuzz_string) |
               std::ranges::to<std::vector<std::string>>();
    }
};
