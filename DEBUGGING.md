# AETHER Debugging and Observability

The v5 contracts provide breakpoints, sessions, events and profiling data as AETHER values. A production editor or CLI may expose these through a Debug Adapter or LSP bridge. The deterministic event sequence is designed so a failing run can be replayed from its source, manifest, inputs and snapshot.
