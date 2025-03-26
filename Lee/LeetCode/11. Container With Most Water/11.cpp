#include <algorithm>
#include <iterator>
#include <vector>

class Solution
{
public:
    int maxArea(std::vector<int>& height)
    {
        int result = 0;

        auto left = std::cbegin(height);
        auto right = std::crbegin(height);

        while (left < right.base())
        {
            result =
                std::max(result, static_cast<int>(std::min(*left, *right) * (std::distance(left, right.base()) - 1)));

            if (*left < *right)
                ++left;
            else
                ++right;
        }

        return result;
    }
};
