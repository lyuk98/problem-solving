use std::cmp::Ordering;
use std::io::prelude::*;
use std::io::stdin;

fn main() {
    let a = {
        let mut a: Vec<i32> = stdin()
            .lock()
            .lines()
            .skip(1)
            .next()
            .unwrap()
            .unwrap()
            .split_whitespace()
            .map(|t| t.parse::<i32>().unwrap())
            .collect();
        a.sort_unstable();

        a
    };

    let mut good: u16 = 0;

    for (i, value) in a.iter().enumerate() {
        let (mut begin, mut end) = (a.iter().enumerate(), a.iter().enumerate().rev());
        let (mut first, mut last) = (begin.next().unwrap(), end.next().unwrap());

        while first.0 < last.0 {
            if first.0 == i {
                first = begin.next().unwrap();
                continue;
            }
            if last.0 == i {
                last = end.next().unwrap();
                continue;
            }

            match (first.1 + last.1).cmp(value) {
                Ordering::Equal => {
                    good += 1;
                    break;
                }
                Ordering::Less => {
                    first = begin.next().unwrap();
                }
                Ordering::Greater => {
                    last = end.next().unwrap();
                }
            }
        }
    }

    println!("{}", good);
}
