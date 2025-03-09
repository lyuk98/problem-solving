use std::io::prelude::*;
use std::io::stdin;
use std::collections::VecDeque;

fn main() {
    let mut input = stdin().lock();

    let n = {
        let mut line = String::new();
        input.read_line(&mut line).unwrap();

        line.trim_end().parse::<usize>().unwrap()
    };

    let mut family: Vec<Vec<bool>> = vec![vec![false; n]; n];
    let find = {
        let mut line = String::new();
        input.read_line(&mut line).unwrap();

        let mut i = line
            .split_whitespace()
            .map(|word| word.parse::<usize>().unwrap());
        (i.next().unwrap() - 1, i.next().unwrap() - 1)
    };

    let m = {
        let mut line = String::new();
        input.read_line(&mut line).unwrap();

        line.trim_end().parse::<usize>().unwrap()
    };

    for _ in 0..m {
        let (x, y) = {
            let mut line = String::new();
            input.read_line(&mut line).unwrap();
    
            let mut i = line
                .split_whitespace()
                .map(|word| word.parse::<usize>().unwrap());
            (i.next().unwrap() - 1, i.next().unwrap() - 1)
        };

        family[x][y] = true;
        family[y][x] = true;
    }

    for i in 0..family.len() {
        family[i][find.0] = false;
    }

    let mut distance: Option<usize> = None;
    let mut queue: VecDeque<(usize, usize)> = VecDeque::with_capacity(m);

    queue.push_back((find.0, 0));

    while !queue.is_empty() {
        let current = queue.pop_front().unwrap();

        if current.0 == find.1 {
            distance = Some(current.1);
            break;
        }

        for i in 0..family[current.0].len() {
            if family[current.0][i] {
                for it in 0..family.len() {
                    family[it][i] = false;
                }
                queue.push_back((i, current.1 + 1));
            }
        }
    }

    match distance {
        Some(d) => { println!("{}", d); },
        None => { println!("-1"); }
    };
}
