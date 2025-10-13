use std::{
    io::{BufRead, stdin},
    iter::{repeat, repeat_n, zip},
};

fn mod_pow(mut base: u64, mut exp: u64, modulus: u64) -> u64 {
    let mut result = 1u64;
    while exp > 0u64 {
        if exp % 2u64 == 1u64 {
            result = result * base % modulus
        }
        base = base * base % modulus;
        exp >>= 1u64;
    }

    result
}

fn ntt(mut a: Vec<u64>, invert: bool, p: u64, g: u64) -> Vec<u64> {
    let n = a.len();

    {
        let mut j = 0usize;
        for i in 1..n {
            let mut bit = n >> 1;
            while j & bit != 0 {
                j ^= bit;
                bit >>= 1;
            }
            j ^= bit;

            if i < j {
                a.swap(i, j);
            }
        }
    }

    let len = repeat(()).scan(1u64, |state, _| {
        *state <<= 1u64;

        match *state <= n.try_into().unwrap() {
            true => Some(*state),
            false => None,
        }
    });
    for len in len {
        let wlen = match invert {
            true => mod_pow(g, (p - 1u64) - (p - 1u64) / len, p),
            false => mod_pow(g, (p - 1u64) / len, p),
        };

        let len = usize::try_from(len).unwrap();

        for i in (0usize..n).step_by(len) {
            let mut w = 1u64;

            for j in 0usize..len / 2usize {
                let u = a[i + j];
                let v = a[i + j + len / 2usize] * w % p;

                a[i + j] = (u + v) % p;
                a[i + j + len / 2usize] = (p + u - v) % p;
                w = w * wlen % p;
            }
        }
    }

    if invert {
        let n_inv = mod_pow(u64::try_from(n).unwrap(), p - 2u64, p);
        for i in a.iter_mut() {
            *i = *i * n_inv % p;
        }
    }

    a
}

fn multiply(mut a: Vec<u64>, mut b: Vec<u64>) -> Vec<u64> {
    const P: u64 = 998244353u64;
    const G: u64 = 3u64;

    let n = {
        let mut n = 1usize;
        while n < a.len() + b.len() {
            n <<= 1usize;
        }
        n
    };

    a.resize(n, Default::default());
    b.resize(n, Default::default());

    a = ntt(a, false, P, G);
    b = ntt(b, false, P, G);

    let c = zip(a.iter(), b.iter()).map(|(a, b)| a * b % P);
    ntt(c.collect(), true, P, G)
}

fn main() {
    let mut lines = stdin().lock().lines().map(|l| l.unwrap());

    let n: usize = lines.next().unwrap().parse().unwrap();

    let (x, y) = (lines.next().unwrap(), lines.next().unwrap());
    let (x, y) = {
        let (x, y) = (
            x.split_whitespace().map(|t| t.parse::<u64>().unwrap()),
            y.split_whitespace().map(|t| t.parse::<u64>().unwrap()),
        );
        (
            x.rev().chain(repeat_n(Default::default(), n)),
            y.clone().chain(y),
        )
    };

    println!(
        "{}",
        multiply(x.collect(), y.collect()).iter().max().unwrap()
    );
}
