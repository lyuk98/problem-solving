use std::io::prelude::*;
use std::io::stdin;

fn squares(sheet: &Vec<Vec<bool>>, (r, c): (usize, usize), size: usize) -> (u16, u16) {
    if size < 2 {
        return match sheet[r][c] {
            false => (1, 0),
            true => (0, 1),
        };
    }

    let half = size / 2;
    let (tl, tr, bl, br) = (
        squares(sheet, (r, c), half),
        squares(sheet, (r, c + half), half),
        squares(sheet, (r + half, c), half),
        squares(sheet, (r + half, c + half), half),
    );
    let (white, blue) = (
        tl.0 + tr.0 + bl.0 + br.0,
        tl.1 + tr.1 + bl.1 + br.1
    );

    if white == 0 {
        return (0, 1);
    }
    else if blue == 0 {
        return (1, 0);
    }

    (white, blue)
}

fn main() {
    let mut lines = stdin().lock().lines().map(|l| l.unwrap());

    let n = lines.next().unwrap().parse::<usize>().unwrap();
    let sheet: Vec<Vec<bool>> = lines
        .map(|l| l.split_whitespace().map(|t| t != "0").collect())
        .take(n)
        .collect();

    let (white, blue) = squares(&sheet, (0, 0), n);

    print!("{}\n{}\n", white, blue);
}
