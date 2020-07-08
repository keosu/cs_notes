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
## 内置数据类型列表
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

# 基本数据类型
与大多数语言一样，Python有许多基本类型，包括整数，浮点数，布尔值和字符串。这些数据类型的行为方式与其他编程语言相似。

- Numbers(数字类型)：代表的是整数和浮点数，它原理与其他语言相同：
```python
x = 3
print(type(x)) # Prints "<class 'int'>"
print(x)       # Prints "3"
print(x + 1)   # Addition; prints "4"
print(x - 1)   # Subtraction; prints "2"
print(x * 2)   # Multiplication; prints "6"
print(x ** 2)  # Exponentiation; prints "9"
x += 1
print(x)  # Prints "4"
x *= 2
print(x)  # Prints "8"
y = 2.5
print(type(y)) # Prints "<class 'float'>"
print(y, y + 1, y * 2, y ** 2) # Prints "2.5 3.5 5.0 6.25"
```
注意，与许多语言不同，Python没有一元增量(x+)或递减(x-)运算符。

Python还有用于复数的内置类型；你可以在这篇文档中找到所有的详细信息。

- Booleans(布尔类型): Python实现了所有常用的布尔逻辑运算符，但它使用的是英文单词而不是符号 (&&, ||, etc.)：
```python
t = True
f = False
print(type(t)) # Prints "<class 'bool'>"
print(t and f) # Logical AND; prints "False"
print(t or f)  # Logical OR; prints "True"
print(not t)   # Logical NOT; prints "False"
print(t != f)  # Logical XOR; prints "True"
```

- Strings(字符串类型)：Python对字符串有很好的支持：
```python
hello = 'hello'    # String literals can use single quotes
world = "world"    # or double quotes; it does not matter.
print(hello)       # Prints "hello"
print(len(hello))  # String length; prints "5"
hw = hello + ' ' + world  # String concatenation
print(hw)  # prints "hello world"
hw12 = '%s %s %d' % (hello, world, 12)  # sprintf style string formatting
print(hw12)  # prints "hello world 12"

# String对象有许多有用的方法；例如：
s = "hello"
print(s.capitalize())  # Capitalize a string; prints "Hello"
print(s.upper())       # Convert a string to uppercase; prints "HELLO"
print(s.rjust(7))      # Right-justify a string, padding with spaces; prints "  hello"
print(s.center(7))     # Center a string, padding with spaces; prints " hello "
print(s.replace('l', '(ell)'))  # Replace all instances of one substring with another;
                                # prints "he(ell)(ell)o"
print('  world '.strip())  # Strip leading and trailing whitespace; prints "world"
```


# 容器(Containers)
Python包含几种内置的容器类型：列表、字典、集合和元组。

## 列表(Lists)
列表其实就是Python中的数组，但是可以它可以动态的调整大小并且可以包含不同类型的元素：
```python
xs = [3, 1, 2]    # Create a list
print(xs, xs[2])  # Prints "[3, 1, 2] 2"
print(xs[-1])     # Negative indices count from the end of the list; prints "2"
xs[2] = 'foo'     # Lists can contain elements of different types
print(xs)         # Prints "[3, 1, 'foo']"
xs.append('bar')  # Add a new element to the end of the list
print(xs)         # Prints "[3, 1, 'foo', 'bar']"
x = xs.pop()      # Remove and return the last element of the list
print(x, xs)      # Prints "bar [3, 1, 'foo']"

#切片(Slicing): 除了一次访问一个列表元素之外，Python还提供了访问子列表的简明语法; 这被称为切片：

nums = list(range(5))     # range is a built-in function that creates a list of integers
print(nums)               # Prints "[0, 1, 2, 3, 4]"
print(nums[2:4])          # Get a slice from index 2 to 4 (exclusive); prints "[2, 3]"
print(nums[2:])           # Get a slice from index 2 to the end; prints "[2, 3, 4]"
print(nums[:2])           # Get a slice from the start to index 2 (exclusive); prints "[0, 1]"
print(nums[:])            # Get a slice of the whole list; prints "[0, 1, 2, 3, 4]"
print(nums[:-1])          # Slice indices can be negative; prints "[0, 1, 2, 3]"
nums[2:4] = [8, 9]        # Assign a new sublist to a slice
print(nums)               # Prints "[0, 1, 8, 9, 4]"

#(循环)Loops: 你可以循环遍历列表的元素，如下所示：

animals = ['cat', 'dog', 'monkey']
for animal in animals:
    print(animal)
# Prints "cat", "dog", "monkey", each on its own line.
如果要访问循环体内每个元素的索引，请使用内置的 enumerate 函数：

animals = ['cat', 'dog', 'monkey']
for idx, animal in enumerate(animals):
    print('#%d: %s' % (idx + 1, animal))
# Prints "#1: cat", "#2: dog", "#3: monkey", each on its own line
列表推导式(List comprehensions): 编程时，我们经常想要将一种数据转换为另一种数据。 举个简单的例子，思考以下计算平方数的代码：

nums = [0, 1, 2, 3, 4]
squares = []
for x in nums:
    squares.append(x ** 2)
print(squares)   # Prints [0, 1, 4, 9, 16]
你可以使用 列表推导式 使这段代码更简单:

nums = [0, 1, 2, 3, 4]
squares = [x ** 2 for x in nums]
print(squares)   # Prints [0, 1, 4, 9, 16]
列表推导还可以包含条件：

nums = [0, 1, 2, 3, 4]
even_squares = [x ** 2 for x in nums if x % 2 == 0]
print(even_squares)  # Prints "[0, 4, 16]"
``` 

