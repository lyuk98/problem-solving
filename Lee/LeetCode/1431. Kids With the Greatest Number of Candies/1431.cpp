#include <algorithm>
#include <ranges>
#include <vector>

class Solution
{
public:
    std::vector<bool> kidsWithCandies(std::vector<int>& candies, int extraCandies)
    {
        const auto greatest = std::ranges::max(candies);
        const auto transform = [greatest, extraCandies](int candy) { return candy + extraCandies >= greatest; };

        return candies | std::views::transform(transform) | std::ranges::to<std::vector<bool>>();
    }
};
