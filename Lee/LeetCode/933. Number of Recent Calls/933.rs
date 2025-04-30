use std::collections::VecDeque;

struct RecentCounter {
    requests: VecDeque<i32>,
}

impl RecentCounter {
    fn new() -> Self {
        RecentCounter {
            requests: VecDeque::new(),
        }
    }

    fn ping(&mut self, t: i32) -> i32 {
        while let Some(&front) = self.requests.front() {
            if front < (t - 3000) {
                self.requests.pop_front();
            } else {
                break;
            }
        }

        self.requests.push_back(t);
        i32::try_from(self.requests.len()).unwrap()
    }
}
