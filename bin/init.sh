#!/bin/bash

set -eu
DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
INCLUDE_DIR=${DIR}/../include
LIB_DIR=${DIR}/../lib

cd ${TMPDIR:-/tmp}
gcc -c ${INCLUDE_DIR}/error{,log}.c
ar cr libapue.a error{,log}.o
mv libapue.a ${LIB_DIR}
