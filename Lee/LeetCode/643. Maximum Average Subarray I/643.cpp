#include <algorithm>
#include <iterator>
#include <numeric>
#include <ranges>
#include <tuple>
#include <vector>

class Solution
{
public:
    double findMaxAverage(std::vector<int>& nums, int k)
    {
        auto state = std::reduce(std::cbegin(nums), std::next(std::cbegin(nums), k));
        auto maximum = state;

        for (auto p : std::views::zip(nums, std::views::drop(nums, k)))
        {
            state = state - std::get<0>(p) + std::get<1>(p);
            maximum = std::max(maximum, state);
        }

        return static_cast<double>(maximum) / static_cast<double>(k);
    }
};
