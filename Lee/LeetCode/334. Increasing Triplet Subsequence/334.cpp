#include <limits>
#include <vector>

class Solution
{
public:
    bool increasingTriplet(std::vector<int>& nums)
    {
        auto first = std::numeric_limits<int>::max();
        auto second = std::numeric_limits<int>::max();

        for (const auto n : nums)
        {
            if (n <= first)
                first = n;
            else if (n <= second)
                second = n;
            else
                return true;
        }

        return false;
    }
};
