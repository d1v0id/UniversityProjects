#!/bin/sh
./fast_mm/kr_fast_mm 6 > fast_mm.log
./gen_mm/kr_gen_mm 6 > gen_mm.log
diff fast_mm.log gen_mm.log

