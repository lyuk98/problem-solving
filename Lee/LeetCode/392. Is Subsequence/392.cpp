#include <algorithm>
#include <iterator>
#include <string>

class Solution
{
public:
    bool isSubsequence(std::string s, std::string t)
    {
        auto si = std::cbegin(s);

        for (auto ti = std::cbegin(t); ti != std::cend(t) && si != std::cend(s); ++si)
        {
            if ((ti = std::find(ti, std::cend(t), *si)) != std::cend(t))
                ++ti;
            else
                --si;
        }

        return si == std::cend(s);
    }
};
