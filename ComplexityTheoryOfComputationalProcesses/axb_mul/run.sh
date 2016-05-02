#!/usr/bin/zsh
GEN_MM=`(time ./gen_mm/kr_gen_mm $1) 2>&1 | awk '{ print $3 }'`
FAST_MM=`(time ./fast_mm/kr_fast_mm $1) 2>&1 | awk '{ print $3 }'`

echo "Generic mul: $GEN_MM"
echo "Fast mul: $FAST_MM"

