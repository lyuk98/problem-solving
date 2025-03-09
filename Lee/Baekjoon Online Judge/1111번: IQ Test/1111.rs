use std::io::prelude::*;
use std::io::stdin;
use std::iter::once;
use std::iter::zip;

fn main() {
    let mut lines = stdin().lock().lines().map(|l| l.unwrap());

    let n = lines.next().unwrap().parse::<usize>().unwrap();

    let p = lines.next().unwrap();
    let mut p = p.split_whitespace().map(|t| t.parse::<i32>().unwrap());

    if n == 1 {
        println!("A");
    } else if n == 2 {
        let (f, s) = (p.next().unwrap(), p.next().unwrap());

        match f == s {
            true => {
                println!("{}", f);
            }
            false => {
                println!("A");
            }
        };
    } else {
        let (f, s, t) = (p.next().unwrap(), p.next().unwrap(), p.next().unwrap());

        let numerator = s - t;
        let denominator = f - s;

        if denominator != 0 && numerator % denominator != 0 {
            println!("B");
        } else {
            let a = match denominator {
                0 => 1,
                _ => numerator / denominator,
            };
            let b = s - f * a;

            let p = once(f).chain(once(s)).chain(once(t)).chain(p);

            let last = p.clone().last().unwrap();
            let mut p = zip(p.clone(), p.skip(1));

            match p.any(|(current, next)| current * a + b != next) {
                true => {
                    println!("B");
                }
                false => {
                    println!("{}", last * a + b);
                }
            }
        }
    }
}
