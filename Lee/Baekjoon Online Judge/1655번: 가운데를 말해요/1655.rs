use std::io::prelude::*;
use std::io::{stdin, stdout, BufWriter};
use std::collections::BinaryHeap;
use std::cmp::Reverse;

fn main() {
    let mut input = stdin().lock();
    let mut output = BufWriter::with_capacity(1048576, stdout().lock());

    let n = {
        let mut line = String::new();
        input.read_line(&mut line).unwrap();
        line.trim_end().parse::<usize>().unwrap()
    };

    let mut less: BinaryHeap<i16> = BinaryHeap::with_capacity(
        n / 2 + 1
    );
    let mut greater: BinaryHeap<Reverse<i16>> = BinaryHeap::with_capacity(
        n / 2 + 1
    );

    for _ in 0..n {
        let i = {
            let mut line = String::new();
            input.read_line(&mut line).unwrap();
            line.trim_end().parse::<i16>().unwrap()
        };

        match less.peek() {
            None => { less.push(i); },
            Some(l) => {
                match i <= *l {
                    true => { less.push(i); },
                    false => { greater.push(Reverse(i)); },
                };
            },
        }

        if greater.len() + 1 < less.len() {
            greater.push(Reverse(less.pop().unwrap()));
        }
        else if less.len() < greater.len() {
            less.push(greater.pop().unwrap().0);
        }

        writeln!(output, "{}", less.peek().unwrap()).unwrap();
    }
}
