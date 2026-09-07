# AETHER wasm target

This directory contains the target boundary for wasm. The language/runtime remains host-agnostic; platform SDKs, linkers, drivers, and signing toolchains are adapters at this boundary.
# AETHER Language

**Standalone. Host-agnostic. No browser required.**

AETHER is an experimental programming language with a working standalone bootstrap compiler.

Version: **7.1.0-standalone**

---

## Status

| Component                    | Status                          |
|-----------------------------|---------------------------------|
| Standalone CLI (`aetherc`)  | Working                         |
| Lexer + Parser              | Working                         |
| Interpreter / VM            | Working                         |
| x86-64 native backend       | Working (calls, recursion, if)  |
| WebAssembly Text backend   | Working (basic)                 |
| Formatter                   | Working                         |
| Self-hosting proof          | Working (16/16 tests passed)    |
| HTML / JS dependency        | **None**                        |

---

## Quick Start

```bash
# Build
cmake -S . -B build
cmake --build build --parallel

# Run
./build/aetherc version
./build/aetherc run tests/smoke.ae fact 5
./build/aetherc run tests/smoke.ae fib 10
./build/aetherc run selfhost/meta_eval.ae main
```

Expected output:

```
aetherc 7.1.0-standalone
120
55
0
```

---

## Commands

```bash
aetherc version                 # print version
aetherc check  <file.ae>        # parse + validate
aetherc run    <file.ae> <fn> [args...]
aetherc asm    <file.ae>        # emit x86-64 assembly
aetherc wat    <file.ae>        # emit WebAssembly Text
aetherc fmt    <file.ae>        # format source
```

---

## Native Backend Test

```bash
./build/aetherc asm tests/smoke.ae > /tmp/aether.s
as /tmp/aether.s -o /tmp/aether.o
cc tests/native_smoke.c /tmp/aether.o -o /tmp/aether-native
./tmp/aether-native
```

Expected: `native backend: PASS`

---

## Language Subset (Current)

**Supported**

- Functions: `fn name(params) -> expr`
- Integers & booleans
- Arithmetic: `+ - * / %`
- Comparison: `== != < <= > >=`
- Unary `-`
- `if` expressions
- Function calls & recursion
- Simple `let` / `return`

**Not yet supported**

- Full language surface (tensors, agents, etc.)
- Complete self-hosting (compiler written in AETHER)
- Native floating-point / strings
- Closures & GC
- Standard library

---

## Project Layout

```
├── CMakeLists.txt
├── LICENSE
├── README.md
├── VERSION
├── include/aether/aether.hpp
├── src/
│   ├── aether.cpp          # core (lexer, parser, VM, backends)
│   └── main.cpp            # CLI
├── tests/
│   ├── smoke.ae
│   └── native_smoke.c
└── selfhost/
    └── meta_eval.ae        # AETHER-in-AETHER proof
```

---

## Design Goals

1. **Standalone** — runs without browser or foreign runtime
2. **Honest** — claims match what actually executes
3. **Native** — real machine code generation
4. **Self-hosting path** — C++ is bootstrap only; goal is AETHER implementing AETHER

---

## License

MIT License. See [LICENSE](LICENSE).
