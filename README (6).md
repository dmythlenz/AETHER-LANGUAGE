# Benchmarks

`bootstrap/cpp/build/aether_benchmark` performs 1,000,000 deterministic VM calls to a two-integer AETHER `add` function.

A sample run in the validation container produced approximately 1064 ms wall time. This is a **local engineering smoke benchmark**, not a language-vs-language performance claim. Re-run on the target machine and publish machine/toolchain details for any comparative result.
