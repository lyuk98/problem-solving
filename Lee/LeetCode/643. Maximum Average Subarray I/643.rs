use std::{cmp::max, iter::zip};

impl Solution {
    pub fn find_max_average(nums: Vec<i32>, k: i32) -> f64 {
        let n = usize::try_from(k).unwrap();

        let mut state: i32 = nums.iter().take(n).copied().sum();
        let mut maximum = state;

        for (left, right) in zip(nums.iter(), nums.iter().skip(n)) {
            state = state - left + right;
            maximum = max(maximum, state);
        }

        f64::from(maximum) / f64::from(k)
    }
}
