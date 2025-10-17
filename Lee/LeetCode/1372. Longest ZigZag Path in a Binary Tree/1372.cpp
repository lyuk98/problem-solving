#include <algorithm>
#include <stack>
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

class Solution
{
public:
    int longestZigZag(TreeNode* root)
    {
        [[assume(root != nullptr)]];

        int max = 0;
        root->val = 0;

        std::stack<std::pair<TreeNode*, int>> stack;
        stack.emplace(root, 0);

        while (!stack.empty())
        {
            auto [node, streak] = stack.top();
            stack.pop();

            max = std::max(streak, max);

            if (node->left != nullptr)
                node->left->val = -1;
            if (node->right != nullptr)
                node->right->val = 1;

            switch (node->val)
            {
            case 1:
                if (node->left != nullptr)
                    stack.emplace(node->left, streak + 1);
                if (node->right != nullptr)
                    stack.emplace(node->right, 1);
                break;
            case -1:
                if (node->left != nullptr)
                    stack.emplace(node->left, 1);
                if (node->right != nullptr)
                    stack.emplace(node->right, streak + 1);
                break;
            default:
                [[unlikely]]
                if (node->left != nullptr)
                    stack.emplace(node->left, 1);
                if (node->right != nullptr)
                    stack.emplace(node->right, 1);
                break;
            }
        }

        return max;
    }
};
