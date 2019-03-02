import numpy as np

def opt_root(A, p, i, s):
	min_sp = 1000.0
	for r in range(i, i + s + 1):
		a1, a2 = 0.0, 0.0
		if i <= r - 1:
			a1 = A[i, r - 1]
		if r + 1 <= i + s:
			a2 = A[r + 1, i + s]
		a = a1 + a2
		if a < min_sp:
			min_sp = a
	
	sum_p = 0.0
	for k in range(i, i + s + 1):
		sum_p += p[k]
	min_sp += sum_p
	return min_sp

n = 7
p = np.array([0.2, 0.05, 0.17, 0.1, 0.2, 0.03, 0.25])
#p = np.array([0.05, 0.4, 0.08, 0.04, 0.1, 0.1, 0.23])

A = np.zeros((n, n))

for s in range(n):
	for i in range(n):
		if (i + s <= n - 1):
			A[i, i + s] = opt_root(A, p, i, s)
print(A)
