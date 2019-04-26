
# Git cheet sheet

## 回到远程仓库的状态 
> git fetch --all && git reset --hard origin/master 

## 重设第一个 commit

也就是把所有的改动都重新放回工作区，并**清空所有的 commit**，这样就可以重新提交第一个 commit 了
> git update-ref -d HEAD 

## 展示差异 diff

| 说明                                          | 命令                             |
| --------------------------------------------- | -------------------------------- |
| 输出**工作区**和**暂存区**的差异              | git diff                         |
| 任意两个 commit 之间的文件变动                | git diff <commit-id> <commit-id> |
| 输出**暂存区**和最近commit的差异              | git diff --cached                |
| 输出**工作区**、**暂存区** 和最近commit的差异 | git diff HEAD                    |


## 分支操作 branch

| 说明                             | 命名                                               |
| -------------------------------- | -------------------------------------------------- |
| 列出本地分支                     | git branch                                         |
| 列出远程分支                     | git branch -r                                      |
| 列出所有分支                     | git branch -a                                      |
| 展示本地分支关联远程仓库的情况   | git branch -vv                                     |
| 创建并切换到本地分支             | git checkout -b <branch-name>                      |
| 快速切换到上一个分支             | git checkout -                                     |
| 从远程分支中创建并切换到本地分支 | git checkout -b <branch-name> origin/<branch-name> |
| 删除本地分支                     | git branch -d <local-branchname>                   |
| 删除远程分支                     | git push origin --delete <remote-branchname>       |
|                                  | git push origin :<remote-branchname>               |
| 关联远程分支                     | git branch -u origin/mybranch                      |
|                                  | git push origin/mybranch -u                        |
| 重命名本地分支                   | git branch -m <new-branch-name>                    |

## 标签操作 tag

| 说明                   | 命名                                                             |
| ---------------------- | ---------------------------------------------------------------- |
| 查看标签               | git tag                                                          |
| 展示当前分支的最近的   | git describe --tags --abbrev=0                                   |
| 查看标签详细信息       | git tag -ln                                                      |
| 本地创建标签           | git tag <tagname>                                                |
| 本地创建标签           | git tag -a <tagname> -m "msg" <commit-id>                        |
| 推送标签到远程仓库     | git push origin <local-version-number>                           |
| 推送所有标签到远程仓库 | git push origin --tags                                           |
| 删除本地标签           | git tag -d <tag-name>                                            |
| 删除远程标签           | **先删除本地标签**         git push origin :refs/tags/<tag-name> |
| 切回到某个标签         | git checkout -b branch_name tag_name                             |





## 回滚

### 恢复删除的文件
| 放弃工作区的修改 | git checkout <file-name> |
| 放弃所有修改 | git checkout . |

```sh
git rev-list -n 1 HEAD -- <file_path> #得到 deleting_commit
git checkout <deleting_commit>^ -- <file_path> #回到删除文件 deleting_commit 之前的状态
```
### 恢复到某一次commit
```sh
git revert <commit-id> # 以新增一个 commit 的方式还原某一个 commit 的修改
git reset <commit-id>  #默认就是-mixed参数。
git reset –mixed HEAD^  #回退至上个版本，它将重置HEAD到另外一个commit,并且重置暂存区以便和HEAD相匹配，但是也到此为止。工作区不会被更改。
git reset –soft HEAD~3  #回退至三个版本之前，只回退了commit的信息，暂存区和工作区与回退之前保持一致。如果还要提交，直接commit即可  
git reset –hard <commit-id>  #彻底回退到指定commit-id的状态，暂存区和工作区也会变为指定commit-id版本的内容
```

## 显示本地更新过 HEAD 的 git 命令记录

每次更新了 HEAD 的 git 命令比如 commit、amend、cherry-pick、reset、revert 等都会被记录下来（不限分支），就像 shell 的 history 一样。
这样你可以 reset 到任何一次更新了 HEAD 的操作之后，而不仅仅是回到当前分支下的某个 commit 之后的状态。

```sh
git reflog
```

## 修改上一个 commit 的描述

如果暂存区有改动，同时也会将暂存区的改动提交到上一个 commit

```sh
git commit --amend
```
| 说明                 | 命名                                                          |
| -------------------- | ------------------------------------------------------------- |
| 查看 commit 历史     | git log                                                       |
| 查看某段代码是谁写的 | git blame <file-name>                                         |
| 修改作者名           | git commit --amend --author='Author Name <email@address.com>' |
| 修改远程仓库的 url   | git remote set-url origin <URL>                               |
| 增加远程仓库         | git remote add origin <remote-url>                            |
| 列出所有远程仓库     | git remote                                                    |
| 查看两个星期内的改动 | git whatchanged --since='2 weeks ago'                         |

## 把 A 分支的某一个 commit，放到 B 分支上

