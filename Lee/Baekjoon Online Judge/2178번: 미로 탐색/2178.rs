use std::io::prelude::*;
use std::io::stdin;
use std::collections::VecDeque;

#[inline(always)]
fn translate((n, m): (usize, usize), width: usize) -> usize {
    n * width + m
}

#[inline]
fn checked_add(
    (n, m): (usize, usize),
    (d1, d2): (isize, isize),
    (height, width): (usize, usize)
) -> Option<(usize, usize)> {
    Some(
        (
            match n.checked_add_signed(d1) {
                Some(i) => {
                    if i >= height {
                        return None;
                    }
                    i
                },
                None => { return None; },
            },
            match m.checked_add_signed(d2) {
                Some(i) => {
                    if i >= width {
                        return None;
                    }
                    i
                },
                None => { return None; },
            }
        )
    )
}

fn main() {
    let stdin = stdin();
    let mut input = stdin.lock();

    // Block statements can return a value in Rust,
    // making separate declarations and assignments unnecessary
    let (n, m) = {
        let mut line = String::new();
        input.read_line(&mut line).unwrap();

        // Instead of collect()ing the iterator into a Vec,
        // Iterator itself can be used to get next() items
        let mut tokens = line
            .split_whitespace()
            .map(|n| n.parse::<usize>().unwrap());

        // Returning a tuple to be assigned to (n, m)
        (tokens.next().unwrap(), tokens.next().unwrap())
    };

    let mut map: Vec<bool> = Vec::with_capacity(n * m);

    for _ in 0..n {
        let mut line = String::new();
        input.read_line(&mut line).unwrap();

        for c in line.trim_end().chars() {
            map.push(c == '1')
        }
    }

    const DELTAS: [(isize, isize); 4] = [
        (-1, 0), (0, -1), (0, 1), (1, 0)
    ];

    let end = translate((n - 1, m - 1), m);
    let mut queue: VecDeque<(usize, usize)> = VecDeque::with_capacity(n * m);

    queue.push_back((0, 0));
    map[0] = false;

    let mut len = queue.len();
    let mut distance: usize = 0;

    while !queue.is_empty() {
        let current = queue.pop_front().unwrap();

        if translate(current, m) == end {
            distance += 1;
            break;
        }

        for d in DELTAS {
            match checked_add(current, d, (n, m)) {
                Some(new) => {
                    if map[translate(new, m)] {
                        queue.push_back(new);
                        map[translate(new, m)] = false;
                    }
                },
                None => (),
            }
        }

        len = match len - 1 {
            0 => {
                distance += 1;
                queue.len()
            },
            _ => len - 1,
        }
    }

    println!("{}", distance);
}
