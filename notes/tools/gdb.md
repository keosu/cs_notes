# GDB调试命令详解

## 简介  

GDB（GNU Debugger）是GCC的调试工具。使用编译器（cc/gcc/g++）的 -g 参数生成调试信息：  
gcc -g hello.c -o hello  
g++ -g hello.cpp -o hello  
如果没有-g，你将看不见程序的函数名、变量名，所代替的全是运行时的内存地址。

## 启动GDB
1、gdb program  
2、gdb program core  用gdb同时调试一个运行程序和core文件，core是程序非法执行后core dump后产生的文件。  
3、gdb PID process-id   指定这个服务程序运行时的进程ID，gdb会自动attach    

下面是一些最常用的GDB命令:  

-   file [filename]       装入想要调试的可执行文件  
-   kill [filename]       终止正在调试的程序  
-   b [file:]function       在(file文件的)function函数中设置一个断点  
-   clear       删除一个断点，这个命令需要指定代码行或者函数名作为参数  
-   run [arglist]       运行您的程序 (如果指定了arglist,则将arglist作为参数运行程序)  
-   bt Backtrace: 显示程序堆栈信息  
-   print expr       打印表达式的值  
-   continue       继续运行您的程序 (在停止之后，比如在一个断点之后)  
-   list       列出产生执行文件的源代码的一部分  
-   next       单步执行 (在停止之后); 跳过函数调用  
-   nexti       执行下一行的源代码中的一条汇编指令  
-   set       设置变量的值。例如：set nval=54 将把54保存到nval变量中  
-   step       单步执行 (在停止之后); 进入函数调用  
-   stepi       继续执行程序下一行源代码中的汇编指令。如果是函数调用，这个命令将进入函数的内部，单步执行函数中的汇编代码  
-   watch       使你能监视一个变量的值而不管它何时被改变  
-   rwatch       指定一个变量，如果这个变量被读，则暂停程序运行，在调试器中显示信息，并等待下一个调试命令。参考rwatch和watch命令  
-   awatch       指定一个变量，如果这个变量被读或者被写，则暂停程序运行，在调试器中显示信息，并等待下一个调试命令。参考rwatch和watch命令  
-   Ctrl-C       在当前位置停止执行正在执行的程序，断点在当前行  
-   disable       禁止断点功能，这个命令需要禁止的断点在断点列表索引值作为参数  
-   display       在断点的停止的地方，显示指定的表达式的值。(显示变量)  
-   undisplay       删除一个display设置的变量显示。这个命令需要将display list中的索引做参数  
-   enable       允许断点功能，这个命令需要允许的断点在断点列表索引值作为参数  
-   finish       继续执行，直到当前函数返回  
-   ignore       忽略某个断点制定的次数。例：ignore 4 23 忽略断点4的23次运行，在第24次的时候中断  
-   info [name]       查看name信息  
-   load       动态载入一个可执行文件到调试器  
-   xbreak       在当前函数的退出的点上设置一个断点  
-   whatis       显示变量的值和类型  
-   ptype       显示变量的类型  
-   return       强制从当前函数返回  
-   txbreak       在当前函数的退出的点上设置一个临时的断点(只可使用一次)  
-   make       使你能不退出 gdb 就可以重新产生可执行文件  
-   shell       使你能不离开 gdb 就执行 UNIX shell 命令  
-   help [name]       显示GDB命令的信息，或者显示如何使用GDB的总体信息  
-   quit       退出gdb 

## 程序运行上下文

- set args 可指定运行时参数。（如：set args 10 20 30 40 50 ）    
- show args 命令可以查看设置好的运行参数。   
- run (r) 不带参数启动程序   
- r 10 20 30 40 50  指定运行参数 
- cd 相当于shell的cd命令。 
- pwd 显示当前的所在目录。 
- info terminal显示你程序用到的终端的模式，使用重定向控制程序输出。如：run > outfile  

