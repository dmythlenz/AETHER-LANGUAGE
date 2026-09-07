# Standalone AETHER bootstrap implementation

This is the first independent systems-language implementation included in the canonical repository. It is deliberately small and testable rather than pretending to implement the entire historical runtime.

It currently provides a useful integer-expression subset of AETHER with:
- standalone lexer/parser
- AST
- interpreter VM
- deterministic diagnostics
- source formatter for the supported subset
- WebAssembly text (WAT) backend for the supported subset
- x86-64 System V assembly backend for the supported integer subset
- CMake build and CTest smoke tests

This is a real implementation, not a contract file. It is not yet a complete replacement for the browser/KAE runtime and does not claim complete language parity.
