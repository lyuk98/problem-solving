use std::iter::once;

impl Solution {
    pub fn largest_altitude(gain: Vec<i32>) -> i32 {
        once(0)
            .chain(gain.iter().scan(0, |state, &x| {
                *state += x;
                Some(*state)
            }))
            .max()
            .unwrap_or_default()
    }
}