## 设置断点
### 简单断点
- break 设置断点，可以简写为b   
- b 10设置断点，在源程序第10行   
- b func设置断点，在func函数入口处     
- b filename:linenum  在源文件filename的linenum行处停住   
- b filename:function  在源文件filename的function函数的入口处停住 
- b class::function或function(type,type) 在类class的function函数的入口处停住   
- b namespace::class::function  在名称空间为namespace的类class的function函数的入口处停住  
- b linespec thread threadno 线程断点
- b linespec thread threadno if …

### 查询所有断点
- info b  

### 观察点  
- watch 为表达式（变量）expr设置一个观察点。当表达式值有变化时，停住程序。 
- rwatch表达式（变量）expr被读时，停住程序。 
- awatch 表达式（变量）的值被读或被写时，停住程序。 
- info watchpoints列出当前所设置了的所有观察点。

### 条件断点

- b test.c:8 if intValue == 5  
- condition bnum expression  修改断点号为bnum的停止条件为expression 
- condition bnum 清除断点号为bnum的停止条件  
- ignore bnum count 表示忽略断点号为bnum的停止条件count次 

### 维护停止点  

- clear清除所有的已定义的停止点。
- clear function清除所有设置在函数上的停止点。
- clear linenum清除所有设置在指定行上的停止点。
- clear filename:linenum清除所有设置在指定文件：指定行上的停止点。
- delete [bp] [range...]删除指定的断点，bp为断点号,简写命令为d。
- disable [bnum] [range...] disable所指定的停止点，bp为停止点号,简写dis.
- enable [bp] [range...]enable所指定的停止点，breakpoints为停止点号。
- enable [bp] once range…enable所指定的停止点一次，当程序停止后，该停止点马上被GDB自动disable。
- enable [bp] delete range…enable所指定的停止点一次，程序停止后停止点自动删除。
- commands [bnum] 批量命令
 
## 调试代码  

- run 运行程序，可简写为r
- next 单步跟踪，函数调用当作一条简单语句执行，可简写为n
- step 单步跟踪，函数调进入被调用函数体内，可简写为s
- finish 退出函数
- until 在一个循环体内单步跟踪时，这个命令可以运行程序直到退出循环体,可简写为u。
- continue 继续运行程序，可简写为c
- stepi或si, nexti或ni 单步跟踪一条机器指令
- info program 来查看程序的是否在运行，进程号，被暂停的原因。

## 查看运行时数据  

- print 打印变量、字符串、表达式等的值，可简写为p 
- p count 打印count的值 
- p cou1+cou2+cou3 打印表达式值
- p f2.c::x
- p *array@len  显示数组

## 自动显示

- display expr 自动显示的变量
- display/fmt expr fmt表示显示的格式
- display/fmt addr 
- info display 查看display设置的自动显示的信息。
- undisplay dnums…
- delete display dnums… 
- disable display dnums…
- enable display dnums…
- disable和enalbe不删除自动显示的设置，而只是让其失效和恢复。

## 历史记录  
当你用GDB的print查看程序运行时的数据时，你每一个print都会被GDB记录下来。  
GDB会为你每一个print命令编上号。于是，你可以使用这个编号访问以前的表达式

## 改变程序的执行

- print x=4 把变量x的值修改为4
- set var width=47
- whatis width 查看类型 

- jump file:line 表示下一条运行语句从哪里开始  
- jump *address 代码行的内存地址  

 *注意*  
 jump命令不会改变当前的程序栈中的内容，所以，当你从一个函数跳到另一个函数时，当函数运行完返回时进行弹栈操作时必然会发生错误，可能结果还是非常奇怪的，甚至于产生程序Core Dump。所以最好是同一个函数中进行跳转。 
 熟悉汇编的人都知道，程序运行时，eip寄存器用于保存当前代码所在的内存地址。所以，jump命令也就是改变了这个寄存器中的值。于是，你可以使用“set $pc”来更改跳转执行的地址。如：    
