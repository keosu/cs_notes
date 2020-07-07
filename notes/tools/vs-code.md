# VS Code 

# Tips and Tricks

## 1 download remote server(ssh/wsl) extreamly slow

```
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
