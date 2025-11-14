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
    pub fn delete_node(
        root: Option<Rc<RefCell<TreeNode>>>,
        key: i32,
    ) -> Option<Rc<RefCell<TreeNode>>> {
        let Some(root) = root else {
            return None;
        };

        let mut root_mut = root.borrow_mut();

        match root_mut.val.cmp(&key) {
            Ordering::Greater => {
                root_mut.left = root_mut
                    .left
                    .as_ref()
                    .and_then(|left| Self::delete_node(Some(Rc::clone(left)), key));
                Some(Rc::clone(&root))
            }
            Ordering::Less => {
                root_mut.right = root_mut
                    .right
                    .as_ref()
                    .and_then(|right| Self::delete_node(Some(Rc::clone(right)), key));
                Some(Rc::clone(&root))
            }
            Ordering::Equal => match (root_mut.left.as_ref(), root_mut.right.as_ref()) {
                (None, None) => None,
                (Some(left), None) => Some(Rc::clone(left)),
                (None, Some(right)) => Some(Rc::clone(right)),
                (Some(_), Some(right)) => {
                    let mut node = Rc::clone(right);

                    loop {
                        let Some(left) = node
                            .borrow()
                            .left
                            .as_ref()
                            .and_then(|left| Some(Rc::clone(left)))
                        else {
                            break;
                        };

                        node = left;
                    }

                    node.borrow_mut().left = root_mut
                        .left
                        .as_ref()
                        .and_then(|left| Some(Rc::clone(left)));
                    root_mut
                        .right
                        .as_ref()
                        .and_then(|right| Some(Rc::clone(right)))
                }
            },
        }
    }
}
