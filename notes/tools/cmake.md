# CMake  
    
## 基本用例  
```  
cmake_minimum_required(VERSION 2.6)  
project(Tutorial)    
  
set(Tutorial_VERSION_MAJOR 1)  
set(Tutorial_VERSION_MINOR 0)    
    
# 配置一个头文件，通过它向源代码中传递一些CMake的设置。  
configure_file(    
    "${PROJECT_SOURCE_DIR}/mymathConfig.h.in"    
    "${PROJECT_BINARY_DIR}/mymathConfig.h"    
)    
    
# 将二进制文件树添加到包含文件的搜索路径中，这样我们可以找到TutorialConfig.h  
include_directories("${PROJECT_BINARY_DIR}")    
    
# 是否使用自定义的math库作为库函数  
option(USE_MYMATH "Use tutorial provided math implementation" On)  
if(USE_MYMATH)    
    include_directories("${PROJECT_SOURCE_DIR}/math")    
    add_subdirectory(math)    
    set(EXTERNAL_LIBS ${EXTERNAL_LIBS} sqrt)  
endif(USE_MYMATH)    
  
add_executable(sample src/main.cpp)  
target_link_libraries(sample ${EXTERNAL_LIBS})    
```    
    
## cmake中一些预定义变量  
| 变量                              | 含义                                                         |
| --------------------------------- | ------------------------------------------------------------ |
| CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS | 用来控制 IF ELSE 语句的书写方式                              |
| CMAKE_CURRENT_BINARY_DIR          | 目标编译目录，使用 ADD_SURDIRECTORY(src bin)可以更改此变量值 |
| CMAKE_CURRENT_LIST_FILE           | 输出调用这个变量的 CMakeLists.txt 的完整路径                 |
| CMAKE_CURRENT_LIST_LINE           | 输出这个变量所在的行                                         |
| CMAKE_CURRENT_SOURCE_DIR          | 当前处理的 CMakeLists.txt 所在的路径                         |
| CMAKE_INCLUDE_PATH                | 环境变量,非 cmake 变量                                       |
| CMAKE_LIBRARY_PATH                | 环境变量                                                     |
| CMAKE_MODULE_PATH                 | 定义 cmake 模块所在的路径，用 INCLUDE 命令来调用自己的模块   |
| EXECUTABLE_OUTPUT_PATH            | 重新定义目标二进制可执行文件的存放位置                       |
| LIBRARY_OUTPUT_PATH               | 重新定义目标链接库文件的存放位置                             |
| PROJECT_BINARY_DIR                | 运行 cmake 命令的目录                                        |
| PROJECT_NAME                      | 返回通过 PROJECT 指令定义的项目名称                          |
| PROJECT_SOURCE_DIR                | 工程的根目录                                                 |
    
## 系统信息  
| 变量                   | 含义                                            |
| ---------------------- | ----------------------------------------------- |
| CAMKE_SYSTEM_NAME      | 不包含版本的系统名,如 Linux                     |
| CMAKE_MAJOR_VERSION    | cmake 主版本号,如 2.8.6 中的 2                  |
| CMAKE_MINOR_VERSION    | cmake 次版本号,如 2.8.6 中的 8                  |
| CMAKE_PATCH_VERSION    | cmake 补丁等级,如 2.8.6 中的 6                  |
| CMAKE_SYSTEM           | 系统名称,例如 Linux-2.6.22                      |
| CMAKE_SYSTEM_PROCESSOR | 处理器名称,如 i686                              |
| CMAKE_SYSTEM_VERSION   | 系统版本,如 2.6.22                              |
| UNIX                   | 在所有的类 UNIX 平台为 TRUE,包括 OS X 和 cygwin |
| WIN32                  | 在所有的 win32 平台为 TRUE,包括 cygwin          |
     
    
## 开关选项  
| 变量              | 含义                     |
| ----------------- | ------------------------ |
| BUILD_SHARED_LIBS | 控制默认的库编译方式     |
| CMAKE_CXX_FLAGS   | 设置 C++编译选项开关选项 |
| CMAKE_C_FLAGS     | 设置 C 编译选项          |

# cmake常用命令  
    
## 基本语法规则：  
0. cmake变量使用${}方式取值,但是在IF控制语句中是直接使用变量名  
1. 环境变量使用$ENV{}方式取值,使用SET(ENV{VAR} VALUE)赋值  
2. 指令(参数1 参数2…)  
>    参数使用括弧括起,参数之间使用空格或分号分开。  
    以ADD_EXECUTABLE指令为例：  
    ADD_EXECUTABLE(hello main.c func.c)或者  
    ADD_EXECUTABLE(hello main.c;func.c)  
    指令是大小写无关的,参数和变量是大小写相关的。推荐你全部使用大写指令。  
    
## 部分常用命令列表：  

- PROJECT    
PROJECT(projectname [CXX] [C] [Java])  工程名称,并可指定工程支持的语言。默认支持所有语言 

- CMAKE_MINIMUM_REQUIRED  
CMAKE_MINIMUM_REQUIRED(VERSION version_number [FATAL_ERROR])   声明CMake的版本要求  
  
- MESSAGE  
MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR] “message to display” …)  向终端输出用户定义的信息或变量的值  
SEND_ERROR, 产生错误,生成过程被跳过  
STATUS, 输出前缀“  ”的信息  
FATAL_ERROR, 立即终止所有cmake过程  
generate_messages 生成消息  

- ADD_EXECUTABLE(bin_file_name ${SRC_LIST})  
生成可执行文件（可执行文件  源文件.cpp） 

