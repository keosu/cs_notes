# Python
# 基本概念
  Python是一种简单的、解释型的、交互式的、面向对象的超高级编程语言。  
  Python是动态类型的，变量无需声明。变量没有类型，类型是与对象绑定的，变量可以看作是对对象的引用。
```python
# Python动态类型
a = 123
a = 1.23
a = 'hello'
```
## 内置数据类型
- 数字  12345
- 字符串 'hello'
- 列表
  [1,2,3,4,5]
- 字典
  {1:'A',2:'b'}
- 元组
  (1,'RED',100,'info')
- 集合
  {'a','b','c'} ,  set('abc')
- 文件 
  f=open('file.txt','r')
- 编程单元 函数、模块、类
## 语法
```python
a = [ (x,y) for x in range(6) if x % 2 == 0 for y in range(6) if y % 2 == 1]
```

# 函数
装饰器
```python
def log(func):
    def wrapper(*args,**kw):
        print("call %s() " % func.__name__)
        return func(*args,**kw)
    return wrapper

@log
def test():
    print("decrator")
```

# 类
```python
class A():
    VAR = 1      #public class member
    __VAR = 100  #private class  member
    def __init__(self):
        self.abc = 4     #public object member
        self.__abc = 5   #private object member
        print("A init")
        
    def show(self):
        print("A:show()" , self.__VAR)
        
    @staticmethod
    def static_f():
        print(A.VAR)
    
    @classmethod
    def class_f(cls):
        print(cls.VAR)
        cls().show()

class B(A):
    def __init__(self):
        A.__init__(self)
        print("B init")

class C(A):
    pass

class D(C,B): #multiple derived
  pass

```
