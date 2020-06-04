# ECMAScript 6


## Class

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

### Mixin 模式的实现 § ⇧
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