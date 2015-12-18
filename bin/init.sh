#!/bin/bash

set -eu
DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
INCLUDE_DIR=${DIR}/../include
LIB_DIR=${DIR}/../lib

TMP_DIR="${TMPDIR:-/tmp}/APUE_compile_$(uuidgen)"
echo "tmpdir is ${TMP_DIR}" >&2
mkdir ${TMP_DIR}
cd ${TMP_DIR}
for file in ${INCLUDE_DIR}/*.c
do
  gcc -c "${file}"
done

ar cr libapue.a *.o
mv libapue.a ${LIB_DIR}
