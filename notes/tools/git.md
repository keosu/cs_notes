
# Git cheet sheet

Git 是一个分布式的版本管理工具 [官方文档](https://git-scm.com/docs)

## 一 快速使用入门

如果你使用github来托管你的项目，先新建一个项目，然后上传本地文件。
注意：需要在github中配置你机器的ssh key，以便能使用ssh方式访问你的远程仓库  

1. 如果需要创建一个新的仓库，使用git init 初始化，然后关联远程仓库  
```
echo "# your project" >> README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin git@github.com:yourname/reponame.git
git push -u origin master
```
2. 使用已有仓库，直接关联  
```
git remote add origin git@github.com:yourname/reponame.git
git push -u origin master
```
后面，如果你在本地更新了文件，使用git add filename/folername添加更改，使用git commit提交，然后使用git push来推送到远程仓库

更多命令参考，见[git cheetsheet](https://github.github.com/training-kit/downloads/github-git-cheat-sheet.pdf)

## 二 基本概念和流程

### 主要概念
我们先来理解下Git 工作区、暂存区和版本库概念  

- 工作区：就是当前能看到的目录。
- 暂存区：英文叫stage, 或index。一般存放在 ".git目录下" 下的index文件（.git/index）中，所以我们把暂存区有时也叫作索引（index）。
- 版本库：工作区有一个隐藏目录.git，这个不算工作区，而是Git的版本库。

![关系图](https://www.runoob.com/wp-content/uploads/2015/02/1352126739_7909.jpg)  

图中的 objects 标识的区域为 Git 的对象库，实际位于 ".git/objects" 目录下，里面包含了创建的各种对象及内容。 

- 当执行 "git add" 命令时，暂存区的目录树被更新，同时工作区修改（或新增）的文件内容被写入到对象库中的一个新的对象中，而该对象的ID被记录在暂存区的文件索引中。  
- 当执行提交操作（git commit）时，暂存区的目录树写到版本库（对象库）中，master 分支会做相应的更新。即 master 指向的目录树就是提交时暂存区的目录树。  
- 当执行 "git reset HEAD" 命令时，暂存区的目录树会被重写，被 master 分支指向的目录树所替换，但是工作区不受影响。    
- 当执行 "git rm --cached <file>" 命令时，会直接从暂存区删除文件，工作区则不做出改变。     
- 当执行 "git checkout ." 或者 "git checkout -- <file>" 命令时，会用暂存区全部或指定的文件替换工作区的文件。这个操作很危险，会清除工作区中未暂存的改动。 
- 当执行 "git checkout HEAD ." 或者 "git checkout HEAD <file>" 命令时，会用 HEAD 指向的 master 分支中的全部或者部分文件替换暂存区和以及工作区中的文件。这个命令也是极具危险性的，因为不但会清除工作区中未提交的改动，也会清除暂存区中未提交的改动。 


### 基本工作流程

- clone一个远程仓库或者init本地仓库并关联远程仓库
- 可以通过add添加文件改动
- 在提交之前查看更改(diff)。
- 提交更改(commit)，并将您的更改push到远程仓库。
- 其他用户更改提交后，使用pull获取远程更改。 

![工作流程图](http://www.yiibai.com/uploads/images/201707/0707/497150749_38351.png)

## 三 常用操作

### 展示差异 diff

| 说明                                          | 命令                             |
| --------------------------------------------- | -------------------------------- |
| 输出**工作区**和**暂存区**的差异              | git diff                         |
| 任意两个 commit 之间的文件变动                | git diff <commit-id> <commit-id> |
| 输出**暂存区**和最近commit的差异              | git diff --cached                |
| 输出**工作区**、**暂存区** 和最近commit的差异 | git diff HEAD                    |


### 分支操作 branch

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

### 标签操作 tag

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


### 回滚

#### 恢复删除的文件
| 放弃工作区的修改 | git checkout <file-name> |
| 放弃所有修改 | git checkout . |

```sh
git rev-list -n 1 HEAD -- <file_path> #得到 deleting_commit
git checkout <deleting_commit>^ -- <file_path> #回到删除文件 deleting_commit 之前的状态
```
#### 恢复到某一次commit
```sh
git revert <commit-id> # 以新增一个 commit 的方式还原某一个 commit 的修改
git reset <commit-id>  #默认就是-mixed参数。
git reset –mixed HEAD^  #回退至上个版本，它将重置HEAD到另外一个commit,并且重置暂存区以便和HEAD相匹配，但是也到此为止。工作区不会被更改。
git reset –soft HEAD~3  #回退至三个版本之前，只回退了commit的信息，暂存区和工作区与回退之前保持一致。如果还要提交，直接commit即可  
git reset –hard <commit-id>  #彻底回退到指定commit-id的状态，暂存区和工作区也会变为指定commit-id版本的内容
```

### 重设第一个 commit

也就是把所有的改动都重新放回工作区，并**清空所有的 commit**，这样就可以重新提交第一个 commit 了
> git update-ref -d HEAD 


### 显示本地更新过 HEAD 的 git 命令记录

每次更新了 HEAD 的 git 命令比如 commit、amend、cherry-pick、reset、revert 等都会被记录下来（不限分支），就像 shell 的 history 一样。
这样你可以 reset 到任何一次更新了 HEAD 的操作之后，而不仅仅是回到当前分支下的某个 commit 之后的状态。

```sh
git reflog
```

### 修改上一个 commit 的描述

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

### 把 A 分支的某一个 commit，放到 B 分支上

这个过程需要 `cherry-pick` 命令，[参考](http://sg552.iteye.com/blog/1300713#bc2367928)

```sh
git checkout <branch-name> && git cherry-pick <commit-id>
```

### 给 git 命令起别名

简化命令

```sh
git config --global alias.<handle> <command>
git config --global alias.st status # e.g. git status 改成 git st
```

### stash

| 说明                                        | 命令                                    |
| ------------------------------------------- | --------------------------------------- |
| 存储当前的修改，但不用提交 commit           | git stash                               |
| 保存当前状态，包括 untracked 的文件         | git stash -u                            |
| 展示所有 stashes                            | git stash list                          |
| 回到某个 stash 的状态                       | git stash apply <stash@{n}>             |
| 回到最后一个 stash 的状态，并删除这个 stash | git stash pop                           |
| 删除所有的 stash                            | git stash clear                         |
| 从 stash 中拿出某个文件的修改               | git checkout <stash@{n}> -- <file-path> |

### 文件操作

| 说明                      | 命令                                        |
| ------------------------- | ------------------------------------------- |
| 展示所有 tracked 的文件   | git ls-files -t                             |
| 展示所有 untracked 的文件 | git ls-files --others                       |
| 展示所有忽略的文件        | git ls-files --others -i --exclude-standard |
| 删除untrack的文件            | git clean <file-name> -f                   |
| 删除untrack的目录            | git clean <directory-name> -df             | 
| 清除 .gitignore 记录的文件   | git clean -X -f                            |

### 展示简化的 commit 历史
```sh
git log --pretty=oneline --graph --decorate --all
```

| 分支导出文件 |git bundle create <file> <branch-name>
|文件导入分支|git clone repo.bundle <repo-dir> -b <branch-name>|



```sh
### 执行 rebase 之前自动 stash
git rebase --autostash 

### 从远程仓库根据 ID，拉下某一状态，到本地分支 
git fetch origin pull/<id>/head:<branch-name> 

### 详细展示一行中的修改 
git diff --word-diff 

### 展示所有 alias 和 configs  
git config --local --list (当前目录)
git config --global --list (全局)

git status --ignored ### 展示忽略的文件 
git log Branch1 ^Branch2 ### commit 历史中显示 Branch1 有的，但是 Branch2 没有 commit 
git log --show-signature ### 在 commit log 中显示 GPG 签名 
git config --global --unset <entry-name>  ### 删除全局设置 

### 新建并切换到新分支上，同时这个分支没有任何 commit 
git checkout --orphan <branch-name>

git show <branch-name>:<file-name> ### 展示任意分支某一文件的内容 
git clone -b <branch-name> --single-branch https://github.com/user/repo.git  ### clone 下来指定的单一分支
git update-index --assume-unchanged path/to/file    ### 忽略某个文件的改动
git update-index --no-assume-unchanged path/to/file ### 恢复 track 指定文件的改动 
git config core.fileMode false ### 忽略文件的权限变化 
git for-each-ref --sort=-committerdate --format='%(refname:short)' refs/heads/ ### 以最后提交的顺序列出所有 Git 分支
git log --all --grep='<given-text>'  ### 在 commit log 中查找相关内容
git reset <file-name> ### 把暂存区的指定 file 放到工作区中 
git push -f <remote-name> <branch-name> ### 强制推送
```


## 附 优雅的提交Commit信息

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

