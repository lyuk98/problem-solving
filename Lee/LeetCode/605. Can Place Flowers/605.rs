use std::iter::once;

impl Solution {
    pub fn can_place_flowers(flowerbed: Vec<i32>, n: i32) -> bool {
        let mut flowerbed = once(&0).chain(flowerbed.iter()).chain(once(&0)).peekable();
        let mut count: i32 = 0;

        while flowerbed.peek().is_some() {
            let empty = flowerbed.by_ref().take_while(|f| **f == 0);

            count += match empty.count() {
                0 => 0,
                c => (i32::try_from(c).unwrap() - 1) / 2,
            };
            if count >= n {
                return true;
            }
        }

        false
    }
}
