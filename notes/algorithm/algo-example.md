# 

# 栈

## 字符串返回去掉重复字母后的最小字典序子串
用栈来存储最终返回的字符串，并维持字符串的最小字典序。每遇到一个字符，如果这个字符不存在于栈中，就需要将该字符压入栈中。但在压入之前，需要先将之后还会出现，并且字典序比当前字符小的栈顶字符移除，然后再将当前字符压入。

```python
class Solution:
    def removeDuplicateLetters(self, s: str) -> str: 
        stack = [] 
        seen = set() 
        last_occurrence = {c: i for i, c in enumerate(s)} 
        for i, c in enumerate(s): 
            if c not in seen: 
                while stack and c < stack[-1] and i < last_occurrence[stack[-1]]:
                    seen.discard(stack.pop())
                seen.add(c)
                stack.append(c)
        return ''.join(stack)
```

# 回溯

## 全排列
```python
def backtrack(first = 0):
    # 所有数都填完了
    if first == n:  
        res.append(nums[:])
    for i in range(first, n):
        # 动态维护数组
        nums[first], nums[i] = nums[i], nums[first]
        # 继续递归填下一个数
        backtrack(first + 1)
        # 撤销操作
        nums[first], nums[i] = nums[i], nums[first]

n = len(nums)
res = []
backtrack()
return res
 
```

## 重复元素的全排列
```python
from typing import List
from itertools import permutations
class Solution:
    def permuteUnique(self, nums: List[int]) -> List[List[int]]:
        # # [1]
        # perms = [[]]
        # for n in nums:
        #     perms = [p[:i] + [n] + p[i:]
        #             for p in perms
        #             for i in range((p + [n]).index(n) + 1)] 
        #     print(perms)
        # return perms 
        # [one-line]
        # return reduce(lambda perms, n: [p[:i] + [n] + p[i:] for p in perms for i in xrange((p + [n]).index(n) + 1)], nums, [[]])

        # [2] backtrack
        nums.sort()
        self.res = []
        check = [0 for i in range(len(nums))] 
        self.backtrack([], nums, check)
        return self.res
        
    def backtrack(self, sol, nums, check):
        if len(sol) == len(nums):
            self.res.append(sol)
            return
        
        for i in range(len(nums)): # 剪枝
            if check[i] == 1:
                continue
            if i > 0 and nums[i] == nums[i-1] and check[i-1] == 0:
                continue
            check[i] = 1
            self.backtrack(sol+[nums[i]], nums, check)
            check[i] = 0
  
```

# 动态规划

状态转移方程
动态规划中当前的状态往往依赖于前一阶段的状态和前一阶段的决策结果。例如我们知道了第i个阶段的状态Si以及决策Ui，那么第i+1阶段的状态Si+1也就确定了。所以解决动态规划问题的关键就是确定状态转移方程，一旦状态转移方程确定了，那么我们就可以根据方程式进行编码。

在前面的文章《动态规划-开篇》讲到了如何设计一个动态规划算法，有以下四个步骤：

1、刻画一个最优解的结构特征。

2、递归地定义最优解的值。

3、计算最优解的值，通常采用自底向上的方法。

4、利用计算出的信息构造一个最优解。
 

## 1、最长公共子串
假设两个字符串为str1和str2，它们的长度分别为n和m。 
d[i][j]表示str1中前i个字符与str2中前j个字符分别组成的两个前缀字符串的最长公共长度。这样就把长度为n的str1和长度为m的str2划分成长度为i和长度为j的子问题进行求解。状态转移方程如下：
```python
dp[0][j] = 0; (0<=j<=m)
dp[i][0] = 0; (0<=i<=n)
dp[i][j] = dp[i-1][j-1] +1; #(str1[i] == str2[j])
dp[i][j] = 0; #(str1[i] != str2[j])
```
因为最长公共子串要求必须在原串中是连续的，所以一但某处出现不匹配的情况，此处的值就重置为0。
 

## 2、最长公共子序列
区分一下，最长公共子序列不同于最长公共子串，序列是保持子序列字符串的下标在str1和str2中的下标顺序是递增的，该字符串在原串中并不一定是连续的。同样的我们可以假设dp[i][j]表示为字符串str1的前i个字符和字符串str2的前j个字符的最长公共子序列的长度。状态转移方程如下：
```python
dp[0][j] = 0; (0<=j<=m)
dp[i][0] = 0; (0<=i<=n)
dp[i][j] = dp[i-1][j-1] +1; (str1[i-1] == str2[j-1])
dp[i][j] = max{dp[i][j-1],dp[i-1][j]}; (str1[i-1] != str2[j-1])
``` 

## 3、最长递增子序列 
因为两者的思路都是一样的，所以只给出最长递增子序列的状态转移方程。假设有序列{a1,a2,...,an}，我们求其最长递增子序列长度。  
按照递推求解的思想，我们用F[i]代表若递增子序列以ai结束时它的最长长度。当 i 较小，我们容易直接得出其值，如 F[1] = 1。
```python
dp = []
for i in range(len(nums)):
    dp.append(1)
    for j in range(i):
        if nums[i] > nums[j]:
            dp[i] = max(dp[i], dp[j] + 1)
return max(dp)
```

 

