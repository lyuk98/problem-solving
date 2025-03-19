use std::iter::{repeat, zip};

#[inline]
fn multiply(state: &mut i32, x: &i32) -> Option<i32> {
    *state = *state * x;
    Some(*state)
}

impl Solution {
    pub fn product_except_self(nums: Vec<i32>) -> Vec<i32> {
        let suffixes: Vec<i32> = nums.iter().rev().scan(1, multiply).collect();

        zip(
            repeat(1).take(2).chain(nums.iter().scan(1, multiply)),
            suffixes.iter().rev().chain(repeat(&1).take(2)),
        )
        .skip(1)
        .take(nums.len())
        .map(|(prefix, suffix)| prefix * suffix)
        .collect()
    }
}
