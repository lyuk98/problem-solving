use std::clone::Clone;
use std::cmp::{Eq, Ord, Ordering, PartialEq, PartialOrd};
use std::collections::HashMap;
use std::io::prelude::*;
use std::io::{stdin, stdout};
use std::marker::Copy;

#[derive(Copy, Clone)]
struct Entry {
    number: u32,
    frequency: u16,
    position: usize,
}

impl Ord for Entry {
    fn cmp(&self, other: &Self) -> Ordering {
        (other.frequency, self.position).cmp(&(self.frequency, other.position))
    }
}

impl PartialOrd for Entry {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl PartialEq for Entry {
    fn eq(&self, other: &Self) -> bool {
        (self.number, self.frequency) == (other.number, other.frequency)
    }
}

impl Eq for Entry {}

fn main() {
    let mut input = stdin().lock();
    let mut output = stdout().lock();

    let (_n, _c) = {
        let mut line = String::new();
        input.read_line(&mut line).unwrap();

        let mut i = line.split_whitespace();
        (
            i.next().unwrap().parse::<u16>().unwrap(),
            i.next().unwrap().parse::<u32>().unwrap(),
        )
    };

    let mut messages = String::new();
    input.read_line(&mut messages).unwrap();

    let messages = messages
        .split_whitespace()
        .map(|word| word.parse::<u32>().unwrap());

    let mut entries: HashMap<u32, Entry> = HashMap::new();

    for (i, value) in messages.enumerate() {
        if let Some(entry) = entries.get_mut(&value) {
            entry.frequency += 1;
        } else {
            entries.insert(
                value,
                Entry {
                    number: value,
                    frequency: 1,
                    position: i,
                },
            );
        }
    }

    let mut messages: Vec<Entry> = entries.values().copied().collect();
    messages.sort_unstable();

    for entry in messages {
        for _ in 1..=entry.frequency {
            write!(output, "{} ", entry.number).unwrap();
        }
    }
    writeln!(output).unwrap();
}
