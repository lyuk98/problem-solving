#include <cstdint>
#include <unordered_map>
#include <utility>

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

int target;

int count(TreeNode* node, std::int_fast64_t sum)
{
    static std::unordered_map<std::int_fast64_t, int> counts({std::make_pair(0, 1)});

    auto c = counts[sum - target];
    ++counts[sum];

    if (node->left != nullptr)
        c += count(node->left, sum + static_cast<std::int_fast64_t>(node->left->val));
    if (node->right != nullptr)
        c += count(node->right, sum + static_cast<std::int_fast64_t>(node->right->val));

    --counts[sum];

    return c;
}

class Solution
{
public:
    int pathSum(TreeNode* root, int targetSum)
    {
        if (root == nullptr)
            return 0;

        target = targetSum;
        [[assume(target >= -1'000 && target <= 1'000)]];

        return count(root, root->val);
    }
};
