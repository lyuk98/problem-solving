#include <algorithm>
#include <cstddef>
#include <functional>
#include <ranges>
#include <type_traits>
#include <utility>
#include <vector>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

struct node_iterator
{
    ListNode* node;

    using difference_type = std::ptrdiff_t;
    using value_type = decltype(std::declval<ListNode>().val);
    using reference = std::add_lvalue_reference_t<value_type>;
    using const_reference = std::add_const_t<reference>;

    constexpr reference operator*() { return node->val; }
    constexpr const_reference operator*() const { return node->val; }

    constexpr node_iterator& operator++()
    {
        node = node->next;
        return *this;
    }
    constexpr node_iterator operator++(int)
    {
        node_iterator prev = *this;
        ++*this;
        return prev;
    }

    constexpr bool operator==(const node_iterator& i) const { return this->node == i.node; }
    constexpr bool operator!=(const node_iterator& i) const { return !(*this == i); }
};

struct node_range
{
    node_iterator head;

    constexpr node_iterator begin() { return head; }
    constexpr node_iterator end() { return node_iterator{nullptr}; }
};

class Solution
{
public:
    int pairSum(ListNode* head)
    {
        [[assume(head != nullptr)]];

        const auto list = std::ranges::to<std::vector>(node_range{node_iterator{head}});

        [[assume(!list.empty())]];
        [[assume(list.size() / 2 * 2 == list.size())]];

        auto sums = std::views::zip_transform(
            std::plus<node_iterator::value_type>{},
            list | std::views::take(list.size() / 2),
            list | std::views::reverse | std::views::take(list.size() / 2)
        );

        return *std::ranges::max_element(sums);
    }
};
