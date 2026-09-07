# Module boundaries

Canonical dependency direction:

language -> compiler -> runtime -> targets
language -> std
runtime -> ai/game/os/web
apps -> tooling/language/runtime

target adapters may depend on runtime contracts, but language semantics never depend on a target.
Domain modules must not redefine compiler semantics or duplicate core data structures.
