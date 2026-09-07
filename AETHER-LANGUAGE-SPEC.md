# AETHER Language Specification — v5

## 1. Lexical model
AETHER source is Unicode text. Whitespace is significant where the active parser defines blocks. `#` begins a line comment. Strings use the syntax accepted by the current AetherLang parser.

## 2. Values
The core runtime admits numbers, booleans, strings, lists/arrays and dictionaries/objects, plus runtime values defined by the host engine. Composite application values are represented structurally.

## 3. Scope
Bindings are lexically scoped. A child block resolves names through its parent environment. `let` creates bindings; `mut` marks mutable local state. Functions close over their lexical environment.

## 4. Evaluation
Expressions use call-by-value, left-to-right evaluation. Function arguments are evaluated before invocation. Mutation is explicit.

## 5. Errors
AETHER supports the existing runtime `try/catch` surface. Platform-neutral libraries should prefer `{ok,value,code,message}` Result values for recoverable boundaries.

## 6. Concurrency
Actors, channels and dataflow graphs are modeled as explicit state machines. Deterministic implementations provide stable ordering for reproducible tests; parallel host backends may execute independent work concurrently.

## 7. Types
The runtime is structurally typed at the universal layer. v5 adds explicit semantic contracts for Number, String, Bool, List, Dict, Any, unions, generics and function signatures. Static rejection is a compiler responsibility; runtime contracts remain available in the interpreter.

## 8. Effects and capabilities
Filesystem, network, GPU, device and host services require explicit capability declarations. Domain logic should not access ambient host state directly.

## 9. Modules
Modules export AETHER functions/data and declare stable names. Package identity uses AEP/1 manifests and AEP-LOCK/1 lockfiles.

## 10. FFI
Foreign symbols use `AETHER-FFI/1` declarations. The ABI boundary defines symbol name, signature, library/adapter, capability and ownership semantics.

## 11. Compiler pipeline
`source → tokens → parser AST → semantic analysis → AETHER-IR → optimization → target backend`. The existing AetherLang parser remains authoritative until a production bootstrap compiler replaces it.

## 12. Determinism
Stable IDs, stable ordering, explicit clocks and content-addressed snapshots are preferred for reproducible builds and simulations.
