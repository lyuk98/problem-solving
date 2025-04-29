#include <cctype>
#include <charconv>
#include <concepts>
#include <cstddef>
#include <generator>
#include <memory>
#include <ranges>
#include <string>

std::generator<std::string::const_reference> decode(std::ranges::contiguous_range auto&& s)
    requires std::same_as<std::ranges::range_value_t<decltype(s)>, std::string::value_type>
{
    for (auto i = std::ranges::cbegin(s); i != std::ranges::cend(s);)
    {
        if (std::isalpha(*i))
        {
            const auto ll = std::ranges::find_if_not(i, std::ranges::cend(s), [](auto c) {
                return std::isalpha(c);
            });

            const auto leading = std::ranges::subrange(i, ll);
            co_yield std::ranges::elements_of(leading);

            i = ll;
        }
        else
        {
            std::size_t n;

            const auto nl = std::ranges::find_if_not(i, std::ranges::cend(s), [](auto c) {
                return std::isdigit(c);
            });
            std::from_chars(std::to_address(i), std::to_address(nl), n);

            i = nl;
            auto sl = i++;
            std::size_t level{};

            do
            {
                switch (*(sl++))
                {
                case '[':
                    ++level;
                    break;
                case ']':
                    --level;
                    break;
                }
            } while (level != 0);
            --sl;

            for (auto throwaway : std::views::repeat(char{}, n))
                co_yield std::ranges::elements_of(decode(std::ranges::subrange(i, sl)));

            i = sl + 1;
        }
    }
}

class Solution
{
public:
    std::string decodeString(std::string s)
    {
        return decode(s) | std::ranges::to<std::string>();
    }
};
