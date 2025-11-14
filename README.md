# problem-solving

This repository contains solutions for problems found across multiple code-learning platforms.

## Try running the code

The solutions here can be built and run using [Nix](https://nixos.org/ "Nix & NixOS | Declarative builds and deployments"). A recent version with [experimental features](https://nix.dev/manual/nix/latest/contributing/experimental-features) `flakes` and `nix-command` enabled is needed.

This repository does not need to be cloned. To run the code, do the following:

```sh
nix run github:lyuk98/problem-solving#[coder].[platform].[problem].[language]
```

where `[coder]`, `[platform]`, `[problem]`, and `[language]` represent the author, programming platform, problem number, and the source language, respectively. Possible values are as follows:

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

Note: code for platform LeetCode cannot be run because it lacks the `main()` method.

The packages' names can be found by using `nix repl`:

```sh
nix repl
:lf github:lyuk98/problem-solving
builtins.attrNames outputs.packages.x86_64-linux
```

### Example

The following is an example of running the solution for a problem:

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
