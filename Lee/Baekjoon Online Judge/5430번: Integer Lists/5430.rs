use std::collections::VecDeque;
use std::fmt::Display;
use std::io::prelude::*;
use std::io::{stdin, stdout, BufWriter};

fn print<T: Display, W: Write>(out: &mut BufWriter<W>, i: impl Iterator<Item = T>) {
    let mut i = i;

    if let Some(front) = i.next() {
        write!(out, "[{}", front).unwrap();
        for e in i {
            write!(out, ",{}", e).unwrap();
        }
        writeln!(out, "]").unwrap();
    } else {
        writeln!(out, "[]").unwrap();
    }
}

fn main() {
    let mut lines = stdin().lock().lines().map(|l| l.unwrap());
    let mut out = BufWriter::new(stdout().lock());

    let mut list: VecDeque<u8> = VecDeque::with_capacity(100_000);

    let t = lines.next().unwrap().parse::<u8>().unwrap();
    'case: for _ in 0..t {
        let op = lines.next().unwrap();
        let op = op.chars();

        lines.next();

        let l = lines.next().unwrap();
        let l = {
            let mut li = l.chars();
            li.next();
            li.next_back();

            li.as_str()
        };

        list.clear();
        list.extend(
            l.split(',')
                .skip_while(|t| t.is_empty())
                .map(|t| t.parse::<u8>().unwrap()),
        );

        let mut rev = false;
        for o in op {
            match o {
                'R' => {
                    rev = !rev;
                }
                'D' => {
                    if list.is_empty() {
                        writeln!(out, "error").unwrap();
                        continue 'case;
                    }

                    match rev {
                        true => {
                            list.pop_back();
                        }
                        false => {
                            list.pop_front();
                        }
                    };
                }
                _ => (),
            };
        }

        match rev {
            true => print(&mut out, list.iter().rev()),
            false => print(&mut out, list.iter()),
        };
    }
}
