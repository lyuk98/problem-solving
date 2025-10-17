use std::cell::RefCell;
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
    pub fn lowest_common_ancestor(
        root: Option<Rc<RefCell<TreeNode>>>,
        p: Option<Rc<RefCell<TreeNode>>>,
        q: Option<Rc<RefCell<TreeNode>>>,
    ) -> Option<Rc<RefCell<TreeNode>>> {
        let Some(root) = root else {
            return None;
        };
        if let Some(p) = &p {
            if root == *p {
                return Some(Rc::clone(&root));
            }
        }
        if let Some(q) = &q {
            if root == *q {
                return Some(Rc::clone(&root));
            }
        }

        let (left, right) = (
            Self::lowest_common_ancestor(
                root.borrow().left.as_ref().map(|n| Rc::clone(&n)),
                p.clone(),
                q.clone(),
            ),
            Self::lowest_common_ancestor(
                root.borrow().right.as_ref().map(|n| Rc::clone(&n)),
                p.clone(),
                q.clone(),
            ),
        );

        match (left, right) {
            (Some(_), Some(_)) => Some(Rc::clone(&root)),
            (Some(p), None) => Some(Rc::clone(&p)),
            (None, Some(q)) => Some(Rc::clone(&q)),
            (None, None) => None,
        }
    }
}
