use std::cmp::min;
use std::io::prelude::*;
use std::io::stdin;

fn main() {
    let mut lines = stdin().lock().lines().map(|l| l.unwrap());

    let (_n, s) = {
        let line = lines.next().unwrap();
        let mut tokens = line.split_whitespace().map(|t| t.parse::<u32>().unwrap());

        (tokens.next().unwrap(), tokens.next().unwrap())
    };

    let sequence: Vec<u32> = lines
        .next()
        .unwrap()
        .split_whitespace()
        .map(|t| t.parse::<u32>().unwrap())
        .collect();

    let mut sum = sequence[0];
    let mut length: Option<usize> = None;

    let (mut begin, mut end) = (sequence.iter().enumerate(), sequence.iter().enumerate());
    let (mut first, mut last) = (begin.next().unwrap(), end.next().unwrap());

    loop {
        if sum >= s {
            length = Some(match length {
                Some(l) => min(l, last.0 - first.0 + 1),
                None => last.0 - first.0 + 1,
            });

            if first.0 < last.0 {
                sum -= first.1;
                first = begin.next().unwrap();

                continue;
            }
        }

        last = match end.next() {
            Some(e) => e,
            None => {
                break;
            }
        };
        sum += last.1;
    }

    if let Some(result) = length {
        println!("{}", result);
    } else {
        println!("0");
    }
}
