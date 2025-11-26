# problem-solving

[![English](https://img.shields.io/badge/Language-English-blue.svg)](./README.md)
[![한국어](https://img.shields.io/badge/%EC%96%B8%EC%96%B4-%ED%95%9C%EA%B5%AD%EC%96%B4-green.svg)](./README.ko.md)

온라인 코딩 플랫폼의 풀이를 기록하는 저장소입니다.

## 코드 실행

이 저장소의 코드는 `flakes`와 `nix-command` [실험 기능](https://nix.dev/manual/nix/latest/contributing/experimental-features)이 활성화된 버전의 [Nix](https://nixos.org/ "Nix & NixOS | Declarative builds and deployments")를 사용하여 빌드하고 실행할 수 있습니다.

```sh
nix run github:lyuk98/problem-solving#[작성자]-[플랫폼]-[문제번호]-[언어]
```

`[작성자]`, `[플랫폼]`, `[문제번호]`, `[언어]`는 각각 코드 작성자, 코딩 플랫폼, 문제 번호와 프로그래밍 언어를 의미합니다. `[문제번호]`를 제외한 가능한 값은 아래에 기술되어 있습니다:

| `작성자` | 설명 |
| --- | --- |
| `lee` | [@lyuk98의 코드](./Lee) |
| `jinju` | [@oMFDOo의 코드](./Jinju) |

| `플랫폼` | 설명 |
| --- | --- |
| `boj` | [백준 온라인 저지](https://www.acmicpc.net/ "Baekjoon Online Judge") |

| `언어` | 설명 |
| --- | --- |
| `c` | C (C23) |
| `cpp` | C++ (C++23) |
| `java` | Java (21) |
| `rs` | Rust (2024) |

LeetCode의 풀이와 같이 `main()` 함수가 존재하지 않는 코드는 실행할 수 없습니다.

`nix repl`을 사용하면 실행 가능한 풀이를 확인할 수 있습니다:

```sh
nix repl
:lf github:lyuk98/problem-solving
builtins.attrNames outputs.packages.x86_64-linux
```

### 예시

아래의 예시는 백준 온라인 저지의 [5430번 문제(AC)](https://www.acmicpc.net/problem/5430 "5430번: AC")에 대한 C 언어로 작성한 풀이를 실행합니다:

```sh
# 예제 입력 준비
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

# 입력과 함께 풀이 실행
cat input | nix run github:lyuk98/problem-solving#lee-boj-5430-c
```
