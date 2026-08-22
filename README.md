# AETHER — Core Language & Runtime

[![Release](https://img.shields.io/badge/release-v1.0.0--final-blue.svg)](https://github.com/dmythlenz/AETHER-LANGUAGE)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

TL;DR

AETHER is an experimental, host‑agnostic programming language and runtime (v1.0.0‑final). It ships as a single-file reference implementation that you can open in a browser or run from Node.js for exploration. AETHER includes:

- A small interpreted language surface ("Omega").
- A hierarchical in-memory filesystem (FS).
- A universal "pixel" store to ingest any content (files, images, video, 3D, animation, LLM sessions).
- Media helpers, a virtual hardware (VHW) simulation rack, basic quantum/continuum stubs, and utility libraries for data and automation.

Why this repo

This repo is a compact, runnable reference implementation intended for experimentation and demos. It's intentionally self-contained so you can open the HTML file in a browser and interact with the runtime UI immediately.

Highlights / Features

- Language: let/mut/const, fn, structs, classes, pattern matching, control flow (if/while/for), try/catch, modules and imports.
- Pixel fabric: ingest arbitrary content into a searchable store (kinds include file/image/video/3d/animation/game/llm/app/code/text).
- Hierarchical FS: create/read/write/list/tree/scan/remove files and folders entirely in-memory.
- Media: image/animation/video/scene helpers and fast conversions into the pixel fabric.
- VHW: a simulated virtual hardware rack (vGPU, vTPU, vRAM, vPhoton, etc.) for resource accounting and demo scripts.
- Utilities: DataFrame helpers, actor mailboxes, DAG runner, RAG/CAG stubs, WASM helpers, simple quantum primitives, and more.

Quick start

1. Browser (recommended for exploration)
   - Open `AETHER Core.html` (or `AETHER Core v1.0.0 FINAL (1).html`) in a modern browser.
   - Use the interactive UI: edit code in the editor and Run → inspect output in the right panel.

2. Node.js (>=18) — embedding the core file
   - The repository provides a single-file runtime; to run parts in Node you can require or eval the script from a small runner.

   Example runner (sketch):

   ```js
   // run-aether.js (example)
   const fs = require('fs');
   const src = fs.readFileSync('AETHER Core.html', 'utf8');
   // extract the <script> content or adapt the single-file script for Node usage
   // then evaluate / run the interpreter parts you need.
   ```

Examples (interpreter built-ins)

Open the runtime console (in-browser) or call from the interpreter API. A few quick commands:

- Files & Pixel fabric
  - fs_write('/example.txt', 'hello world')
  - fs_read('/example.txt')
  - fs_to_pixel('/example.txt')  // returns a pixel hash
  - px_get('<hash>')

- Images & Animation
  - img_create('img1', 128, 128)
  - img_to_pixel('img1')
  - anim_create('anim1', 24, 60)
  - anim_add_track('anim1', 'position', [{t:0,x:0},{t:1,x:10}])

- System / Status
  - fs_tree('/')
  - fs_stats()
  - px_stats()
  - package_info()
  - mind_status()

API reference (selected built-ins)

- FS: fs_mkdir, fs_write, fs_read, fs_exists, fs_isdir, fs_isfile, fs_list, fs_tree, fs_scan, fs_remove, fs_download, fs_to_pixel, fs_stats
- Pixel: px_store, px_get, px_search, px_ingest, px_stats
- Image/Anim: img_create, img_info, img_to_pixel, anim_create, anim_add_track, anim_to_pixel
- Media: video_create, video_info, video_to_pixel, scene_create, scene_add_mesh, scene_to_pixel
- VHW: vhw_compute, vhw_attend, vhw_alloc, vhw_store, vhw_send, vhw_scrape, vhw_fabric, vhw_guard, vhw_quantum, vhw_logic, vhw_photon, vhw_stat
- Utilities: lib_gcd, lib_fib, lib_factorial, lib_is_prime, df_create, df_select, actor_spawn, dag_create, rag_add, rag_generate, wasm_emit_wat, qreg, qprob

Files in this repository

- AETHER Core.html — main single-file interactive runtime (open in browser)
- AETHER Core v1.0.0 FINAL (1).html — alternate copy (reference)
- README.md — this file

Contributing

This repository is experimental and aims to be easy to iterate on. Suggested contribution guidelines:

- Open an issue to describe the feature or bug.
- Small, focused PRs are preferred.
- When adding new runtime features, include a short example (in the examples/ folder or README) demonstrating the behavior.

License

This project is provided under the MIT license unless otherwise specified. If you want an explicit LICENSE file added to the repo I can add the standard MIT template for you.

Contact

Repo owner: @dmythlenz

---

If you'd like, I can also:

- Add a LICENSE (MIT) file.
- Add an "examples/" folder with runnable interpreter snippets (fs/pixel/image).
- Shorten or expand any section and add badges (CI, code coverage) if you plan to add automated tests.

Tell me which improvements you want next and I'll apply them.