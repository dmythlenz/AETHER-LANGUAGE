# AETHER Memory Model

The universal layer treats memory as explicit runtime state. `HyperFS` and virtual memory services are host/runtime facilities. v5 does not pretend to define a low-level allocator ABI for every target; the kernel/target layer owns physical allocation policy. Applications use structured values, stores, snapshots and explicit resource reservations.
