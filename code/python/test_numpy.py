import matplotlib.pyplot as plt

# create

np.zeros((2, 4))
np.ones((3, 4))
np.empty((2, 3))
np.arange(6)
np.full((2, 2), 3)
np.eye(3, 3)
np.linspace(0, 10, num=4)
np.random.random((2, 2))

#
# 1D Array

a = np.array([0, 1, 2, 3, 4])
b = np.array((0, 1, 2, 3, 4))
c = np.arange(5)
d = np.linspace(0, 2*np.pi, 5)

print(a)  # >>>[0 1 2 3 4]
print(b)  # >>>[0 1 2 3 4]
print(c)  # >>>[0 1 2 3 4]
print(d)  # >>>[ 0.          1.57079633  3.14159265  4.71238898  6.28318531]
print(a[3])  # >>>3

# Array properties
a = np.array([[11, 12, 13, 14, 15],
              [16, 17, 18, 19, 20],
              [21, 22, 23, 24, 25],
              [26, 27, 28, 29, 30],
              [31, 32, 33, 34, 35]])

print(type(a))  # >>><class 'numpy.ndarray'>
print(a.dtype)  # >>>int64
print(a.size)  # >>>25
print(a.shape)  # >>>(5, 5)
print(a.itemsize)  # >>>8
print(a.ndim)  # >>>2
print(a.nbytes)  # >>>200

# Basic Operators
a = np.arange(25)
a = a.reshape((5, 5))

b = np.array([10, 62, 1, 14, 2, 56, 79, 2, 1, 45,
              4, 92, 5, 55, 63, 43, 35, 6, 53, 24,
              56, 3, 56, 44, 78])
b = b.reshape((5, 5))

print(a + b)
print(a - b)
print(a * b)
print(a / b)
print(a ** 2)
print(a < b) print(a > b)

print(a.dot(b))


# dot, sum, min, max, cumsum
a = np.arange(10)

print(a.sum())  # >>>45
print(a.min())  # >>>0
print(a.max())  # >>>9
print(a.cumsum())  # >>>[ 0  1  3  6 10 15 21 28 36 45]


# Fancy indexing
a = np.arange(0, 100, 10)
indices = [1, 5, -1]
b = a[indices]
print(a)  # >>>[ 0 10 20 30 40 50 60 70 80 90]
print(b)  # >>>[10 50 90]

# contatenate
a = np.arange(3).reshape(3, 1)
# array([[0],
#        [1],
#        [2]])
np.contatenate([a, a], axis=0)
np.vstack([a, a])
np.r_[a, a]
# array([[0],
#        [1],
#        [2],
#        [0],
#        [1],
#        [2]])
np.contatenate([a, a], axis=1)
np.hstack([a, a])
np.c_[a, a]
# array([[0, 0],
#        [1, 1],
#        [2, 2]])

# Boolean masking

a = np.linspace(0, 2 * np.pi, 50)
b = np.sin(a)
plt.plot(a, b)
mask = b >= 0
plt.plot(a[mask], b[mask], 'bo')
mask = (b >= 0) & (a <= np.pi / 2)
plt.plot(a[mask], b[mask], 'go')
plt.show()

# Incomplete Indexing
a = np.arange(0, 100, 10)
b = a[:5]
c = a[a >= 50]
print(b)  # >>>[ 0 10 20 30 40]
print(c)  # >>>[50 60 70 80 90]

# Where
a = np.arange(0, 100, 10)
b = np.where(a < 50)
c = np.where(a >= 50)[0]
print(b)  # >>>(array([0, 1, 2, 3, 4]),)
print(c)  # >>>[5 6 7 8 9]

# solve equation
A = np.array([[2, 1, -2], [3, 0, 1], [1, 1, -1]])
b = np.transpose(np.array([[-3, 5, -2]]))
x = np.linalg.solve(A, b)
