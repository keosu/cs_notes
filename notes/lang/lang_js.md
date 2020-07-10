 # javascript基础 
  
# 1 数据类型   

javascript包含两大类数据类型：值类型和引用类型  
- 值类型(基本类型)：字符串（string）、数字(number)、布尔(boolean)、空（null）、未定义（undefined）、Symbol（ES6引入）。
- 引用数据类型：对象(Object)、数组(Array)、函数(Function) ……

## 值类型  
### Number  

javascript不区分整数和浮点数，统一用Number表示，以下都是合法的Number类型：  
```js  
  123; // 整数123  
  0.456; // 浮点数0.456  
  1.2345e3; // 科学计数法表示1.2345x1000，等同于1234.5  
  -99; // 负数  
  NaN; // NaN表示Not a Number，当无法计算结果时用NaN表示  
  Infinity; // Infinity表示无限大   
```   
  Number可以直接做四则运算，规则和数学一致：  
```js    
  1 + 2; // 3  
  (1 + 2) * 5 / 2; // 7.5  
  2 / 0; // Infinity  
  0 / 0; // NaN  
  10 % 3; // 1  
  10.5 % 3; // 1.5   
```

### 字符串  
字符串是以单引号'或双引号"括起来的任意文本，比如'abc'，"xyz"等等。   
  
### 布尔值  
布尔值和布尔代数的表示完全一致，一个布尔值只有true、false两种值  
  
**比较运算符**  
  
第一种是==比较，它会自动转换数据类型再比较，很多时候，会得到非常诡异的结果；  
  
第二种是===比较，它不会自动转换数据类型，如果数据类型不一致，返回false，如果一致，再比较。  
  
由于javascript这个设计缺陷，不要使用==比较，始终坚持使用===比较。  
  
另一个例外是NaN这个特殊的Number与所有其他值都不相等，包括它自己：  
  
NaN === NaN; // false， 唯一能判断NaN的方法是通过isNaN()函数：  
  
isNaN(NaN); // true  


**null和undefined**  
null表示一个“空”的值，它和0以及空字符串''不同，0是一个数值，''表示长度为0的字符串，而null表示“空”。  
  
在其他语言中，也有类似javascript的null的表示，例如Java也用null，Swift用nil，Python用None表示。但是，在javascript中，还有一个和null类似的undefined，它表示“未定义”。  
  
javascript的设计者希望用null表示一个空的值，而undefined表示值未定义。大多数情况下，我们都应该用null。undefined仅仅在判断函数参数是否传递的情况下有用。  

## 引用类型

### Object
javascript 对象是拥有属性和方法的数据。对象也是一个变量，但对象可以包含多个值（多个变量）。
```js
var car = {type:"Fiat", model:500, color:"white"};
```

### Array
Array 对象用于在变量中存储多个值:  
```js
var cars = ["Saab", "Volvo", "BMW"];
```

### Function
函数就是包裹在花括号中的代码块，前面使用了关键词 function：
```js
function functionname(arg1,arg2)
{
    // 执行代码
}
```

## 变量  
变量的概念基本上和初中代数的方程变量是一致的，只是在计算机程序中，变量不仅可以是数字，还可以是任意数据类型。  
  
变量在javascript中就是用一个变量名表示，变量名是大小写英文、数字、$和_的组合，且不能用数字开头。变量名也不能是javascript的关键字，如if、while等。  

```js  
var a; // 申明了变量a，此时a的值为undefined  
var $b = 1; // 申明了变量$b，同时给$b赋值，此时$b的值为1  
let s_007 = '007'; // s_007是一个字符串  
let Answer = true; // Answer是一个布尔值true  
var t = null; // t的值是null   
```  
在javascript中，使用等号=对变量进行赋值。可以把任意数据类型赋值给变量，同一个变量可以反复赋值，而且可以是不同类型的变量

在JS函数中的var声明，其作用域是函数体的全部。ES6 后引入了let和const
- let声明的变量拥有块级作用域。   
- let声明的全局变量不是全局对象的属性。这就意味着，你不可以通过window.变量名的方式访问这些变量。它们只存在于一个不可见的块的作用域中。 
- 形如for (let x...)的循环在每次迭代时都为x创建新的绑定。  
- 用let重定义变量会抛出一个语法错误（SyntaxError）。 
- const声明常量，绑定的是对象指针，但是能修改指向对象的内容
 
   
  
### strict模式  
javascript在设计之初，为了方便初学者学习，并不强制要求用var申明变量。这个设计错误带来了严重的后果：如果一个变量没有通过var申明就被使用，那么该变量就自动被申明为全局变量：   
  
使用var申明的变量则不是全局变量，它的范围被限制在该变量被申明的函数体内（函数的概念将稍后讲解），同名变量在不同的函数体内互不冲突。  
  
为了修补javascript这一严重设计缺陷，ECMA在后续规范中推出了strict模式，在strict模式下运行的javascript代码，强制通过var申明变量，未使用var申明变量就使用的，将导致运行错误。  
  
启用strict模式的方法是在javascript代码的第一行写上：  
  
'use strict';  

### 作用域

- 全局
- 局部(函数内用，使用 var声明)
- 块级作用域( ES6新增, let命令用来进行变量声明)

# 2 javascript 常用对象

javascript的对象是一组由键-值组成的无序集合，例如：  
```js  
var person = {  
    name: 'Bob',  
    age: 20,  
    tags: ['js', 'web', 'mobile'],  
    city: 'Beijing',  
    hasCar: true,  
    zipcode: null  
};  
```
javascript对象的键都是字符串类型，值可以是任意数据类型。   
  
