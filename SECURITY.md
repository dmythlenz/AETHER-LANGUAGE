# AETHER Security Model

1. No ambient device access in portable domain logic.
2. Capabilities are explicit and inspectable.
3. Network/storage/device requests cross a named adapter boundary.
4. Web/LLM code executes in a constrained AETHER capability context.
5. Package resolution uses exact versions and lockfiles.
6. Cryptographic functions provided by the host must be addressed through documented capabilities; do not invent cryptographic guarantees in source-only contracts.
