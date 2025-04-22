use std::collections::{HashMap, HashSet};

impl Solution {
    pub fn unique_occurrences(arr: Vec<i32>) -> bool {
        let occurrences = {
            let mut occurrences: HashMap<i32, u16> = HashMap::with_capacity(arr.len());
            for n in arr {
                *occurrences.entry(n).or_default() += 1;
            }
            occurrences
        };

        {
            let mut set: HashSet<u16> = HashSet::with_capacity(occurrences.len());
            occurrences.values().all(|n| set.insert(*n))
        }
    }
}
