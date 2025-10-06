use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;

// Definition for a binary tree node.
// #[derive(Debug, PartialEq, Eq)]
// pub struct TreeNode {
//   pub val: i32,
//   pub left: Option<Rc<RefCell<TreeNode>>>,
//   pub right: Option<Rc<RefCell<TreeNode>>>,
// }
// 
// impl TreeNode {
//   #[inline]
//   pub fn new(val: i32) -> Self {
//     TreeNode {
//       val,
//       left: None,
//       right: None
//     }
//   }
// }

impl Solution {
    pub fn max_depth(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        let Some(root) = root else { return 0 };

        root.borrow_mut().val = 1;
        let mut level: i32 = 1;

        let mut stack = VecDeque::new();
        stack.push_back(root);

        while let Some(node) = stack.pop_back() {
            let current = node.borrow().val;
            level = level.max(current);

            if let Some(left) = &node.borrow_mut().left {
                left.borrow_mut().val = current + 1;
                stack.push_back(Rc::clone(left));
            }
            if let Some(right) = &node.borrow_mut().right {
                right.borrow_mut().val = current + 1;
                stack.push_back(Rc::clone(right));
            }
        }

        level
    }
}
