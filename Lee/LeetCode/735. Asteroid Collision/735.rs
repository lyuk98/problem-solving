use std::cmp::Ordering;

impl Solution {
    pub fn asteroid_collision(asteroids: Vec<i32>) -> Vec<i32> {
        let mut aftermath: Vec<i32> = Vec::new();

        for asteroid in asteroids {
            let mut asteroid = Some(asteroid);

            while let (Some(&left), Some(right)) = (aftermath.last(), asteroid) {
                if ((left < 0) == (right < 0)) || ((left < 0) && (right > 0)) {
                    break;
                }
                let left = aftermath.pop().unwrap();

                asteroid = match left.abs().cmp(&right.abs()) {
                    Ordering::Less => Some(right),
                    Ordering::Greater => Some(left),
                    Ordering::Equal => None,
                };
            }

            if let Some(asteroid) = asteroid {
                aftermath.push(asteroid);
            }
        }

        aftermath
    }
}
