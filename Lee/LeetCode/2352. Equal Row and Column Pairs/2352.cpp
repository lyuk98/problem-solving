#include <algorithm>
#include <ranges>
#include <vector>

class Solution
{
public:
    int equalPairs(std::vector<std::vector<int>>& grid)
    {
        return std::ranges::fold_left(
            grid | std::views::enumerate | std::views::transform([&grid](const auto& e) {
                const auto& [i, row] = e;

                return static_cast<int>(std::ranges::count_if(
                    std::views::iota(decltype(grid.size()){}, grid.size()) |
                        std::views::transform([&grid](const auto j) {
                            return grid | std::views::transform([j](const auto& row) { return row[j]; });
                        }),
                    [&row](const auto& column) { return std::ranges::equal(row, column); }
                ));
            }),
            int{}, std::plus<>()
        );
    }
};
