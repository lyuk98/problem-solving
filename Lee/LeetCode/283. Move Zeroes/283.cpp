#include <algorithm>
#include <iterator>
#include <vector>

class Solution
{
public:
    void moveZeroes(std::vector<int>& nums)
    {
        std::fill(std::remove(std::begin(nums), std::end(nums), 0), std::end(nums), 0);
    }
};
