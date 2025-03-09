use std::io::prelude::*;
use std::io::stdin;

fn is_available(col: &Vec<usize>, row: usize) -> bool {
    for i in 1..row {
        if col[i] == col[row] || (row - i) == col[row].abs_diff(col[i]) {
            return false;
        }
    }

    true
}

fn set_queen(n: usize, col: &mut Vec<usize>, row: usize, ans: &mut usize) {
    if !is_available(col, row - 1) {
        return;
    }

    if row > n {
        *ans += 1;
        return;
    }

    for c in 1..=n {
        col[row] = c;
        set_queen(n, col, row + 1, ans);
    }
}

fn n_queen(n: usize) -> usize {
    let mut col: Vec<usize> = vec![0; n + 1];
    let mut count: usize = 0;

    set_queen(n, &mut col, 1, &mut count);

    count
}

fn main() {
    let n = stdin()
        .lock()
        .lines()
        .next()
        .unwrap()
        .unwrap()
        .parse::<usize>()
        .unwrap();
    println!("{}", n_queen(n));
}
