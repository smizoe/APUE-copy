#!/bin/bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cp "${DIR}/prog_17_17.c" "${DIR}/../../include/open.h"
cp "${DIR}/prog_17_20.c" "${DIR}/../../include/opend.h"

gcc -Wall -lapue -o open_svr_client1 prog_17_18.c prog_17_19.c
gcc -Wall -lapue -o opend prog_17_21.c prog_17_22.c prog_17_23.c prog_17_24.c
