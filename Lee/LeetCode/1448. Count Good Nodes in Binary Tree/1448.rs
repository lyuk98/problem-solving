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
    pub fn good_nodes(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        let Some(root) = root else {
            return 0;
        };

        let mut count = 0;
        let mut stack = VecDeque::new();

        stack.push_back((Rc::clone(&root), root.borrow().val));

        while let Some((current, max)) = stack.pop_back() {
            if current.borrow().val >= max {
                count += 1;
            }

            if let Some(left) = &current.borrow().left {
                stack.push_back((Rc::clone(&left), max.max(current.borrow().val)));
            }
            if let Some(right) = &current.borrow().right {
                stack.push_back((Rc::clone(&right), max.max(current.borrow().val)));
            }
        }

        count
    }
}
