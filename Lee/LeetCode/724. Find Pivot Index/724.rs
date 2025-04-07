use std::iter::{once, zip};

impl Solution {
    pub fn pivot_index(nums: Vec<i32>) -> i32 {
        let rev: Vec<i32> = nums
            .iter()
            .rev()
            .scan(0, |state, &n| {
                *state += n;
                Some(*state)
            })
            .collect();

        for ((i, left), right) in zip(
            once(0)
                .chain(nums.iter().take(nums.len() - 1).scan(0, |state, &n| {
                    *state += n;
                    Some(*state)
                }))
                .enumerate(),
            rev.iter().take(rev.len() - 1).rev().copied().chain(once(0)),
        ) {
            if left == right {
                return i32::try_from(i).unwrap();
            }
        }

        -1
    }
}
