import numpy as np
import time
arr1 = np.random.rand(5000, 256)
arr2 = np.random.rand(5000, 256)
t0 = time.time()
res = np.dot(arr1, arr2.transpose())
t1 = time.time()
print("numpy get distance take {}".format(t1 - t0))