这个过程需要 `cherry-pick` 命令，[参考](http://sg552.iteye.com/blog/1300713#bc2367928)

```sh
git checkout <branch-name> && git cherry-pick <commit-id>
```

## 给 git 命令起别名

简化命令

```sh
git config --global alias.<handle> <command>
git config --global alias.st status # e.g. git status 改成 git st
```

## stash

| 说明                                        | 命令                                    |
| ------------------------------------------- | --------------------------------------- |
| 存储当前的修改，但不用提交 commit           | git stash                               |
| 保存当前状态，包括 untracked 的文件         | git stash -u                            |
| 展示所有 stashes                            | git stash list                          |
| 回到某个 stash 的状态                       | git stash apply <stash@{n}>             |
| 回到最后一个 stash 的状态，并删除这个 stash | git stash pop                           |
| 删除所有的 stash                            | git stash clear                         |
| 从 stash 中拿出某个文件的修改               | git checkout <stash@{n}> -- <file-path> |

## 显示文件

| 说明                      | 命令                                        |
| ------------------------- | ------------------------------------------- |
| 展示所有 tracked 的文件   | git ls-files -t                             |
| 展示所有 untracked 的文件 | git ls-files --others                       |
| 展示所有忽略的文件        | git ls-files --others -i --exclude-standard |

## 强制删除 untracked 的文件

可以用来删除新建的文件。如果不指定文件文件名，则清空所有工作的 untracked 文件。`clean` 命令，**注意两点**：
1. clean 后，删除的文件无法找回
2. 不会影响 tracked 的文件的改动，只会删除 untracked 的文件

```sh
git clean <file-name> -f
```

## 强制删除 untracked 的目录

可以用来删除新建的目录，**注意**:这个命令也可以用来删除 untracked 的文件。详情见上一条

```sh
git clean <directory-name> -df
```

## 展示简化的 commit 历史
```sh
git log --pretty=oneline --graph --decorate --all
```

| 分支导出文件 |git bundle create <file> <branch-name>
|文件导入分支|git clone repo.bundle <repo-dir> -b <branch-name>|

## 执行 rebase 之前自动 stash

```sh
git rebase --autostash
```

## 从远程仓库根据 ID，拉下某一状态，到本地分支

```sh
git fetch origin pull/<id>/head:<branch-name>
```

## 详细展示一行中的修改

```sh
git diff --word-diff
```

## 清除 gitignore 文件中记录的文件

```sh
git clean -X -f
```

## 展示所有 alias 和 configs

**注意：** config 分为：当前目录（local）和全局（golbal）的 config，默认为当前目录的 config

```sh
git config --local --list (当前目录)
git config --global --list (全局)
```

## 展示忽略的文件
```sh
git status --ignored
```

## commit 历史中显示 Branch1 有的，但是 Branch2 没有 commit
```sh
git log Branch1 ^Branch2
```

## 在 commit log 中显示 GPG 签名
```sh
git log --show-signature
```

## 删除全局设置

```sh
git config --global --unset <entry-name>
```

## 新建并切换到新分支上，同时这个分支没有任何 commit

相当于保存修改，但是重写 commit 历史

```sh
git checkout --orphan <branch-name>
```

## 展示任意分支某一文件的内容

```sh
git show <branch-name>:<file-name>
```

## clone 下来指定的单一分支
```sh
git clone -b <branch-name> --single-branch https://github.com/user/repo.git
```

## 忽略某个文件的改动

关闭 track 指定文件的改动，也就是 Git 将不会在记录这个文件的改动

```sh
git update-index --assume-unchanged path/to/file
```

恢复 track 指定文件的改动

```sh
git update-index --no-assume-unchanged path/to/file
```

## 忽略文件的权限变化

不再将文件的权限变化视作改动

```sh
git config core.fileMode false
```

## 以最后提交的顺序列出所有 Git 分支

最新的放在最上面

```sh
git for-each-ref --sort=-committerdate --format='%(refname:short)' refs/heads/
```

## 在 commit log 中查找相关内容

通过 grep 查找，given-text：所需要查找的字段


```sh
git log --all --grep='<given-text>'
```

## 把暂存区的指定 file 放到工作区中

不添加参数，默认是 `-mixed`

```sh
git reset <file-name>
```

## 强制推送

```sh
git push -f <remote-name> <branch-name>
```

## 一图详解

![](./assets/git.png)

## 优雅的提交Commit信息

使用[Angular团队提交规范](https://github.com/angular/angular.js/blob/master/DEVELOPERS.md#-git-commit-guidelines)

主要有以下组成

* 标题行: 必填, 描述主要修改类型和内容
* 主题内容: 描述为什么修改, 做了什么样的修改, 以及开发的思路等等
* 页脚注释: 放 Breaking Changes 或 Closed Issues

常用的修改项

* type: commit 的类型
* feat: 新特性
* fix: 修改问题
* refactor: 代码重构
* docs: 文档修改
* style: 代码格式修改, 注意不是 css 修改
* test: 测试用例修改
* chore: 其他修改, 比如构建流程, 依赖管理.
* scope: commit 影响的范围, 比如: route, component, utils, build...
* subject: commit 的概述
* body: commit 具体修改内容, 可以分为多行
* footer: 一些备注, 通常是 BREAKING CHANGE 或修复的 bug 的链接.

