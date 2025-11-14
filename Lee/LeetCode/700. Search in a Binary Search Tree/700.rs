use std::cell::RefCell;
use std::cmp::Ordering;
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
    pub fn search_bst(
        root: Option<Rc<RefCell<TreeNode>>>,
        val: i32,
    ) -> Option<Rc<RefCell<TreeNode>>> {
        let Some(root) = root else {
            return None;
        };

        match root.borrow().val.cmp(&val) {
            Ordering::Equal => Some(Rc::clone(&root)),
            Ordering::Greater => root
                .borrow()
                .left
                .as_ref()
                .and_then(|left| Self::search_bst(Some(Rc::clone(&left)), val)),
            Ordering::Less => root
                .borrow()
                .right
                .as_ref()
                .and_then(|right| Self::search_bst(Some(Rc::clone(&right)), val)),
        }
    }
}
