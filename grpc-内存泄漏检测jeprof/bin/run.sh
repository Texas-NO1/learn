export MALLOC_CONF="dirty_decay_ms:0,muzzy_decay_ms:0,background_thread:true,prof:true,lg_prof_sample:0,prof_prefix:jeprof.out"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
./build/server