fn gcd<'a>(str1: &'a str, str2: &'a str) -> &'a str {
    if str1.len() < str2.len() {
        return gcd(str2, str1);
    }

    if !str1.starts_with(str2) {
        return "";
    }
    if str2.is_empty() {
        return str1;
    }

    gcd(&str1[str2.len()..], str2)
}

impl Solution {
    pub fn gcd_of_strings(str1: String, str2: String) -> String {
        gcd(str1.as_str(), str2.as_str()).to_string()
    }
}
