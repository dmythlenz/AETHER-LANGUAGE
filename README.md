# AETHER — Core Language & Runtime

AETHER is an experimental, host-agnostic programming language and runtime (v1.0.0-final). It provides a small interpreted language surface ("Omega"), a hierarchical in-memory filesystem, a universal "pixel" store for ingesting arbitrary content, media and image helpers, virtual hardware primitives (VHW), and many convenience libraries for data processing, automation, and prototyping.

This repository contains a single-file reference implementation (AETHER Core) that can be opened in a browser or run in Node.js for exploration and testing.

## Highlights

- Language features: let/mut/const, fn, structs, classes, pattern match, control flow (if/while/for), try/catch, modules and imports.
- Pixel fabric: ingest arbitrary content (files, images, video, 3D, animation, LLM sessions) into a searchable store.
- Hierarchical in-memory FS: create/read/write/list/tree/scan files and folders without external dependencies.
- Media utilities: image/animation/video/scene helpers and pixelization.
- VHW: virtual hardware units (vGPU, vTPU, vRAM, vPhoton, etc.) for simulation and resource accounting.
- Utilities: small dataframe helpers, actor mailbox, DAG runner, RAG/CAG stubs, WASM helpers, quantum primitives, and more.

## Quick start

- Open `AETHER Core.html` or `AETHER Core v1.0.0 FINAL (1).html` in a modern browser to try the interactive single-file UI.
- Or run in Node.js (>=18) by embedding the core script into a small runner — this repo is primarily a reference single-file implementation.

Example usage (from the in-browser console or interpreter):

- Create a file and ingest into pixel fabric:
  - fs_write('/example.txt', 'hello world')
  - fs_to_pixel('/example.txt')

- Create an image and convert to pixel:
  - img_create('img1', 128, 128)
  - img_to_pixel('img1')

- Inspect FS tree:
  - fs_tree('/')

- Use built-in docs/help:
  - help('fs')
  - package_info()

## Files

- AETHER Core.html — main single-file interactive runtime
- AETHER Core v1.0.0 FINAL (1).html — alternate/minified copy (reference)
- README.md — this file

## Contributing

This project is experimental. Contributions, issues, and examples are welcome. Prefer small focused PRs and include examples when adding runtime features.

## License

MIT — see LICENSE (if present). If a license file is not provided, contact the repository owner for licensing terms.

## Contact

Repo owner: @dmythlenz

---

(README generated to provide a concise overview of the AETHER Core implementation and usage.)