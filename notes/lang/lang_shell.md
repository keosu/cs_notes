# shell基础

## shell参数
- $0:命令含命令所在的路径，$1 表示程序的第一个参数 
- $#:传递给程序的总的参数数目。 
- $?:命令结果，正常退出返回 0，反之为非 0 值。 
- $*:传递给程序的所有参数组成的字符串。  

## 变量
在 Shell 中所有变量名都由字符串组成，不需要进行声明。  
赋值格式如下(=前后无空格)：   
> 名=值   

标准输入  
> read 变量 

## 数组的定义
shell中数组两种类型：一是数值类型，二是字符串类型； 
括号表示数组，数组中元素之间使用“空格”来隔开。 
- 　　arr_number=(1 2 3 4 5); 
- 　　arr_string=("abc" "edf" "sss"); 或 arr_string=('abc' 'edf' 'sss');
数组的操作
　　以数组arr_number=(1 2 3 4 5)为例讲解：获取数组长度，读取某个下标的值，对某个下标赋值，删除、分配和替换以及遍历。提一个知识点，我们在shell里面想获取某个变量的值，使用$符开头，如：$a或者${a}即可。
#### 获取数组长度
　　arr_length=${#arr_number[*]}或${#arr_number[@]}均可
#### 读取某个下标的值
　　arr_index2=${arr_number[2]}，即形式：${数组名[下标]}
#### 对某个下标赋值 
- 如果该下标元素已经存在，会修改该下标的值为新的指定值.  
  例如：arr_number[2]=100，数组被修改为(1 2 100 4 5)
- 如果下标已经超过数组的大小，新赋值被追加到数组尾部。  
  例如：arr_number[13]=13，数组被修改为(1 2 100 4 5 13)
#### 删除操作
清除某个元素：unset arr_number[1]，清除下标为1的数组；  
清空整个数组：unset arr_number;
#### 分片访问
　　　　分片访问形式为：${数组名[@或*]:开始下标:结束下标}，注意，不包括结束下标元素的值。
　　　　例如：${arr_number[@]:1:4}，这里分片访问从下标为1开始，元素个数为4。
#### 模式替换
　　　　形式为：${数组名[@或*]/模式/新值}
　　　　例如：${arr_number[@]/2/98}
#### 数组的遍历
```bash
for v in ${arr_number[@]}; do
　　echo $v;
done 
```

## 表达式比较
- 字符串操作符 
  符号| 含义
   ---|---
  =   |是否相同
  !=  |是否不同 
  -n  |字符串长度是否大于零 
  -z  |字符串长度是否等于零 

- 逻辑运算符
   符号| 含义
    ---|---
  !    |非
  -a   |and 与
  -o   |or 或  

- 用 test 比较的运算符 

- 数字比较符 
    符号| 含义
     ---|---
  -eq   |==
  -ge   |>= 
  -le   |<= 
  -ne   |!= 
  -gt   |> 
  -lt   |< 

- 文件操作符  
运算符号| 含义
     ---|---
  -d    |对象存在且为目录返回值为“是” 
  -f    |对象存在且为文件返回值为“是” 
  -L    |对象存在且为符号连接返回值为“是” 
  -r    |对象存在且可读则返回值为“是” 
  -s    |对象存在且长度非零则返回值为“是” 
  -w    |对象存在且且可写则返回值为“是” 
  -x    |对象存在且且可执行则返回值为“是” 

## 条件语句
```bash
if 表达式 1  then 
    操作 
elif 表达式 2  then 
    操作 
elif 表达式 3  then 
    操作  
else 
    操作 
fi 
```
## case语句
```bash
case 表达式 in 
    值 1|值 2） 
        操作；； 
    值 3|值 4） 
        操作；； 
    值 5|值 6） 
        操作；； 
    *） 
        操作；； 
esac
```
## 函数
```bash
#!/bin/sh 
add() 
{ 
    a=$1 
    b=$2 
    z=’expr $a + $b’ 
    echo “The sum is $z” 
} 
add $1 $2 
```

## 变量声明 local、export 、declare、set  
- local一般用于局部变量声明，多在在函数内部使用。    
      1.    Shell脚本中定义的变量是global的，其作用域从被定义的地方开始，到shell结束或被显示删除的地方为止。  
      2.    Shell函数定义的变量默认是global的，其作用域从“函数被调用时执行变量定义的地方”开始，到shell结束或被显示删除处为止。函数定义的变量可以被显示定义成local的，其作用域局限于函数内。但请注意，函数的参数是local的。  
      3.    如果同名，Shell函数定义的local变量会屏蔽脚本定义的global变量。
      
- export:将自定义变量设定为系统环境变量（仅限于该次登陆操作，当前shell中有效）
      语　　法：export [-fnp][变量名称]=[变量设置值]
      补充说明：在shell中执行程序时，shell会提供一组环境变量。export可新增，修改或删除环境变量，供后续执行的程序使用。
      参　　数：
      -f 　代表[变量名称]中为函数名称。  
      -n 　删除指定的变量。变量实际上并未删除，只是不会输出到后续指令的执行环境中。  
      -p 　列出所有的shell赋予程序的环境变量。
      
- 系统设置--declare  和set类似
  功能说明：声明 shell 变量。

  语法：declare [+/-][rxi][变量名称＝设置值] 或 declare -f

  补充说明：declare为shell指令，在第一种语法中可用来声明变量并设置变量的属性([rix]即为变量的属性），在第二种语法中可用来显示shell函数。若不加上任何参数，则会显示全部的shell变量与函数(与执行set指令的效果相同)。

  参数：  
   +/- 　"-"可用来指定变量的属性，"+"则是取消变量所设的属性。   
   -f 　仅显示函数。   
   r 　将变量设置为只读 。   
   x 　指定的变量会成为环境变量，可供shell以外的程序来使用。   
   i 　[设置值]可以是数值，字符串或运算式。  