use std::io::prelude::*;
use std::io::{stdin, stdout, BufWriter};

fn next_permutation(sequence: &mut Vec<u8>) -> bool {
    if sequence.len() < 2 {
        return false;
    }

    let mut i = sequence.len() - 1;
    while i > 0 && sequence[i - 1] >= sequence[i] {
        i -= 1;
    }

    if i == 0 {
        return false;
    }

    let mut j = sequence.len() - 1;
    while j >= i && sequence[j] <= sequence[i - 1] {
        j -= 1;
    }

    sequence.swap(j, i - 1);

    sequence[i..].reverse();

    true
}

fn main() {
    let mut sequence: Vec<u8> = {
        let mut input = stdin().lock();
        let mut line = String::new();
        input.read_line(&mut line).unwrap();
        let n = line.trim_end().parse::<u8>().unwrap();

        (1..=n).collect()
    };

    let mut output = BufWriter::new(stdout().lock());

    // A do-while equivalent in Rust... sort of
    loop {
        for i in &sequence {
            write!(output, "{} ", i).unwrap();
        }
        writeln!(output).unwrap();

        if !next_permutation(&mut sequence) {
            break;
        }
    }
}
