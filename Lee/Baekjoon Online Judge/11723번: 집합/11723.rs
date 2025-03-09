use std::io::prelude::*;
use std::io::{stdin, stdout, BufWriter};

fn main() {
    let mut lines = stdin().lock().lines().map(|l| l.unwrap());
    let mut output = BufWriter::new(stdout().lock());

    let m: u32 = lines.next().unwrap().parse().unwrap();
    let mut s: u32 = 0;

    for _ in 0..m {
        let line = lines.next().unwrap();
        let (operator, i) = {
            let mut i = line.split_whitespace();
            (
                i.next().unwrap(),
                i.next().map(|t| t.parse::<u8>().unwrap()),
            )
        };

        match operator {
            "add" => {
                s |= 1 << i.unwrap();
            }
            "remove" => {
                s &= !(1 << i.unwrap());
            }
            "check" => match s & (1 << i.unwrap()) {
                0 => {
                    writeln!(output, "{}", 0).unwrap();
                }
                _ => {
                    writeln!(output, "{}", 1).unwrap();
                }
            },
            "toggle" => {
                s ^= 1 << i.unwrap();
            }
            "all" => {
                s = 0b111111111111111111111;
            }
            "empty" => {
                s = 0;
            }
            &_ => {}
        };
    }
}