## 字典
字典存储（键，值）对，类似于Java中的Map或Javascript中的对象。你可以像这样使用它：
```python
d = {'cat': 'cute', 'dog': 'furry'}  # Create a new dictionary with some data
print(d['cat'])       # Get an entry from a dictionary; prints "cute"
print('cat' in d)     # Check if a dictionary has a given key; prints "True"
d['fish'] = 'wet'     # Set an entry in a dictionary
print(d['fish'])      # Prints "wet"
# print(d['monkey'])  # KeyError: 'monkey' not a key of d
print(d.get('monkey', 'N/A'))  # Get an element with a default; prints "N/A"
print(d.get('fish', 'N/A'))    # Get an element with a default; prints "wet"
del d['fish']         # Remove an element from a dictionary
print(d.get('fish', 'N/A')) # "fish" is no longer a key; prints "N/A"
你可以在这篇文档中找到有关字典的所有信息。

(循环)Loops: 迭代词典中的键很容易：

d = {'person': 2, 'cat': 4, 'spider': 8}
for animal in d:
    legs = d[animal]
    print('A %s has %d legs' % (animal, legs))
# Prints "A person has 2 legs", "A cat has 4 legs", "A spider has 8 legs"
如果要访问键及其对应的值，请使用items方法：

d = {'person': 2, 'cat': 4, 'spider': 8}
for animal, legs in d.items():
    print('A %s has %d legs' % (animal, legs))
# Prints "A person has 2 legs", "A cat has 4 legs", "A spider has 8 legs"
字典推导式(Dictionary comprehensions): 类似于列表推导式，可以让你轻松构建词典数据类型。例如：

nums = [0, 1, 2, 3, 4]
even_num_to_square = {x: x ** 2 for x in nums if x % 2 == 0}
print(even_num_to_square)  # Prints "{0: 0, 2: 4, 4: 16}"
``` 
## 集合(Sets)
集合是不同元素的无序集合。举个简单的例子，请思考下面的代码： 
```python
animals = {'cat', 'dog'}
print('cat' in animals)   # Check if an element is in a set; prints "True"
print('fish' in animals)  # prints "False"
animals.add('fish')       # Add an element to a set
print('fish' in animals)  # Prints "True"
print(len(animals))       # Number of elements in a set; prints "3"
animals.add('cat')        # Adding an element that is already in the set does nothing
print(len(animals))       # Prints "3"
animals.remove('cat')     # Remove an element from a set
print(len(animals))       # Prints "2"
与往常一样，你想知道的关于集合的所有内容都可以在这篇文档中找到。

循环(Loops): 遍历集合的语法与遍历列表的语法相同；但是，由于集合是无序的，因此不能假设访问集合元素的顺序：

animals = {'cat', 'dog', 'fish'}
for idx, animal in enumerate(animals):
    print('#%d: %s' % (idx + 1, animal))
# Prints "#1: fish", "#2: dog", "#3: cat"
集合推导式(Set comprehensions): 就像列表和字典一样，我们可以很容易地使用集合理解来构造集合：

from math import sqrt
nums = {int(sqrt(x)) for x in range(30)}
print(nums)  # Prints "{0, 1, 2, 3, 4, 5}"
``` 
## 元组(Tuples)
元组是（不可变的）有序值列表。 元组在很多方面类似于列表; 其中一个最重要的区别是元组可以用作字典中的键和集合的元素，而列表则不能。 这是一个简单的例子：
```python
d = {(x, x + 1): x for x in range(10)}  # Create a dictionary with tuple keys
t = (5, 6)        # Create a tuple
print(type(t))    # Prints "<class 'tuple'>"
print(d[t])       # Prints "5"
print(d[(1, 2)])  # Prints "1"
``` 

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

## 官方文档

- 语言参考： https://docs.python.org/zh-cn/3.7/reference/index.html
- 标准库 https://docs.python.org/zh-cn/3.7/library/index.html
- 内置函数 https://docs.python.org/zh-cn/3.7/library/functions.html
