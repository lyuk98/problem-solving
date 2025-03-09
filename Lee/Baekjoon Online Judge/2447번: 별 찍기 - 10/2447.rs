use std::io::prelude::*;
use std::io::{stdin, stdout};

fn is_blank(i: u16, j: u16) -> bool {
    let mut i = i;
    let mut j = j;

    while i > 0 || j > 0 {
        if i % 3 == 1 && j % 3 == 1 {
            return true;
        }

        i /= 3;
        j /= 3;
    }

    false
}

fn main() {
    let mut input = stdin().lock();
    let mut output = stdout().lock();

    let n = {
        let mut line = String::new();
        input.read_line(&mut line).unwrap();

        line.trim_end().parse::<u16>().unwrap()
    };

    for i in 0..n {
        for j in 0..n {
            write!(
                output,
                "{}",
                match is_blank(i, j) {
                    true => ' ',
                    false => '*',
                }
            ).unwrap();
        }
        writeln!(output).unwrap();
    }
}
