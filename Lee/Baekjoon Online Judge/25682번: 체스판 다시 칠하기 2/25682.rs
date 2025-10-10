use std::io::{BufRead, stdin};

#[derive(Clone, Copy, Default)]
struct Fix {
    black: u32,
    white: u32,
}

fn main() {
    let mut lines = stdin().lock().lines().map(|l| l.unwrap());

    let (n, m, k) = {
        let line = lines.next().unwrap();
        let mut tokens = line.split_whitespace().map(|t| t.parse::<usize>().unwrap());

        (
            tokens.next().unwrap(),
            tokens.next().unwrap(),
            tokens.next().unwrap(),
        )
    };

    let fixes = {
        let board: Vec<Vec<bool>> = lines
            .map(|l| l.chars().map(|c| c == 'W').take(m).collect())
            .take(n)
            .collect();
        let mut fixes: Vec<Vec<Fix>> = vec![vec![Default::default(); m + 1]; n + 1];

        for i in 1..=n {
            for j in 1..=m {
                let c = board[i - 1][j - 1];
                let add = match (i + j) % 2 {
                    0 => match c {
                        false => (0u32, 1u32),
                        true => (1u32, 0u32),
                    },
                    _ => match c {
                        false => (1u32, 0u32),
                        true => (0u32, 1u32),
                    },
                };

                fixes[i][j] = Fix {
                    black: fixes[i - 1][j].black
                        + fixes[i][j - 1].black
                        - fixes[i - 1][j - 1].black
                        + add.0,
                    white: fixes[i - 1][j].white
                        + fixes[i][j - 1].white
                        - fixes[i - 1][j - 1].white
                        + add.1,
                };
            }
        }

        fixes
    };

    let min = {
        let mut min = u32::MAX;

        for i in k..=n {
            for j in k..=m {
                let fix = (
                    fixes[i][j].black - fixes[i - k][j].black - fixes[i][j - k].black
                        + fixes[i - k][j - k].black,
                    fixes[i][j].white - fixes[i - k][j].white - fixes[i][j - k].white
                        + fixes[i - k][j - k].white,
                );

                min = min.min(fix.0.min(fix.1));
            }
        }

        min
    };

    println!("{}", min);
}
