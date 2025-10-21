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
    pub fn max_level_sum(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        let Some(root) = root else {
            return Default::default();
        };

        let mut queue = VecDeque::new();

        queue.push_back(Rc::clone(&root));

        let mut size = queue.len();
        let mut level = 1;
        let mut sum = 0;

        let mut min = (i32::MIN, i32::MIN);

        while let Some(node) = queue.pop_front() {
            if let Some(left) = &node.borrow().left {
                queue.push_back(Rc::clone(left));
            }
            if let Some(right) = &node.borrow().right {
                queue.push_back(Rc::clone(right));
            }

            sum += node.borrow().val;
            size -= 1;

            if size < 1 {
                min = match min.1 < sum {
                    true => (level, sum),
                    false => min,
                };

                size = queue.len();
                level += 1;
                sum = 0;
            }
        }

        min.0
    }
}
