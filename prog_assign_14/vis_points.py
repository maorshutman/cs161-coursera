import numpy as np
import matplotlib.pyplot as plt

filepath = 'tsp.txt'
with open(filepath) as fp:
	line = int(fp.readline())
	n = int(line)
	pts = np.zeros((n, 2))
	for i in range(n):
		line = fp.readline()
		floats = [float(x) for x in line.split()]
		pts[i] = floats
print(pts)
print(pts.shape)

fig, ax = plt.subplots()
ax.scatter(pts[:, 0], pts[:, 1])
for i in range(pts.shape[0]):
    ax.annotate(i, (pts[i, 0], pts[i, 1]))
plt.show()
