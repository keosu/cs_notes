# conda quick reference

conda 是一个命令行的包管理和环境管理工具    
1. 包管理：安装、卸载、升级软件包，类似于pip  
2. 环境管理：解决不同版本库共存以及依赖问题，如分别使用python2和python3，类似与virtualenv  

**注**   
1. 此处只是一个快速参考，系统的学习，请参考[官方文档](https://conda.io/projects/conda/en/latest/user-guide/getting-started.html)  
2. 这里是官方的[cheetsheet](https://docs.conda.io/projects/conda/en/4.6.0/_downloads/52a95608c49671267e40c689e0bc00ca/conda-cheatsheet.pdf)  


## 基本配置

Conda默认的软件源在国外,速度非常的慢,我们可以将其更换为清华源,如果你是用的是教育网,那么软件下载速度会非常快.
```
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/
# 以上两条是Anaconda官方库的镜像

conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/conda-forge/
# 以上是Anaconda第三方库 Conda Forge的镜像
```

添加完成后可以使用conda info命令查看是否添加成功  

在安装软件时，也可以手动指定
```
conda install --channel conda-forge PACKAGENAME
```

## 包管理

功能 | 命令
-----|----
搜索包 | conda search PACKAGENAME
安装包 | conda install PACKAGENAME
卸载包 | conda remove PACKAGENAME
升级包 | conda update PACKAGENAME
包列表 | conda list

## 环境管理

功能 | 命令
-----|----
列出所有环境 | conda env list
创建环境 | conda create --name py37 python=3.7
克隆环境 | conda create --clone py37 --name py37-2
使用环境 | source activate py37 
删除环境 | conda env remove --name py37

## 发布conda包

上面主要介绍如何使用conda管理和使用包，我们也可以使用conda发布自己的包。
事实上，conda不局限于python库，你可以管理发布C++库，你需要按照一定的规范来组织文件、编写配置文件和脚本。  

[官方参考](https://docs.conda.io/projects/conda-build/en/latest/user-guide/tutorials/build-pkgs.html)
