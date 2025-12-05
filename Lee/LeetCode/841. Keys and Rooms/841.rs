use std::collections::VecDeque;

impl Solution {
    pub fn can_visit_all_rooms(rooms: Vec<Vec<i32>>) -> bool {
        let mut visited = vec![false; rooms.len()];
        let mut stack = VecDeque::new();

        visited[0] = true;
        stack.push_back(0);

        while let Some(key) = stack.pop_back() {
            let Ok(key) = usize::try_from(key) else {
                break;
            };

            for next in &rooms[key] {
                let Ok(key) = usize::try_from(*next) else {
                    break;
                };

                if !visited[key] {
                    visited[key] = true;
                    stack.push_back(*next);
                }
            }
        }

        visited.iter().all(|v| *v)
    }
}
