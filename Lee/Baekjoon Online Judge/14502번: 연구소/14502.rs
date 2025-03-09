use std::collections::VecDeque;
use std::io::prelude::*;
use std::io::stdin;

#[inline]
fn checked_add(
    (i, j): (usize, usize),
    (d1, d2): (isize, isize),
    (height, width): (usize, usize),
) -> Option<(usize, usize)> {
    if let (Some(k), Some(l)) = (i.checked_add_signed(d1), j.checked_add_signed(d2)) {
        if k < height && l < width {
            return Some((k, l));
        }
    }

    None
}

fn main() {
    const DELTAS: [(isize, isize); 4] = [(-1, 0), (0, -1), (0, 1), (1, 0)];

    let mut input = stdin().lock();

    let (n, m) = {
        let mut line = String::new();
        input.read_line(&mut line).unwrap();

        let mut i = line
            .split_whitespace()
            .map(|word| word.parse::<usize>().unwrap());
        (i.next().unwrap(), i.next().unwrap())
    };

    let mut lab: Vec<Vec<i8>> = vec![vec![0; m]; n];
    let mut blank: Vec<(usize, usize)> = Vec::with_capacity(n * m);
    let mut virus: Vec<(usize, usize)> = Vec::with_capacity(n * m);
    let mut walls: usize = 0;

    for i in 0..n {
        let mut line = String::new();
        input.read_line(&mut line).unwrap();

        for (j, spot) in line
            .split_whitespace()
            .map(|word| word.parse::<i8>().unwrap())
            .enumerate()
        {
            match spot {
                0 => {
                    blank.push((i, j));
                }
                1 => {
                    walls += 1;
                }
                2 => {
                    virus.push((i, j));
                }
                _ => (),
            };

            lab[i][j] = spot;
        }
    }

    walls += 3;
    let mut min = usize::MAX;

    let mut log: Vec<(usize, usize)> = Vec::with_capacity(blank.len());
    let mut queue: VecDeque<(usize, usize)> = VecDeque::with_capacity(blank.len());

    for (i0, b0) in blank.iter().enumerate() {
        lab[b0.0][b0.1] = 1;

        for (i1, b1) in blank.iter().skip(i0 + 1).enumerate() {
            lab[b1.0][b1.1] = 1;

            for b2 in blank.iter().skip(i0 + i1 + 2) {
                lab[b2.0][b2.1] = 1;

                log.clear();
                let mut count: usize = virus.len();

                'spread: for v in &virus {
                    queue.clear();
                    queue.push_back(*v);

                    while !queue.is_empty() {
                        let c = queue.pop_front().unwrap();

                        for d in DELTAS {
                            if let Some(next) = checked_add(c, d, (n, m)) {
                                if lab[next.0][next.1] == 0 {
                                    lab[next.0][next.1] = 2;
                                    queue.push_back(next);
                                    log.push(next);

                                    count += 1;
                                    if count > min {
                                        break 'spread;
                                    }
                                }
                            }
                        }
                    }
                }

                min = min.min(count);

                for l in &log {
                    lab[l.0][l.1] = 0;
                }

                lab[b2.0][b2.1] = 0;
            }
            lab[b1.0][b1.1] = 0;
        }
        lab[b0.0][b0.1] = 0;
    }

    println!("{}", (n * m) - walls - min);
}
