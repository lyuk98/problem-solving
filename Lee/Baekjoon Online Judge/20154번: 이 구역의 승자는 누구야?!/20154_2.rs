use std::io::prelude::*;
use std::io::stdin;

#[inline]
fn map(c: char) -> u32 {
    match c {
        'A' | 'E'..='H' | 'K' | 'M'..='N' => 3,
        'B' | 'D' | 'P'..='R' | 'T' | 'W'..='Y' => 2,
        'C' | 'I'..='J' | 'L' | 'O' | 'S' | 'U'..='V' | 'Z' => 1,
        _ => 0,
    }
}

fn main() {
    let sum: u32 = {
        let mut input = stdin().lock();
        let mut line = String::new();

        input.read_line(&mut line).unwrap();
        line.trim_end().chars().map(map).sum()
    };

    match sum % 2 {
        1 => {
            println!("I'm a winner!");
        }
        _ => {
            println!("You're the winner?");
        }
    }
}