要获取一个对象的属性，我们用对象变量.属性名的方式：  
  
person.name; // 'Bob'  
person.zipcode; // null  
'name' in person // true

## Array
数组，可以包含任意数据类型，并通过索引来访问每个元素，长度访问length属性
> new Array(1, 2, 3); // 创建了数组[1, 2, 3], 建议直接使用[]。 

数组的元素可以通过索引来访问。请注意，索引的起始值为0：  
  
var arr = [1, 2, 3.14, 'Hello', null, true];  
arr[0]; // 返回索引为0的元素，即1  
arr[5]; // 返回索引为5的元素，即true  
arr[6]; // 索引超出了范围，返回undefined  

- concat()
- indexOf() ： 查找，返回位置，没有返回-1
- join() ：转换成字符串，默认逗号分隔
- lastIndexOf()
- pop() ： 移除最后一个元素
- push() ： 在最后增加一个元素，返回长度
- reverse()
- shift() : 移除第一个元素
- slice() 
- sort()
- splice()
- toString()
- unshift() ：在最前面增加一个元素，返回长度
- valueOf()

## String 
字符串对象，用''或""括起来的字符表示。

- charAt()
- charCodeAt()
- concat()
- fromCharCode()
- indexOf()
- lastIndexOf()
- match()
- replace()
- search()
- slice()
- split() ： 按指定分隔符分割成数组
- substr()
- substring()
- toLowerCase()
- toUpperCase()
- valueOf()

## Map
  
集合中的键和值可以是任何类型。如果使用现有密钥向集合添加值，则新值会替换旧值。  
> var mp = new Map();  
  
- clear	  从映射中移除所有元素。  
- delete	  从映射中移除指定的元素。  
- forEach 对映射中的每个元素执行指定操作。   
- get	  返回映射中的指定元素。  
- has	  如果映射包含指定元素，则返回 true。  
- set	  添加一个新建元素到映射。  
- toString	  返回映射的字符串表示形式。  
- valueOf	  返回指定对象的原始值。

## Set
Set和Map类似，也是一组key的集合，但不存储value。由于key不能重复，所以，在Set中，没有重复的key。

# 3 函数

定义函数

```js
function abs(x) {
    if (x >= 0) {
        return x;
    } else {
        return -x;
    }
}
```


## 高阶函数(Higher-order function)

一个函数就可以接收另一个函数作为参数，这种函数就称之为高阶函数。

```js 
function add(x, y, f) {
    return f(x) + f(y);
}
add(-5, 6, Math.abs)
```

## 闭包(Closure)

闭包就是携带状态的函数，并且它的状态可以完全对外隐藏起来,可以封装私有变量
```js
function create_counter(initial) {
    var x = initial || 0;
    return {
        inc: function () {
            x += 1;
            return x;
        }
    }
} 

var c1 = create_counter();
c1.inc(); // 1
c1.inc(); // 2
c1.inc(); // 3

var c2 = create_counter(10);
c2.inc(); // 11
c2.inc(); // 12
c2.inc(); // 13
```
## 箭头函数(Arrow Function)
箭头函数相当于匿名函数，并且简化了函数定义
```js
// 两个参数:
(x, y) => x * x + y * y

// 无参数:
() => 3.14

// 可变参数:
(x, y, ...rest) => {
    var i, sum = x + y;
    for (i=0; i<rest.length; i++) {
        sum += rest[i];
    }
    return sum;
}
```


# 4 Class 类

ES6中新增了class的支持

```js
class Point {

  bar = 'hello'; //  实例属性
  baz = 'world';
  constructor(x, y) {
    this.x = x;
    this.y = y;
    this._count = 1; // 
  }

  toString() {
    return '(' + this.x + ', ' + this.y + ')';
  }

  static classMethod() {
    return 'hello';
  }
}

class ColorPoint extends Point {
    constructor(x, y, color) {
    super(x, y); // 调用父类的constructor(x, y)
    this.color = color;
  }
}

```
*注*   
1. ES6 没有规定静态属性和私有方法，通过变通方法解决  
2.  可以通过如下代码查看成员
 ```js
 Object.keys(Point.prototype)
// []
Object.getOwnPropertyNames(Point.prototype)
// ["constructor","toString"]
Object.getPrototypeOf(ColorPoint) === Point
```

```js
class A {
}
class B extends A {
}

B.__proto__ === A // true
B.prototype.__proto__ === A.prototype // true
```

###  new.target 属性  

new是从构造函数生成实例对象的命令。ES6 为new命令引入了一个new.target属性，该属性一般用在构造函数之中，返回new命令作用于的那个构造函数。如果构造函数不是通过new命令或Reflect.construct()调用的，new.target会返回undefined，因此这个属性可以用来确定构造函数是怎么调用 

```js
function Person(name) {
  if (new.target !== undefined) {
    this.name = name;
  } else {
    throw new Error('必须使用 new 命令生成实例');
  }
}

// 另一种写法
function Person(name) {
  if (new.target === Person) {
    this.name = name;
  } else {
    throw new Error('必须使用 new 命令生成实例');
  }
}
``` 


# 其他

## Mixin 模式的实现 § ⇧
Mixin 指的是多个对象合成一个新的对象，新对象具有各个组成成员的接口。它的最简单实现如下。
```js
const a = {
  a: 'a'
};
const b = {
  b: 'b'
};
const c = {...a, ...b}; // {a: 'a', b: 'b'}
```