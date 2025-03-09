use std::io::prelude::*;
use std::io::stdin;

fn count(paper: &Vec<Vec<i8>>, (r, c): (usize, usize), n: usize) -> (u32, u32, u32) {
    if n < 2 {
        return match paper[r][c] {
            -1 => (1, 0, 0),
            0 => (0, 1, 0),
            1 => (0, 0, 1),
            _ => (0, 0, 0),
        };
    }

    let l = n / 3;
    let s = {
        let mut s: (u32, u32, u32) = (0, 0, 0);
        for i in 0..3 {
            for j in 0..3 {
                let add = count(paper, (r + l * i, c + l * j), l);

                s.0 += add.0;
                s.1 += add.1;
                s.2 += add.2;
            }
        }

        s
    };

    if s.0 == 9 && s.1 == 0 && s.2 == 0 {
        return (1, 0, 0);
    } else if s.0 == 0 && s.1 == 9 && s.2 == 0 {
        return (0, 1, 0);
    } else if s.0 == 0 && s.1 == 0 && s.2 == 9 {
        return (0, 0, 1);
    }

    s
}

fn main() {
    let mut lines = stdin().lock().lines().map(|l| l.unwrap());

    let n = lines.next().unwrap().parse::<usize>().unwrap();
    let paper: Vec<Vec<i8>> = lines
        .map(|l| {
            l.split_whitespace()
                .map(|t| t.parse::<i8>().unwrap())
                .take(n)
                .collect()
        })
        .take(n)
        .collect();

    let (n1, z, p1) = count(&paper, (0, 0), n);
    print!("{}\n{}\n{}\n", n1, z, p1);
}
