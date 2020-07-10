# Typescript基础

# ch1 基本类型

```js
//---------------------------------------------------
// ch1 基本类型
function basic_type_test() {

  // Bool
  let isDone: boolean = false;
  // 数值
  let decLiteral: number = 6;
  let hexLiteral: number = 0xf00d;
  let binaryLiteral: number = 0b1010;
  let octalLiteral: number = 0o744;
  //字符串
  let abc: string = 'abc';
  let xname: string = `Gene`;
  let sentence: string = `Hello, my name is ${name}.`;
  // 数组
  let alist: number[] = [1, 2, 3];
  let blist: Array<number> = [1, 2, 3];
  // tuple
  let x: [string, number] = ['hello', 10]; // OK
  // 枚举
  enum Color { Red, Green, Blue }
  let c1: Color = Color.Green;
  let colorName: string = Color[2];
  // 任意值
  let notSure: any = 4;
  notSure = "maybe a string instead";
  notSure = false; // okay, definitely a boolean
  // undefined null
  let u: undefined = undefined;
  let n: null = null;
  // 联合类型
  var val: string | number
  val = 12
  console.log("数字为 " + val)
  val = "string"
  console.log("字符串为 " + val)
}
basic_type_test();
```

# ch2 函数

```js
//---------------------------------------------------
// ch2 函数
function add(x: number, y: number): number {
  return x + y;
}

let myAdd = function (x: number, y: number): number { return x + y; };
let myAdd2 = (x: number, y: number): number => { return x + y; };

//函数 - 默认参数
function buildName(firstName: string, lastName?: string) {
  if (lastName)
    return firstName + " " + lastName;
  else
    return firstName;
}

let result1 = buildName("Bob");  // works correctly now
let result3 = buildName("Bob", "Adams");  // ah, just right

// 函数 - 变长参数
function buildNameX(firstName: string, ...restOfName: string[]) {
  return firstName + " " + restOfName.join(" ");
}

let employeeName = buildNameX("Joseph", "Samuel", "Lucas", "MacKinzie");
```

# ch3 循环语句

```js
//---------------------------------------------------
// ch3 循环语句
function loop_test() {
  var num: number = 5;
  var i: number;
  var factorial = 1;

  for (i = num; i >= 1; i--) {
    factorial *= i;
  }
  console.log(factorial)

  factorial = 1;
  while (num >= 1) {
    factorial = factorial * num;
    num--;
  }
  console.log("5 的阶乘为：" + factorial);

  var nx: number = 10;
  do {
    nx--;
  } while (nx >= 0);
  ////////////////////////////////////////////////////////////////////
  var j: any;
  var n: any = "a b c"

  for (j in n) {
    console.log(n[j])
  }

  /////////////////////////////////////////////////////////////////////
  // TypeScript 还支持 for…of 、forEach、every 和 some 循环。

  // for...of 语句创建一个循环来迭代可迭代的对象。
  // 在 ES6 中引入的 for...of 循环，以替代 for...in 和 forEach() ，并支持新的迭代协议。
  // for...of 允许你遍历 Arrays（数组）, Strings（字符串）, Maps（映射）, Sets（集合）等可迭代的数据结构等。
  let someArray = [1, "string", false];

  for (let entry of someArray) {
    console.log(entry); // 1, "string", false
  }

  let list1 = [4, 5, 6];
  list1.forEach((val, idx, array) => {
    // val: 当前值
    // idx：当前index
    // array: Array
  });

  let list2 = [4, 5, 6];
  list2.every((val, idx, array) => {
    // val: 当前值
    // idx：当前index
    // array: Array
    return true; // Continues
    // Return false will quit the iteration
  });
  /////////////////////////////////////////////////////////////////////////////
}
loop_test()

```

# ch4 条件语句

```js
//---------------------------------------------------
// ch4 条件语句
function condition_state_test(): void {
  var num: number = 2
  if (num > 0) {
    console.log(num + " 是正数")
  } else if (num < 0) {
    console.log(num + " 是负数")
  } else {
    console.log(num + " 不是正数也不是负数")
  }

  var grade: string = "A";
  switch (grade) {
    case "A": {
      console.log("优");
      break;
    }
    case "B": {
      console.log("良");
      break;
    }
    case "C": {
      console.log("及格");
      break;
    }
    case "D": {
      console.log("不及格");
      break;
    }
    default: {
      console.log("非法输入");
      break;
    }
  }
}
condition_state_test()
```

# ch5 Number 对象测试

```js
//---------------------------------------------------
// ch5 Number 对象测试
function Number_test(): void {
  console.log("TypeScript Number 属性: ");
  console.log("最大值为: " + Number.MAX_VALUE);
  console.log("最小值为: " + Number.MIN_VALUE);
  console.log("负无穷大: " + Number.NEGATIVE_INFINITY);
  console.log("正无穷大:" + Number.POSITIVE_INFINITY);

  let num: Number = 1.234;
  num.toString();
  num.toExponential()
}
```

# ch6 String 对象测试

```js
//---------------------------------------------------
// ch6 String 对象测试
function String_test(): void {
}
```

# ch7 interface  

```js
//---------------------------------------------------
// ch7 interface
function inter_test(): void {
  interface IPerson {
    firstName: string,
    lastName: string,
    sayHi: () => string
  }

  var customer: IPerson = {
    firstName: "Tom",
    lastName: "Hanks",
    sayHi: (): string => { return "Hi there" }
  }

  console.log("Customer 对象 ")
  console.log(customer.firstName)
  console.log(customer.lastName)
  console.log(customer.sayHi())

  var employee: IPerson = {
    firstName: "Jim",
    lastName: "Blakes",
    sayHi: (): string => { return "Hello!!!" }
  }

  console.log("Employee  对象 ")
  console.log(employee.firstName)
  console.log(employee.lastName)
}
```

# ch8 class  

```js
//---------------------------------------------------
// ch8 class
function class_test(): void {
  class Car {
    // 字段 
    engine: string;

    // 构造函数 
    constructor(engine: string) {
      this.engine = engine
    }

    // 方法 
    disp(): void {
      console.log("发动机为 :   " + this.engine)
    }
  }

  var obj = new Car("Engine 1")
  obj.engine
  obj.disp()
  // 继承 与 重载
  class Shape {
    Area: number

    constructor(a: number) {
      this.Area = a
    }
    disp(): void {
      console.log("父类方法:  " + this.Area)
    }
  }

  class Circle extends Shape {
    disp(): void {
      console.log("子类方法:  " + this.Area)
    }
  }

  var obj2 = new Circle(223);
  obj2.disp()

  // 接口实现
  interface ILoan {
    interest: number
  }

  class AgriLoan implements ILoan {
    interest: number
    rebate: number

    constructor(interest: number, rebate: number) {
      this.interest = interest
      this.rebate = rebate
    }
  }

  var obj3 = new AgriLoan(10, 1)
  console.log("利润为 : " + obj3.interest + "，抽成为 : " + obj3.rebate)

}

```