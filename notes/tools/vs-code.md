# VS Code 

# Tips and Tricks

## 1 download remote server(ssh/wsl) extreamly slow

```sh
Attempt to connect, let it fail
On server, get the commit id

$ ls ~/.vscode-server/bin
553cfb2c2205db5f15f3ee8395bbd5cf066d357d
Download tarball replacing $COMMIT_ID with the the commit number from the previous step  
  https://update.code.visualstudio.com/commit:$COMMIT_ID/server-linux-x64/stable

Move tarball to ~/.vscode-server/bin/$COMMIT_ID/vscode-server-linux-x64.tar.gz

Extract tarball in this directory

$ cd ~/.vscode-server/bin/$COMMIT_ID
$ tar -xvzf vscode-server-linux-x64.tar.gz --strip-components 1
Connect again
```

# 调试配置(lauch.json)

**注意：** 更多配置，参见[官网](https://code.visualstudio.com/docs/editor/debugging)

## VS CODE混合调试c++和python
### 用到的文件
- func.cpp   : c++ 库源文件
- test.py    : 测试用python程序
- launch.json : vscode调试配置文件

#### func.cpp

```cpp
#include <iostream>
using namespace std;

int value = 1234;

extern "C" {

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

void setValue(int val) {
  cout << "before set, val = " << value << endl;
  value = val;
  cout << "after set, val = " << value << endl;
}
}
```
#### test.py
```python
from ctypes import *

lib = CDLL('/home/yijianlong/works/DNNDK/test/mix_py_cpp/libfunc.so')

a = lib.add(3, 4)
b = lib.sub(65, 23)
print("a = %d, b = %d" % (a, b))
lib.setValue(1111)from ctypes import *

lib = CDLL('./libfunc.so') #此处路径需确保库能被找到

a = lib.add(3, 4)
b = lib.sub(65, 23)
print("a = %d, b = %d" % (a, b))
lib.setValue(1111)
```

#### launch.json
```json
{ 
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Python",
      "type": "python",
      "program": "${file}",
      "request": "launch",
      "cwd": "${workspaceFolder}/"
    },
    {
      "name": "GDB Attach proc",
      "type": "cppdbg",
      "request": "attach",
      "program": "/usr/bin/python",
      "processId": "${command:pickProcess}",
      "MIMode": "gdb"
    }
  ]
}
```

### 步骤
0. 新建项目文件夹，放入源文件，配置lanuch.json
1. 将c++源文件生成动态库
    g++ -fPIC -shared func.cpp -o libfunc.so -g
2. 在python和c++源文件添加断点
3. 启动python调试配置python debug
4. 启动c++调试配置GDB Attach proc，并选择对应的proc


## VSCODE ARM remote debug 

### 示例配置文件
```json
{ 
  "version": "0.2.0",
  "configurations": [
    {
      "name": "ARM Remote Debug",
      "type": "cppdbg",
      "request": "launch",
      "program": "/path/to/your/debugging/file",
      "args": [],
      "stopAtEntry": false,
      "cwd": "/path/to/your/working/directory",
      "environment": [],
      "externalConsole": true,
      "MIMode": "gdb",
      "miDebuggerPath": "/full/path/to/your/debugger/aarch64-linux-gnu-gdb",
      "miDebuggerServerAddress": "localhost:11111",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ],
    }
  ]
}
```
### 主要配置项
- program:  
- cwd 
- miDebuggerPath : full path of your arm debugger
- miDebuggerServerAddress

### 步骤
1. 目标板上开启gdbserver
2. 调试机器上使用上述配置连接


## VSCODE other debug conf template
```json
{
  // Use IntelliSense to learn about possible attributes.
  // Hover to view descriptions of existing attributes.
  // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
  "version": "0.2.0",
  "configurations": [
    // python debug 
    {
      "name": "Python debug",
      "type": "python",
      "program": "${file}",
      "request": "launch",
      "cwd": "${workspaceFolder}"
    }, 
    // attach process
    {
      "name": "GDB Attach Proc",
      "type": "cppdbg",
      "request": "attach",
      "program": "/usr/bin/python3",
      "processId": "${command:pickProcess}",
      "MIMode": "gdb"
    },
    // config preLaunchTask
    {
      "name": "debug",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/a.out",
      "args": [
        "img/test.png"
      ],
      "stopAtEntry": false,
      "cwd": "${workspaceFolder}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ],
      "preLaunchTask": "taskName",
      "miDebuggerPath": "/usr/bin/gdb"
    },
  ]
}
```
tasks.json
```json
{

  "version": "2.0.0",
  "tasks": [

    {
      "type": "shell",
      "label": "g++ build file",
      "command": "/opt/rh/devtoolset-7/root/usr/bin/g++",
      "args": [
        "-g",
        "${file}",
        "-fno-elide-constructors",
        "-o",
        "${workspaceFolder}/a.out"
      ],
      "options": {
        "cwd": "/opt/rh/devtoolset-7/root/usr/bin"
      }
    }
  ]
}
```


    
   ## typescript
    
    
 ```json
    
    {
      "name": "Current TS File",
      "type": "node",
      "request": "launch",
      "args": ["${relativeFile}"],
      "runtimeArgs": ["--nolazy", "-r", "ts-node/register"],
      "sourceMaps": true,
      "cwd": "${workspaceRoot}",
      "protocol": "inspector",
  }
```
