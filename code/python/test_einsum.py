import numpy as np
'''
Einstein notation是一个表达向量矩阵运算的优雅方式。
numpy,pytorch,tensorflow均有对应实现
'''

a = np.arange(6)
b = np.ones(6)
aa = a.reshape(2, 3)
bb = b.reshape(3, 2)

print("转置")
print(aa.T)
print(np.einsum('ij->ji', aa))

print("按列求和")
print(np.sum(aa, axis=0))
print(np.einsum('ij->j', aa))

print("按行求和")
print(np.sum(aa, axis=1))
print(np.einsum('ij->i', aa))

print("矩阵乘")
print(np.matmul(aa, bb))
print(np.einsum('ij,jk->ik', aa, bb))

print("矩阵向量乘")
print(aa.dot(b[0:3]))
print(np.einsum('ij,j->i', aa, b[0:3]))

print("向量内积")
print(np.inner(a, b))
print(np.einsum('i,i->', a, b))

print("向量外积")
print(np.outer(a, b))
print(np.einsum('i,j->ij', a, b))
