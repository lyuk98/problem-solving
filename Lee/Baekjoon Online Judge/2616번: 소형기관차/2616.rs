use std::{
    io::{BufRead, stdin},
    iter::{once, zip},
};

fn main() {
    let mut lines = stdin().lock().lines().map(|l| l.unwrap());

    let _cars: usize = lines.next().unwrap().parse().unwrap();
    let passengers: Vec<u32> = {
        let line = lines.next().unwrap();
        line.split_whitespace()
            .map(|t| t.parse().unwrap())
            .collect()
    };
    let limit: usize = lines.next().unwrap().parse().unwrap();

    let sum = passengers.iter().scan(0, |state, &n| {
        *state += n;
        Some(*state)
    });
    let window = zip(sum.clone().skip(limit - 1), once(0u32).chain(sum.clone()))
        .map(|(keep, discard)| keep - discard);

    let accumulator = |state: &mut u32, (previous, n): (u32, u32)| {
        *state = (n + previous).max(*state);
        Some(*state)
    };

    let car1 = window.clone().scan(0u32, |state, n| {
        *state = n.max(*state);
        Some(*state)
    });
    let car2 = zip(car1, window.clone().skip(limit)).scan(0u32, accumulator);
    let car3 = zip(car2, window.clone().skip(limit * 2)).scan(0u32, accumulator);

    println!("{}", car3.last().unwrap());
}
