#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

class Solution
{
public:
    bool canConstruct(std::string ransomNote, std::string magazine)
    {
        std::array<std::int_fast32_t, 26> frequency{};

        for (char c : magazine)
            ++frequency[static_cast<std::size_t>(c - 'a')];

        for (char c : ransomNote)
        {
            if (!(frequency[static_cast<std::size_t>(c - 'a')]--))
                return false;
        }

        return true;
    }
};
