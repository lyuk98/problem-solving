use std::io::prelude::*;
use std::io::{stdin, stdout, BufWriter};

fn main() {
    let mut input = stdin().lock();
    let mut output = BufWriter::new(stdout().lock());

    let n = {
        let mut line = String::new();
        input.read_line(&mut line).unwrap();
        line.trim_end().parse::<u32>().unwrap()
    };

    for _ in 0..n {
        let _ = {
            let mut line = String::new();
            input.read_line(&mut line).unwrap();
            line
        };

        let mut carriages: Vec<u8> = {
            let mut line = String::new();
            input.read_line(&mut line).unwrap();
            line.split_whitespace()
                .map(|word| word.parse::<u8>().unwrap())
                .collect()
        };

        let mut swaps: u32 = 0;
        let mut swapped = true;

        while swapped {
            swapped = false;

            for i in 1..carriages.len() {
                if carriages[i - 1] > carriages[i] {
                    carriages.swap(i - 1, i);
                    swapped = true;
                    swaps += 1;
                }
            }
        }

        writeln!(output, "Optimal train swapping takes {} swaps.", swaps).unwrap();
    }
}
