use std::io::prelude::*;
use std::io::{stdin, stdout, StdoutLock};
use std::ops::RangeInclusive;

#[inline]
fn write_line(count: u8, text: &str, output: &mut StdoutLock) {
    for _ in 0..count {
        write!(output, "____").unwrap();
    }
    writeln!(output, "{}", text).unwrap();
}

fn answer(range: &mut RangeInclusive<u8>, output: &mut StdoutLock) {
    match range.next() {
        Some(count) => {
            write_line(count, "\"재귀함수가 뭔가요?\"", output);

            if !RangeInclusive::<u8>::is_empty(range) {
                write_line(
                    count,
                    "\"잘 들어보게. 옛날옛날 한 산 꼭대기에 이세상 모든 지식을 통달한 선인이 있었어.",
                    output
                );
                write_line(
                    count,
                    "마을 사람들은 모두 그 선인에게 수많은 질문을 했고, 모두 지혜롭게 대답해 주었지.",
                    output
                );
                write_line(
                    count,
                    "그의 답은 대부분 옳았다고 하네. 그런데 어느 날, 그 선인에게 한 선비가 찾아와서 물었어.\"",
                    output
                );

                answer(range, output);
            }
            else {
                write_line(
                    count,
                    "\"재귀함수는 자기 자신을 호출하는 함수라네\"",
                    output
                );
            }

            write_line(count, "라고 답변하였지.", output);
        },
        None => (),
    }
}

fn main() {
    let mut input = stdin().lock();
    let mut output = stdout().lock();

    let n = {
        let mut line = String::new();
        input.read_line(&mut line).unwrap();

        line.trim_end().parse::<u8>().unwrap()
    };

    writeln!(output, "어느 한 컴퓨터공학과 학생이 유명한 교수님을 찾아가 물었다.").unwrap();
    answer(&mut (0..=n), &mut output);
}
