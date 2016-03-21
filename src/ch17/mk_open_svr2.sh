#!/bin/bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cp "${DIR}/prog_17_17.c" "${DIR}/../../include/open.h"
cp "${DIR}/prog_17_26.c" "${DIR}/../../include/opend.h"

gcc -Wall -lapue -o open_svr_client2 prog_17_18.c prog_17_25.c prog_17_10.c
gcc -Wall -lapue -o opend2 prog_17_28.c prog_17_27.c prog_17_29.c prog_17_31.c prog_17_8.c prog_17_9.c prog_17_23.c prog_17_24.c
# or we can use prog_17_30.c instead of 29
