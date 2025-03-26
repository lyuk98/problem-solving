impl Solution {
    pub fn max_operations(nums: Vec<i32>, k: i32) -> i32 {
        let mut nums = nums;
        nums.sort_unstable();

        let (mut begin, mut end) = (nums.iter().enumerate(), nums.iter().enumerate().rev());
        let mut count: i32 = 0;

        let (mut left, mut right) = (begin.next(), end.next());
        while let (Some((i, a)), Some((j, b))) = (left, right) {
            if !(i < j) {
                break;
            }

            if a + b == k {
                count += 1;
                (left, right) = (begin.next(), end.next());
            } else if a + b < k {
                left = begin.next();
            } else {
                right = end.next();
            }
        }

        count
    }
}
