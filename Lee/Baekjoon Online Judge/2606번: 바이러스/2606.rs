use std::io::prelude::*;
use std::io::stdin;

fn main() {
    let mut lines = stdin().lock().lines().map(|l| l.unwrap());

    let (computers, pairs) = {
        (
            lines.next().unwrap().parse::<usize>().unwrap(),
            lines.next().unwrap().parse::<usize>().unwrap(),
        )
    };

    let mut link: Vec<Vec<usize>> = vec![Vec::with_capacity(computers); computers];

    for _ in 0..pairs {
        let (a, b) = {
            let line = lines.next().unwrap();
            let mut tokens = line.split_whitespace().map(|t| t.parse::<usize>().unwrap());
            (tokens.next().unwrap() - 1, tokens.next().unwrap() - 1)
        };

        link[a].push(b);
        link[b].push(a);
    }

    let mut spread: Vec<bool> = vec![false; computers];
    let mut stack: Vec<usize> = Vec::with_capacity(computers);

    spread[0] = true;
    stack.push(0);

    while !stack.is_empty() {
        let current = stack.pop().unwrap();

        spread[current] = true;

        for destination in &link[current] {
            if !spread[*destination] {
                stack.push(*destination);
            }
        }
    }

    println!("{}", spread.iter().filter(|c| **c).count() - 1);
}
