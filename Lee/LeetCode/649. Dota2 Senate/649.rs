use std::collections::VecDeque;

impl Solution {
    pub fn predict_party_victory(senate: String) -> String {
        let mut radiant = VecDeque::new();
        let mut dire = VecDeque::new();

        for (i, senator) in senate.chars().enumerate() {
            match senator {
                'R' => {
                    radiant.push_back(i);
                }
                'D' => {
                    dire.push_back(i);
                }
                _ => (),
            };
        }
        let n = radiant.len() + dire.len();

        while !radiant.is_empty() && !dire.is_empty() {
            let (Some(r), Some(d)) = (radiant.pop_front(), dire.pop_front()) else {
                break;
            };

            match r < d {
                true => {
                    radiant.push_back(r + n);
                }
                false => {
                    dire.push_back(d + n);
                }
            };
        }

        match radiant.is_empty() {
            true => "Dire".to_string(),
            false => "Radiant".to_string(),
        }
    }
}
