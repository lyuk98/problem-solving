# problem-solving

[![English](https://img.shields.io/badge/Language-English-green.svg)](./README.md)
[![한국어](https://img.shields.io/badge/%EC%96%B8%EC%96%B4-%ED%95%9C%EA%B5%AD%EC%96%B4-blue.svg)](./README.ko.md)

This repository contains solutions for problems found across multiple code-learning platforms.

## Try running the code

The solutions here can be built and run using [Nix](https://nixos.org/ "Nix & NixOS | Declarative builds and deployments"). A recent version with [experimental features](https://nix.dev/manual/nix/latest/contributing/experimental-features) `flakes` and `nix-command` enabled is needed.

This repository does not need to be cloned. To run the code, do the following:

```sh
nix run github:lyuk98/problem-solving#[coder].[platform].[problem].[language]
```

where `[coder]`, `[platform]`, `[problem]`, and `[language]` represent the author, programming platform, problem number, and the source language, respectively. Possible values, except `[problem]`, are as follows:

| `coder` | Description |
| --- | --- |
| `lee` | [Code written by @lyuk98](./Lee) |
| `jinju` | [Code written by @oMFDOo](./Jinju) |

| `platform` | Description |
| --- | --- |
| `boj` | [Baekjoon Online Judge](https://www.acmicpc.net/ "Baekjoon Online Judge") |

| `language` | Description |
| --- | --- |
| `c` | C (C23) |
| `cpp` | C++ (C++23) |
| `java` | Java (21) |
| `rs` | Rust (2024) |

Note: solutions that lack the `main()` method, such as the ones for LeetCode, cannot be run this way.

Possible solutions can be enumerated by using `nix repl`:

```sh
nix repl
:lf github:lyuk98/problem-solving
builtins.attrNames outputs.packages.x86_64-linux
```

### Example

The following is an example of running a solution written in C, for [problem 5430](https://www.acmicpc.net/problem/5430 "5430번: Integer Lists") from Baekjoon Online Judge:

```sh
# Prepare sample input
cat > input << EOF
4
RDD
4
[1,2,3,4]
DD
1
[42]
RRD
6
[1,1,2,3,5,8]
D
0
[]
EOF

# Run the solution with the input
cat input | nix run github:lyuk98/problem-solving#lee-boj-5430-c
```
