# AETHER Reference v7

## Status

AETHER v7 defines a small, deterministic language core and a compatibility boundary around the historical AETHER/KAE runtime.

The **standalone bootstrap compiler** in `bootstrap/cpp` implements the following executable core today:

- identifiers and integer literals
- strings in the parser/runtime
- unary negation
- binary arithmetic and comparisons
- function declarations using `fn name(a,b) -> expression`
- function calls in the interpreter/WAT path
- deterministic line/column diagnostics

The historical runtime remains richer. Features such as structs, classes, collections, tensors, pattern matching, modules, `try/catch`, and domain engines are preserved as compatibility/runtime layers and are not falsely claimed as native-backend parity in v7.

## Evaluation

The standalone core is call-by-value and left-to-right. Function arguments are evaluated before function entry. Integer arithmetic is signed 64-bit in the bootstrap implementation.

## Errors

Lexer, parser and runtime errors carry source line and column information. Division by zero is a runtime error.

## Backends

The bootstrap compiler currently emits:

- executable native x86-64 System V assembly for the integer expression subset
- WebAssembly Text (WAT) for the same subset
- an interpreter VM for deterministic execution and reference behavior

A future native linker/assembler driver can consume the emitted assembly. Platform-specific SDKs, GPU APIs and mobile packaging remain explicit adapters.
