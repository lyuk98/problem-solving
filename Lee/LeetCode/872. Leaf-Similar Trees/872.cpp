#include <algorithm>
#include <generator>
#include <ranges>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

std::generator<int> leaf(TreeNode* node)
{
    if (node->left)
        co_yield std::ranges::elements_of(leaf(node->left));
    if (node->right)
        co_yield std::ranges::elements_of(leaf(node->right));

    if (!node->left && !node->right)
        co_yield node->val;
}

class Solution
{
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2)
    {
        return std::ranges::equal(leaf(root1), leaf(root2));
    }
};
