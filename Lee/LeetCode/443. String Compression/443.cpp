#include <algorithm>
#include <charconv>
#include <iterator>
#include <memory>
#include <vector>

class Solution
{
public:
    int compress(std::vector<char>& chars)
    {
        auto write = std::data(chars);

        for (auto first = std::begin(chars); first != std::end(chars);)
        {
            auto second = std::find_if_not(first, std::end(chars), [first](char c) { return c == *first; });
            const auto distance = std::distance(first, second);

            *write++ = *first;
            first = second;

            if (distance > 1)
                write = std::to_chars(write, std::to_address(std::end(chars)), distance).ptr;
        }

        return std::distance(std::data(chars), write);
    }
};
