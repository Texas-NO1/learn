#!/bin/bash
set -x
prof_begin=$1
prof_end=$2
jeprof --show_bytes --pdf --base=${prof_begin} ./build/server ${prof_end} > ./build/show.pdf