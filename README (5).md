# AETHER LANGUAGE — v7.0.0

AETHER is an experimental language/runtime platform. v7 is the engineering reset that makes the distinction between executable reality and architectural intent explicit.

## What is real in v7

- The historical browser/Node AETHER runtime is retained for compatibility.
- A standalone C++17 bootstrap compiler is included under `bootstrap/cpp`.
- The bootstrap implementation has a lexer, parser, interpreter VM, formatter, x86-64 System V assembly backend, and WAT backend for a defined integer-expression core.
- CMake + CTest builds and tests the standalone implementation.
- A native backend smoke test links generated assembly with C and executes it.

## What is intentionally not over-claimed

The historical repository exposes tensors, HyperFS, VHW, KAE, quantum primitives, actors/DAG, modules and other domain features. Those remain valuable AETHER runtime layers, but v7 does not claim that the standalone compiler already lowers every one of those features to native code.

Physical GPU drivers, OS kernels, Android SDK/signing, codec stacks and arbitrary external LLM weight execution are adapter boundaries.

## Recommended repository model

```text
AETHER-LANGUAGE/
├── language/      # language contracts and semantics
├── bootstrap/     # independent compiler implementation
├── compiler/      # AETHER-level compiler contracts/IR work
├── runtime/       # runtime implementations
├── std/           # standard library
├── tooling/       # CLI/tooling contracts
├── targets/       # platform targets/adapters
├── tests/         # conformance and regression tests
├── benchmarks/    # reproducible benchmark harnesses/results
├── docs/          # reference/specification/tutorials
├── ai/ game/ os/ web/  # domain layers
├── apps/ kernel/ compat/
└── scripts/
```

## Build standalone compiler

```sh
cmake -S bootstrap/cpp -B bootstrap/cpp/build
cmake --build bootstrap/cpp/build --parallel
ctest --test-dir bootstrap/cpp/build --output-on-failure
```

## CLI

```text
aetherc check file.ae
aetherc run file.ae function [integer args...]
aetherc fmt file.ae
aetherc wat file.ae
aetherc asm file.ae
```

## Status

This project is **experimental engineering software**, not a claim of highest-tier production maturity. The path to that status is measurable: complete compiler parity, multiple maintained implementations, reproducible benchmarks, working tooling, security review and independent adoption.
