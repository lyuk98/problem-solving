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

#[inline]
fn translate((n, m): (usize, usize), width: usize) -> usize {
    n * width + m
}

fn main() {
    const DELTAS: [(isize, isize); 4] = [(-1, 0), (0, -1), (0, 1), (1, 0)];

    let mut lines = stdin().lock().lines().map(|l| l.unwrap());

    let (n, range) = {
        let line = lines.next().unwrap();

        let mut i = line.split_whitespace();
        let n = i.next().unwrap().parse::<usize>().unwrap();

        let mut i = i.map(|t| t.parse::<u32>().unwrap());
        let (l, r) = (i.next().unwrap(), i.next().unwrap());

        (n, l..=r)
    };

    let mut countries: Vec<Vec<u32>> = lines
        .map(|line| {
            line.split_whitespace()
                .map(|t| t.parse::<u32>().unwrap())
                .collect()
        })
        .take(n)
        .collect();

    let mut days: u16 = 0;

    let mut unity: bool = false;
    let mut visit: Vec<bool> = vec![false; n * n];

    let mut queue: VecDeque<(usize, usize)> = VecDeque::new();
    let mut group: Vec<(usize, usize)> = Vec::new();

    loop {
        for r in 0..n {
            for c in 0..n {
                if visit[translate((r, c), n)] {
                    continue;
                }

                let mut sum: u32 = countries[r][c];
                visit[translate((r, c), n)] = true;

                group.clear();
                group.push((r, c));

                queue.clear();
                queue.push_back((r, c));

                while !queue.is_empty() {
                    let (cr, cc) = queue.pop_front().unwrap();

                    for delta in DELTAS {
                        if let Some((nr, nc)) = checked_add((cr, cc), delta, (n, n)) {
                            if !visit[translate((nr, nc), n)]
                                && range.contains(&countries[cr][cc].abs_diff(countries[nr][nc]))
                            {
                                unity = true;
                                visit[translate((nr, nc), n)] = true;

                                group.push((nr, nc));
                                queue.push_back((nr, nc));

                                sum += countries[nr][nc];
                            }
                        }
                    }
                }

                let average = sum / group.len() as u32;
                for (r, c) in &group {
                    countries[*r][*c] = average;
                }
            }
        }

        if !unity {
            break;
        }

        unity = false;
        visit.fill(false);

        days += 1;
    }

    println!("{}", days);
}
