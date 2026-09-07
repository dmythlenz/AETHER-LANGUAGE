#!/usr/bin/env sh
set -eu
ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
BUILD="$ROOT/bootstrap/cpp/build"
if [ ! -x "$BUILD/aetherc" ]; then
  cmake -S "$ROOT/bootstrap/cpp" -B "$BUILD"
  cmake --build "$BUILD" --parallel
fi
exec "$BUILD/aetherc" "$@"
