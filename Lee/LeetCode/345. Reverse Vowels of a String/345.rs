#[inline]
fn is_vowel(c: &char) -> bool {
    match c {
        'a' | 'e' | 'i' | 'o' | 'u' | 'A' | 'E' | 'I' | 'O' | 'U' => true,
        _ => false,
    }
}

impl Solution {
    pub fn reverse_vowels(s: String) -> String {
        let mut vowels = s.chars().filter(is_vowel).rev();
        s.chars()
            .map(|c| match is_vowel(&c) {
                true => vowels.next().unwrap(),
                false => c,
            })
            .collect()
    }
}
