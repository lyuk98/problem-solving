use std::io::prelude::*;
use std::io::stdin;
use std::cmp::max;

fn main() {
    let mut input = stdin().lock();
    let a: Vec<char> = {
        let mut line = String::new();
        input.read_line(&mut line).unwrap();
        line.trim_end().chars().collect()
    };
    let b: Vec<char> = {
        let mut line = String::new();
        input.read_line(&mut line).unwrap();
        line.trim_end().chars().collect()
    };

    let mut l: Vec<Vec<u32>> = vec![vec![0; b.len() + 1]; a.len() + 1];

    for i in 1..=a.len() {
        for j in 1..=b.len() {
            l[i][j] = match a[i - 1] == b[j - 1] {
                true => l[i - 1][j - 1] + 1,
                false => max(l[i - 1][j], l[i][j - 1]),
            };
        }
    }

    let lcs: String = {
        let mut s = String::with_capacity(
            l[a.len()][b.len()] as usize
        );

        let (mut i, mut j) = (a.len(), b.len());

        while i > 0 && j > 0 {
            if a[i - 1] == b[j - 1] {
                s.push(a[i - 1]);
                i -= 1;
                j -= 1;
            }
            else {
                match l[i - 1][j] > l[i][j - 1] {
                    true => { i -= 1; },
                    false => { j -= 1; },
                }
            }
        }

        s.chars().rev().collect()
    };

    println!("{}", lcs.chars().count());
    if !lcs.is_empty() {
        println!("{}", lcs);
    }
}
