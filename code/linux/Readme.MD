# linux programming 

## shared memory test

```bash
gcc shmread.c -o shmread
gcc shmwrite.c -o shmwrite
# 打开两个终端测试用shared memory 通信
```

## socket test (UDP)

```bash
gcc socketserver.c -o server
gcc socketclient.c -o client
# 打开两个终端测试socket UDP通信
./server
./client localshot
```