## 4、最大子序列和的问题
假设有序列{a1,a2,...,an}，求子序列的和最大问题，我们用dp[i]表示以ai结尾的子序列的最大和。
```python
dp[1] = a1; (a1>=0 && i == 1) 
dp[i] = dp[i-1]+ai; (ai>=0 && i>=2) 
dp[i] = 0; (dp[i-1] + ai <=0 && i>=2)
```

## 5、数塔问题（动态搜索）
给定一个数组data[n][m]构成一个数塔求从最上面走到最低端经过的路径和最大。可以假设dp[i][j]表示走到第i行第j列位置处的最大值，那么可以推出状态转移方程：
```python
dp[i][j] = max{dp[i-1][j-1],dp[i-1][j]} + data[i][j];
```
 View Code
## 6、0-1背包问题
这是一个经典的动态规划问题，另外在贪心算法里也有背包问题，至于二者的区别在此就不做介绍了。

假设有N件物品和一个容量为V的背包。第i件物品的体积是v[i]，价值是c[i]，将哪些物品装入背包可使价值总和最大？

每一种物品都有两种可能即放入背包或者不放入背包。可以用dp[i][j]表示第i件物品放入容量为j的背包所得的最大价值，则状态转移方程可以推出如下：
```python
dp[i][j]=max{dp[i-1][j-v[i]]+c[i],dp[i-1][j]};
``` 

## 7、矩阵连乘 
例如矩阵链<A1,A2,A3>,它们的维数分别为10*100,100*5,5*50，那么如果顺序相乘即((A1A2)A3)，共需10*100*5 + 10*5*50 = 7500次乘法，如果按照(A1(A2A3))顺序相乘，却需做100*5*50 + 10*100*50 = 75000次乘法。两者之间相差了10倍，所以说矩阵链的相乘顺序也决定了计算量的大小。

我们用利用动态规划的方式(dp[i][j]表示第i个矩阵至第j个矩阵这段的最优解,还有对于两个矩阵A(i,j)*B(j,k)则需要i*j*k次乘法)，推出状态转移方程：
```python
dp[i][j] = 0; (i ==j，表示只有一个矩阵，计算次数为0)

dp[i][j] = min{dp[i][k] + dp[k+1][j] + p[i-1]*p[k]*p[j]}; (i<j && i<=k<j)            

dp[1][n]即为最终求解.
```

<<<<<<< HEAD
## 8. 树中距离之和
给定一个无向、连通的树。树中有 N 个标记为 0...N-1 的节点以及 N-1 条边 。 第 i 条边连接节点 edges[i][0] 和 edges[i][1] 。
 返回一个表示节点 i 与其他所有节点距离之和的列表 ans。

**解题思路**  
朴素的想法是，计算每一个节点到其他节点的距离，然后求和。 显然，这样做存在大量的重复计算，也就是说，有较大的优化空间。

 
稍加观察，不难发现，我们只需要计算出根节点的结果，其他节点无非就是根节点的转移，只需考虑靠近和远离的节点个数即可。

对于父子节点来说，子节点比父节点更靠近它的子孙节点，同时远离父节点的其他节点。我们不难得出这样的状态转移方程：
    dp[i] = dp[i.parent] - x + y

其中，x为靠近的节点个数，y为远离的节点个数。二者之和固定，只需要得到其中的一个，就可以计算出另一个。

要想得到x或者y，我们还需要知道每个节点有多少个子孙节点，这可以在第一次遍历，计算根节点到其他节点的距离和是顺便求出。
我们将其记录下来，以备它用。最后，再从根节点开始，遍历一遍，把其他节点的结果也计算出来，就大功告成了。
 
 
```python
class Solution:
    def sumOfDistancesInTree(self, N: int, edges: List[List[int]]) -> List[int]:
        graph = [[] for _ in range(N)]
        for edge in edges:
            graph[edge[0]].append(edge[1])
            graph[edge[1]].append(edge[0])
        dist_sum = [0 for _ in range(N)]
        node_num = [1 for _ in range(N)]

        def post_order(node, parent):
            for n in graph[node]:
                if n == parent:
                    continue
                post_order(n, node)
                node_num[node] += node_num[n]
                dist_sum[node] += dist_sum[n] + node_num[n]

        def pre_order(node, parent):
            for n in graph[node]:
                if n == parent:
                    continue
                dist_sum[n] = dist_sum[node] - node_num[n] + (N - node_num[n])
                pre_order(n, node)
        
        post_order(0, -1)
        pre_order(0, -1)
        return dist_sum
```
=======
## 8、任意两点的最短路径
Floyd算法
Floyd-Warshall算法的原理是动态规划 

设  D_{i,j,k} 为从 i到 j的只以(1..k)集合中的节点为中间节点的最短路径的长度。

若最短路径经过点k，则 D_{i,j,k} = D_{i,k,k-1} + D_{k,j,k-1}  
若最短路径不经过点k，则  D_{i,j,k} = D_{i,j,k-1}  
因此， D_{i,j,k} = min(D_{i,j,k-1}, D_{i,k,k-1}  +D_{k,j,k-1})  

在实际算法中，为了节约空间，可以直接在原来空间上进行迭代，这样空间可降至二维。
>>>>>>> 06d14709bf2798098920a8da795015e0f232229e
