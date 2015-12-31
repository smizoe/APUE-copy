#!/bin/bash

set -eu
DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TMPLOCK="${TMPDIR:-/tmp}/templock"
gcc -o ex_14_1 -Wall -lapue ex_14_1.c
touch "${TMPLOCK}"

${DIR}/ex_14_1 r ${TMPLOCK} &
${DIR}/ex_14_1 w ${TMPLOCK} &
${DIR}/ex_14_1 r ${TMPLOCK} &
wait
