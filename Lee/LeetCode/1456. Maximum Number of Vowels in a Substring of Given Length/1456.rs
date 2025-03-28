use std::iter::{once, zip};

impl Solution {
    pub fn max_vowels(s: String, k: i32) -> i32 {
        let n = usize::try_from(k).unwrap();
        let i = s.chars().map(|c| match c {
            'a' | 'e' | 'i' | 'o' | 'u' => 1i32,
            _ => 0i32,
        });
        let init = i.clone().take(n).sum();

        once(init)
            .chain(
                zip(i.clone(), i.skip(n)).scan(init, |state, (left, right)| {
                    *state = *state - left + right;
                    Some(*state)
                }),
            )
            .max()
            .unwrap()
    }
}
