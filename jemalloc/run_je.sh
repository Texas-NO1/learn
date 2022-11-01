export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
export LD_PRELOAD=/usr/local/lib/libjemalloc.so.2
export MALLOC_CONF="dirty_decay_ms:0,muzzy_decay_ms:0,background_thread:true,prof:true,lg_prof_sample:0,prof_prefix:jeprof.out"
g++ jemalloc.cpp /usr/local/lib/libjemalloc.so.2
pid=`./a.out`
echo ${pid}
jeprof --show_bytes --pdf a.out jeprof.out.${pid}.0.m0.heap > res1.pdf
jeprof --show_bytes --pdf a.out jeprof.out.${pid}.1.m1.heap > res2.pdf
jeprof --show_bytes --pdf --base=jeprof.out.${pid}.0.m0.heap a.out jeprof.out.${pid}.1.m1.heap > show.pdf
# rm jeprof.out.${pid}.0.m0.heap jeprof.out.${pid}.1.m1.heap