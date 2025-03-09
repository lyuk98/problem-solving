use std::io::prelude::*;
use std::io::stdin;

#[inline]
fn map(c: char) -> u8 {
    match c {
        'A' | 'E'..='H' | 'K' | 'M'..='N' => 3,
        'B' | 'D' | 'P'..='R' | 'T' | 'W'..='Y' => 2,
        'C' | 'I'..='J' | 'L' | 'O' | 'S' | 'U'..='V' | 'Z' => 1,
        _ => 0,
    }
}

#[inline]
fn add(a: u8, b: u8) -> u8 {
    (a + b) % 10
}

fn main() {
    let mut scoreboard: Vec<u8> = {
        let mut input = stdin().lock();
        let mut line = String::new();

        input.read_line(&mut line).unwrap();
        line.trim_end().chars().map(map).collect()
    };

    while scoreboard.len() > 1 {
        scoreboard = scoreboard
            .chunks(2)
            .map(|v| match v.len() {
                1 => v[0],
                _ => add(v[0], v[1]),
            })
            .collect()
    }

    match scoreboard[0] % 2 {
        1 => {
            println!("I'm a winner!");
        }
        _ => {
            println!("You're the winner?");
        }
    }
}
