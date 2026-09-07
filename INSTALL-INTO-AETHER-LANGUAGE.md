# Install / Integrate AETHER UNIVERSAL PLATFORM v5.0.0

Recommended layout inside the existing repository:

```text
AETHER-LANGUAGE/
  runtime/                         # existing AETHER runtime
  universal/                       # copy this package's Aether source modules
```

The canonical one-file source is:

`universal/AETHER-UNIVERSAL.ae`

The modular form is under `core/`, `compiler/`, `os/`, `game/`, `ai/`, `web/`, `targets/`, `tests/`, and `docs/`.

`runtime/AETHER-UNIVERSAL-FINAL-RUNTIME.html` is a browser host based on the user's existing Fusion v17 runtime and contains a smoke-test hook for the canonical core.

No external language is required for the domain logic. The physical execution boundary is intentionally represented by explicit adapter-required targets.
