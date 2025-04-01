use std::{cmp::max, iter::zip};

impl Solution {
    pub fn longest_subarray(nums: Vec<i32>) -> i32 {
        let nums = nums.split(|n| *n == 0).map(|ns| ns.len());
        let mut count: usize = {
            let mut i = nums.clone();
            if let Some(n) = i.next() {
                if i.next().is_none() {
                    return i32::try_from(match n {
                        0 => 0,
                        _ => n - 1,
                    })
                    .unwrap();
                }
                n
            } else {
                return 0;
            }
        };

        for (a, b) in zip(nums.clone(), nums.skip(1)) {
            count = max(count, a + b);
        }

        i32::try_from(count).unwrap()
    }
}
