use std::cmp::max;

impl Solution {
    pub fn longest_ones(nums: Vec<i32>, k: i32) -> i32 {
        let nums = nums.iter().map(|n| *n != 0).enumerate();

        let mut count: usize = 0;
        let mut filled: i32 = 0;
        let (mut begin, mut end) = (nums.clone(), nums);
        let (mut left, mut right) = (begin.next(), end.next());

        while let (Some((mut i, a)), Some((j, b))) = (left, right) {
            if !b {
                filled += 1;

                while filled > k {
                    if let Some((i, a)) = left {
                        if !(i < j) {
                            break;
                        }

                        filled -= match a {
                            true => 0,
                            false => 1,
                        };
                        left = begin.next();
                    } else {
                        break;
                    }
                }
                if let Some((it, _)) = left {
                    i = it;
                }

                count = max(
                    count,
                    j - i
                        + match k {
                            0 => 0,
                            _ => 1,
                        },
                );
            } else {
                if !a && k == 0 {
                    left = begin.next();
                    if let Some((it, _)) = left {
                        i = it;
                    }
                }

                count = max(count, j - i + 1);
            }
            right = end.next();
        }

        i32::try_from(count).unwrap()
    }
}
