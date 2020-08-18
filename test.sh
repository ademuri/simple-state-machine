#!/bin/bash

set -euo pipefail

mkdir -p build
pushd build
cmake ..
make
# TODO: actually run tests
popd

