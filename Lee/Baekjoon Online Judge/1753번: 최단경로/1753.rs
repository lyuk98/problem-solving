use std::cmp::Ordering;
use std::collections::BinaryHeap;
use std::io::prelude::*;
use std::io::{stdin, stdout, BufWriter};

#[derive(Copy, Clone, Eq, PartialEq)]
struct State {
    cost: u32,
    position: usize,
}

impl Ord for State {
    fn cmp(&self, other: &Self) -> Ordering {
        other
            .cost
            .cmp(&self.cost)
            .then_with(|| self.position.cmp(&other.position))
    }
}

impl PartialOrd for State {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

#[derive(Copy, Clone)]
struct Edge {
    node: usize,
    cost: u32,
}

fn main() {
    let mut lines = stdin().lock().lines().map(|l| l.unwrap());

    let (v, e) = {
        let line = lines.next().unwrap();
        let mut i = line.split_whitespace().map(|t| t.parse::<usize>().unwrap());

        (i.next().unwrap(), i.next().unwrap())
    };
    let k = lines.next().unwrap().parse::<usize>().unwrap() - 1;

    let edges = {
        let mut edges: Vec<Vec<Edge>> = vec![Vec::new(); v];

        for _ in 0..e {
            let (u, v, w) = {
                let line = lines.next().unwrap();
                let mut i = line.split_whitespace();

                (
                    i.next().unwrap().parse::<usize>().unwrap() - 1,
                    i.next().unwrap().parse::<usize>().unwrap() - 1,
                    i.next().unwrap().parse::<u32>().unwrap(),
                )
            };
            edges[u].push(Edge { node: v, cost: w });
        }
        edges
    };

    let distances = {
        let mut distances: Vec<Option<u32>> = vec![None; v];
        let mut heap: BinaryHeap<State> = BinaryHeap::new();

        distances[k] = Some(0);
        heap.push(State {
            cost: 0,
            position: k,
        });

        while let Some(State { cost, position }) = heap.pop() {
            if cost > distances[position].unwrap() {
                continue;
            }

            for node in &edges[position] {
                if distances[node.node].is_none()
                    || cost + node.cost < distances[node.node].unwrap()
                {
                    let distance = cost + node.cost;
                    distances[node.node] = Some(distance);
                    heap.push(State {
                        cost: distance,
                        position: node.node,
                    });
                }
            }
        }

        distances
    };

    let mut output = BufWriter::new(stdout().lock());
    for distance in &distances {
        match distance {
            Some(distance) => {
                writeln!(output, "{}", distance).unwrap();
            }
            None => {
                writeln!(output, "INF").unwrap();
            }
        }
    }
}
