import random
import time
base_id='aegean_suzhou_wujiang-ch10018-fid-track-301005-af332754-c015-48cc-92f9-931695600311'

tids=set()
for i in range(0, 30000000):
    tids.add('aegean_suzhou_wujiang-ch{}-fid-track-{}-af332754-c015-48cc-92f9-93{}'.format(random.randint(0, 1000), random.randint(0, 10000), random.randint(100000000, 200000000)))


t0=time.time()
new_tids=set()
for i in range(0, 1000000):
    tid='aegean_suzhou_wujiang-ch{}-fid-track-{}-af332754-c015-48cc-92f9-93{}'.format(random.randint(0, 1000), random.randint(0, 10000), random.randint(100000000, 200000000))
    if tid not in tids:
        continue
    new_tids.add(tid)
t1=time.time()

print("total {}".format(t1 - t0))