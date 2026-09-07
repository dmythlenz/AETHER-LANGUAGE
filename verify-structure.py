from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
required = [
    'language','compiler','runtime','std','ai','game','os','web',
    'targets','tooling','tests','docs','examples','apps','kernel','compat','build','scripts'
]
missing = [d for d in required if not (ROOT/d).is_dir()]
if missing:
    raise SystemExit('MISSING DIRECTORIES: ' + ', '.join(missing))
for f in ['project.ae','README.md','LICENSE','language/TYPES-SEMANTICS.ae','compiler/AETHER-COMPILER-CONTRACT.ae','tests/AETHER-CONFORMANCE.ae']:
    if not (ROOT/f).is_file():
        raise SystemExit('MISSING FILE: ' + f)
print('AETHER structure: PASS')
print('Canonical directories:', len(required))
print('Required files: PASS')
