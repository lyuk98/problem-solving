use std::{
    cmp::Ordering,
    collections::BinaryHeap,
    io::{BufRead, stdin},
    iter::zip,
};

#[derive(Clone, Copy, PartialEq, Eq)]
struct State {
    time: u32,
    position: usize,
}

impl Ord for State {
    fn cmp(&self, other: &Self) -> Ordering {
        other
            .time
            .cmp(&self.time)
            .then_with(|| self.position.cmp(&other.position))
    }
}

impl PartialOrd for State {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

fn distances(reachability: &Vec<Vec<(usize, u32)>>, from: usize, n: usize) -> Vec<u32> {
    let mut distances = vec![u32::MAX; n];
    distances[from] = 0;

    let mut heap = BinaryHeap::new();
    heap.push(State {
        time: 0,
        position: from,
    });

    while let Some(State { time, position }) = heap.pop() {
        if time > distances[position] {
            continue;
        }

        for &(b, t) in &reachability[position] {
            let next = State {
                time: t + time,
                position: b,
            };

            if next.time < distances[next.position] {
                heap.push(next);
                distances[next.position] = next.time;
            }
        }
    }
    distances
}

fn main() {
    let mut lines = stdin().lock().lines().map(|l| l.unwrap());

    let (n, m, x) = {
        let line = lines.next().unwrap();
        let mut tokens = line.split_whitespace().map(|t| t.parse::<usize>().unwrap());

        (
            tokens.next().unwrap(),
            tokens.next().unwrap(),
            tokens.next().unwrap() - 1,
        )
    };

    let (reachability, reachability2) = {
        let mut r = vec![Vec::with_capacity(n); n];
        let mut r2 = vec![Vec::with_capacity(n); n];

        for _ in 0..m {
            let (a, b, t) = {
                let line = lines.next().unwrap();
                let mut tokens = line.split_whitespace();

                (
                    tokens.next().unwrap().parse::<usize>().unwrap() - 1,
                    tokens.next().unwrap().parse::<usize>().unwrap() - 1,
                    tokens.next().unwrap().parse::<u32>().unwrap(),
                )
            };

            r[a].push((b, t));
            r2[b].push((a, t));
        }

        (r, r2)
    };

    println!(
        "{}",
        zip(
            distances(&reachability, x, n).iter(),
            distances(&reachability2, x, n).iter()
        )
        .map(|(a, b)| a + b)
        .max()
        .unwrap()
    );
}
