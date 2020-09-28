# 

## 回溯

### 重复元素的全排列
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