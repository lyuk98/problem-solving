use std::collections::VecDeque;
use std::io::prelude::*;
use std::io::stdin;

fn main() {
    const DELTAS: [(isize, isize); 4] = [(-1, 0), (0, -1), (0, 1), (1, 0)];

    let mut input = stdin().lock();

    let (m, n) = {
        let mut line = String::new();
        input.read_line(&mut line).unwrap();

        let mut i = line
            .split_whitespace()
            .map(|word| word.parse::<usize>().unwrap());
        (i.next().unwrap(), i.next().unwrap())
    };

    let mut tomatoes: Vec<Vec<i8>> = Vec::with_capacity(n);
    let mut ripequeue: VecDeque<(usize, usize, usize)> = VecDeque::new();

    let mut fresh_tomatoes: usize = 0;

    for i in 0..n {
        let mut line = String::new();
        input.read_line(&mut line).unwrap();

        let mut row: Vec<i8> = Vec::with_capacity(m);

        for (j, tomato) in line
            .split_whitespace()
            .map(|word| word.parse::<i8>().unwrap())
            .enumerate()
        {
            match tomato {
                0 => {
                    fresh_tomatoes += 1;
                }
                1 => {
                    ripequeue.push_back((i, j, 0));
                }
                _ => (),
            };
            row.push(tomato);
        }
        tomatoes.push(row);
    }

    let mut days: Option<usize> = None;

    if fresh_tomatoes == 0 {
        days = Some(0);
    }

    // Add label to the outer loop to control flow from nested ones
    'ripequeue: while !ripequeue.is_empty() && fresh_tomatoes > 0 {
        let t = ripequeue.pop_front().unwrap();

        for delta in DELTAS {
            if let (Some(i), Some(j)) = (
                t.0.checked_add_signed(delta.0),
                t.1.checked_add_signed(delta.1),
            ) {
                if i >= n || j >= m {
                    continue;
                }

                if tomatoes[i][j] == 0 {
                    fresh_tomatoes -= 1;
                    if fresh_tomatoes == 0 {
                        days = Some(t.2 + 1);

                        // continue outer loop as intended
                        continue 'ripequeue;
                    }

                    tomatoes[i][j] = 1;
                    ripequeue.push_back((i, j, t.2 + 1));
                }
            }
        }
    }

    match days {
        Some(d) => {
            println!("{}", d);
        }
        None => {
            println!("-1");
        }
    };
}