- set $pc = 0×485  

- signal signal 产生一个信号量给被调试的程序，UNIX的系统信号量通常从1到15。所以取值也在这个范围。
 
- return  
- return expression 
- call expr  调用函数 


## 显示源代码

- list linenum 
- list function 显示函数名为function的函数的源程序  
- list 显示当前行后面的源程序  
- list - 显示当前行前面的源程序   
- set listsize count 设置一次显示源代码的行数  
- show listsize 查看当前listsize的设置  


## 栈信息  

- breacktrace,简称bt  
- backtrace -n 表示只打印栈顶上n层的栈信息。
- frame n n是栈中的层编号, frame 0栈顶，frame 1栈的第二层。
- frame addr 
- up n 表示向栈的上面移动n层，可以不打n，表示向上移动一层。
- down n 表示向栈的下面移动n层，可以不打n，表示向下移动一层 
  + select-frame 对应于 frame 命令。 
  + up-silently n 对应于 up 命令。 
  + down-silently n 对应于 down 命令 
- frame 或 f 查看当前栈层的信息 
- info frame
- info f

## 信号  

handle signal[keywords...]
signal可以以SIG开头或不以SIG开头，可以用定义一个要处理信号的范围（如：SIGIO-SIGKILL，表示处理从 SIGIO信号到SIGKILL的信号，其中包括SIGIO，SIGIOT，SIGKILL三个信号），也可以使用关键字all来标明要处理所有的信号。一旦被调试的程序接收到信号，运行程序马上会被GDB停住，以供调试。   
 keywords列表如下:
 - nostop 当被调试的程序收到信号时，GDB不会停住程序的运行，但会打出消息告诉你收到这种信号。
 - stop   当被调试的程序收到信号时，GDB会停住你的程序。This implies the print keyword as well.
 - print  当被调试的程序收到信号时，GDB会显示出一条信息。
 - noprint当被调试的程序收到信号时，GDB不会告诉你收到信号的信息。This implies the nostop keyword as well.
 - pass
 - noignore当被调试的程序收到信号时，GDB不处理信号。这表示，GDB会把这个信号交给被调试程序处理 or else it may terminate if the signal is fatal and not handled.
 - nopass
 - ignore当被调试的程序收到信号时，GDB不会让被调试程序来处理这个信号。 
info signals
info handle 查看有哪些信号在被GDB检测中。


   
## 设置捕捉点(CatchPoint) 

catch 设置捕捉点来补捉程序运行时的一些事件。如载入共享库(动态链接库)或是C++的异常  

当event发生时，停住程序。event可以是下面的内容：
- throw 一个C++抛出的异常 (throw为关键字)。
- catch 一个C++捕捉到的异常 (catch为关键字)。
- exec 调用系统调用exec时(exec为关键字，目前此功能只在HP-UX下有用)。
- fork 调用系统调用fork时(fork为关键字，目前此功能只在HP-UX下有用)。
- vfork 调用系统调用vfork时(vfork为关键字，目前此功能只在HP-UX下有)。
- load 或 load 载入共享库(动态链接库)时 (load为关键字，目前此功能只在HP-UX下有用)。
- unload 或 unload 卸载共享库(动态链接库)时 (unload为关键字，目前此功能只在HP-UX下有用)。

## 指定源文件的路径  

- Directory dirname …
- dir dir1:dir2:dir3 如果你要指定多个路径，UNIX下你可以使用“:”，Windows下你可以使用“;”  
- directory 清除所有的自定义的源文件搜索路径信息。
- show directories 显示定义了的源文件搜索路径。

## 机器语言工具 

 1. $pc： 程序计数器 
 2. $fp： 帧指针（当前堆栈帧） 
 3. $sp： 栈指针 
 4. $ps： 处理器状态 


## 原文件的搜索  
1. search text:该命令可显示在当前文件中包含text串的下一行。 
2. Reverse-search text:该命令可以显示包含text 的前一行。 






