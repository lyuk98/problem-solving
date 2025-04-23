#include <algorithm>
#include <cstddef>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

class Solution
{
public:
    bool closeStrings(std::string word1, std::string word2)
    {
        constexpr auto key = [](const auto& e) { return e.first; };
        constexpr auto value = [](const auto& e) { return e.second; };

        std::unordered_map<char, std::size_t> frequency1;
        std::unordered_map<char, std::size_t> frequency2;

        for (const auto c1 : word1)
            frequency1[c1] += 1;
        for (const auto c2 : word2)
            frequency2[c2] += 1;

        auto keys1 = frequency1 | std::views::transform(key) | std::ranges::to<std::vector>();
        auto keys2 = frequency2 | std::views::transform(key) | std::ranges::to<std::vector>();
        auto values1 = frequency1 | std::views::transform(value) | std::ranges::to<std::vector>();
        auto values2 = frequency2 | std::views::transform(value) | std::ranges::to<std::vector>();

        std::ranges::sort(keys1);
        std::ranges::sort(keys2);
        std::ranges::sort(values1);
        std::ranges::sort(values2);

        return std::ranges::equal(keys1, keys2) && std::ranges::equal(values1, values2);
    }
};
