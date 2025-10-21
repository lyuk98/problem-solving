#include <queue>
#include <stack>

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
    std::vector<int> rightSideView(TreeNode* root)
    {
        std::vector<int> path;

        if (root == nullptr)
            return path;

        std::queue<TreeNode*> queue;
        queue.push(root);

        auto size = queue.size();

        while (!queue.empty())
        {
            auto node = queue.front();
            queue.pop();

            for (auto next : {node->left, node->right})
            {
                if (next != nullptr)
                    queue.push(next);
            }

            if (--size < 1)
            {
                path.push_back(node->val);
                size = queue.size();
            }
        }

        return path;
    }
};
