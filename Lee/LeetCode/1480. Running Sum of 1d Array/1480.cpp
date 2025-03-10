#include <iterator>
#include <numeric>
#include <vector>

class Solution
{
public:
    std::vector<int> runningSum(std::vector<int>& nums)
    {
        std::vector<int> sums;
        sums.reserve(nums.size());

        std::partial_sum(std::cbegin(nums), std::cend(nums), std::back_inserter(sums));

        return sums;
    }
};
