# Canonical AETHER-LANGUAGE tree

```text
AETHER-LANGUAGE/
├── project.ae
├── README.md
├── LICENSE
├── CHANGELOG.md
├── CONTRIBUTING.md
│
├── language/                 # Language definition; no platform-specific code
│   ├── TYPES-SEMANTICS.ae
│   ├── UNIVERSAL-CORE.ae
│   ├── UNIVERSAL.ae
│   ├── UNIVERSAL-ALL.ae
│   ├── MANIFEST.ae
│   └── aether-syntax.json
│
├── compiler/                # Frontend, semantic analysis, IR, FFI, optimizer
├── runtime/                 # Execution, scheduler, compatibility runtimes
├── std/                     # Canonical standard library
├── ai/                      # Tensor/LLM/agent/EGI layers
├── game/                    # ECS/graphics/game runtime contracts
├── os/                      # OS/kernel/resource contracts
├── web/                     # HTTP/full-stack application layer
├── targets/                 # ABI/backend boundaries: wasm/native/android/desktop/embedded
├── tooling/                 # CLI/pkg/fmt/lsp/debugger
├── tests/                   # Conformance, coverage, verification
├── docs/                    # Normative spec, tutorials, references
├── examples/                # Runnable user-facing examples
├── apps/                    # Browser/workbench/runtime UIs
├── kernel/                  # Binary kernels and target support artifacts
├── compat/                  # Legacy migration and compatibility maps
├── build/                   # Repository architecture/build metadata
└── scripts/                 # Maintainer migration/verification scripts
```

## Dependency rule

`language` is the lowest-level semantic layer.

`compiler` consumes `language`.

`runtime` implements execution contracts and may serve all domain modules.

`std` depends only on language/runtime contracts.

`ai`, `game`, `os`, and `web` depend on language/runtime/std contracts.

`targets` adapt runtime/compiler interfaces to a platform.

`apps` and `tooling` consume the public language/runtime/tooling interfaces.

No language semantics may import a target, browser UI, or domain-specific application module.
