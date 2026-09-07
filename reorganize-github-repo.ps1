$ErrorActionPreference = 'Stop'
# Run from the root of the existing AETHER-LANGUAGE repository.
New-Item -ItemType Directory -Force language, compiler, runtime, apps, kernel | Out-Null

git mv 'Aether Language Library.ae' 'std/Aether Language Library.ae'
git mv 'KAE-SYSTEM Aether Compiler.ae' compiler/
git mv 'KAE-SYSTEM Aether.ae' runtime/
git mv 'KAE-SYSTEM-kernel.wasm' kernel/
git mv 'aether-syntax.json' language/
git mv 'AETHER Core.html' apps/
git mv 'Aether Workshop.html' apps/
git mv 'Aether os.html' apps/
git mv 'Dmyth Aather.html' apps/
Write-Host 'Moved core artifacts. Update relative URLs/import paths in HTML/docs before commit.'
Write-Host "Run: git grep -nE 'KAE-SYSTEM|Aether Language Library|aether-syntax|AETHER Core|Aether Workshop|Aether os|Dmyth Aather'"
