use std::{
    collections::{HashSet, VecDeque},
    iter,
};

impl Solution {
    pub fn find_circle_num(is_connected: Vec<Vec<i32>>) -> i32 {
        let mut provinces: Vec<_> = iter::repeat_n(usize::MAX, is_connected.len()).collect();

        let mut queue = VecDeque::new();

        for c in 0..provinces.len() {
            if provinces[c] != usize::MAX {
                continue;
            }
            provinces[c] = c;

            queue.clear();
            queue.push_back(c);

            while let Some(ci) = queue.pop_back() {
                for nci in is_connected[ci]
                    .iter()
                    .enumerate()
                    .filter(|(_, i)| **i != 0)
                    .map(|(c, _)| c)
                {
                    if provinces[nci] != usize::MAX {
                        continue;
                    }

                    provinces[nci] = c;
                    queue.push_back(nci);
                }
            }
        }

        provinces
            .iter()
            .collect::<HashSet<_>>()
            .len()
            .try_into()
            .unwrap()
    }
}