- TARGET_LINK_LIBRARIES  
TARGET_LINK_LIBRARIES(target lib1 lib2 …) 为target添加需要链接的共享库（将可执行文件连接到库上）  
ADD_LIBRARY(libname [SHARED | STATIC | MODULE] [EXCLUDE_FROM_ALL] SRC_LIST)  
生成动态库或静态库  
SHARED 动态库  
STATIC 静态库  
MODULE 在使用dyld的系统有效,若不支持dyld,等同于SHARED  
EXCLUDE_FROM_ALL 表示该库不会被默认构建 

- ADD_DEFINITIONS  
向C/C++编译器添加-D定义  ADD_DEFINITIONS(-DENABLE_DEBUG -DABC),参数之间用空格分隔  

- ADD_DEPENDENCIES(target-name depend-target1 depend-target2 …)  
定义target依赖的其他target,确保target在构建之前,其依赖的target已经构建完毕  

- ADD_SUBDIRECTORY  
ADD_SUBDIRECTORY(src_dir [binary_dir] [EXCLUDE_FROM_ALL])  
向当前工程添加存放源文件的子目录,并可以指定中间二进制和目标二进制的存放位置  
EXCLUDE_FROM_ALL含义：将这个目录从编译过程中排除  
add_service_files 添加服务文件  

- SET  
SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])  
定义变量(可以定义多个VALUE,如SET(SRC_LIST main.c util.c reactor.c))  
SET_TARGET_PROPERTIES  
设置输出的名称,设置动态库的版本和API版本  

- INCLUDE  
INCLUDE(file [OPTIONAL]) 用来载入CMakeLists.txt文件  
INCLUDE(module [OPTIONAL])用来载入预定义的cmake模块  
OPTIONAL参数的左右是文件不存在也不会产生错误  
可以载入一个文件,也可以载入预定义模块（模块会在CMAKE_MODULE_PATH指定的路径进行搜索）  
载入的内容将在处理到INCLUDE语句时直接执行  

- INCLUDE_DIRECTORIES  
INCLUDE_DIRECTORIES([AFTER | BEFORE] [SYSTEM] dir1 dir2 … )  
向工程添加多个特定的头文件搜索路径,路径之间用空格分隔,如果路径包含空格,可以使用双引号将它括起来,默认的行为为追加到当前头文件搜索路径的后面。有如下两种方式可以控制搜索路径添加的位置：CMAKE_INCLUDE_DIRECTORIES_BEFORE,通过SET这个cmake变量为on,可以将添加的头文件搜索路径放在已有路径的前面; 通过AFTER或BEFORE参数,也可以控制是追加还是置前。  

- LINK_DIRECTORIES  
LINK_DIRECTORIES(dir1 dir2 …)  添加非标准的共享库搜索路径   

- AUX_SOURCE_DIRECTORY  
AUX_SOURCE_DIRECTORY(dir VAR)  
发现一个目录下所有的源代码文件并将列表存储在一个变量中  
把当前目录下的所有源码文件名赋给变量DIR_HELLO_SRCSINCLUDE  

- FIND_  

0. FIND_FILE(<VAR> name path1 path2 …)   VAR变量代表找到的文件全路径,包含文件名  
1. FIND_LIBRARY(<VAR> name path1 path2 …)   VAR变量代表找到的库全路径,包含库文件名  
  
    FIND_LIBRARY(libX X11 /usr/lib)  
    IF (NOT libx)    
        MESSAGE(FATAL_ERROR "libX not found")  
    ENDIF(NOT libX)  

2. FIND_PATH(<VAR> name path1 path2 …)   VAR变量代表包含这个文件的路径  
  
3. FIND_PROGRAM(<VAR> name path1 path2 …)  
VAR变量代表包含这个程序的全路径  

4. FIND_PACKAGE(<name> [major.minor] [QUIET] [NO_MODULE] [[REQUIRED | COMPONENTS] [componets …]])  
用来调用预定义在CMAKE_MODULE_PATH下的Find<name>.cmake模块,你也可以自己定义Find<name>模块,通过SET(CMAKE_MODULE_PATH dir)将其放入工程的某个目录供工程使用  
```
## IF语法：  
  
```  
IF (expression)    
    COMMAND1(ARGS ...)    
    COMMAND2(ARGS ...)    
    ...  
ELSE (expression)    
    COMMAND1(ARGS ...)    
    COMMAND2(ARGS ...)    
    ...  
ENDIF (expression) # 一定要有ENDIF与IF对应  

IF (expression), expression不为：空,0,N,NO,OFF,FALSE,NOTFOUND或<var>_NOTFOUND,为真  
IF (not exp), 与上面相反  
IF (var1 AND var2)  
IF (var1 OR var2)  
IF (COMMAND cmd) 如果cmd确实是命令并可调用,为真  
IF (EXISTS dir) IF (EXISTS file) 如果目录或文件存在,为真  
IF (file1 IS_NEWER_THAN file2),当file1比file2新,或file1/file2中有一个不存在时为真,文件名需使用全路径  
IF (IS_DIRECTORY dir) 当dir是目录时,为真  
IF (DEFINED var) 如果变量被定义,为真  
IF (var MATCHES regex) 此处var可以用var名,也可以用${var}  
IF (string MATCHES regex)    
  
当给定的变量或者字符串能够匹配正则表达式regex时为真。比如：  
IF ("hello" MATCHES "ell")    
    MESSAGE("true")  
ENDIF ("hello" MATCHES "ell")  
数字比较表达式  
IF (variable LESS number)  
IF (string LESS number)  
IF (variable GREATER number)  
IF (string GREATER number)  
IF (variable EQUAL number)  
IF (string EQUAL number)    
```

## WHILE语法：
```  
WHILE(condition)    
    COMMAND1(ARGS ...)    
    COMMAND2(ARGS ...)    
    ...  
ENDWHILE(condition)
```