#include <algorithm>
#include <iterator>
#include <numeric>
#include <ranges>
#include <vector>

class Solution
{
public:
    int maximumWealth(std::vector<std::vector<int>>& accounts)
    {
        return std::ranges::max(accounts | std::views::transform([](const auto& customer) {
                                    return std::reduce(std::cbegin(customer), std::cend(customer));
                                }));
    }
};
