use std::{cmp::min, iter::zip};

impl Solution {
    pub fn merge_alternately(word1: String, word2: String) -> String {
        let len = min(word1.len(), word2.len());
        let merged = zip(word1.chars(), word2.chars()).flat_map(|(char1, char2)| [char1, char2]);

        merged.chain(word1.chars().skip(len))
            .chain(word2.chars().skip(len))
            .collect()
    }
}
