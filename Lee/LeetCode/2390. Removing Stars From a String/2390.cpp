#include <string>

class Solution
{
public:
    std::string removeStars(std::string s)
    {
        std::string removed;
        removed.reserve(s.size());

        for (auto c : s)
        {
            if (c == '*')
            {
                if (!removed.empty()) [[likely]]
                    removed.pop_back();
            }
            else
            {
                removed.push_back(c);
            }
        }

        return removed;
    }
};
