## 基本概念：
- container  
  容器。可以把每个 container 看做是一个独立的主机。 container 的创建通常有一个 image 作为其模板。类比成虚拟机的话可以理解为 image 就是虚拟机的镜像，而 container 就是一个个正在运行的虚拟机。一个虚拟机镜像可以创建出多个运行的虚拟主机且相互独立。 注意：container 一旦创建如果没有用 rm 命令移除，将会一直存在。所以用完后记得删除哦。

- image  
  镜像。image 相当于 container 的模板，container 创建后里面有什么软件完全取决于它使用什么 image 。image 可以通过 container 创建（相当于把此时 container 的状态保存成快照），也可以通过 Dockerfile （一个文本文件，里面使用 docker 规定的一些写法）来创建。其中通过 Dockerfile 创建的方法能让环境配置和代码一起被版本库一起管理。

- registry  
  存放镜像的仓库。只要能连接到 registry 每个人都可以很方便地通过 pull 命令从仓库中获取镜像。docker 默认使用的仓库是 docker hub，国内可以使用 DaoCloud 来建立 Mirror 连接到 docker hub，进而加快获取 image 的速度。



## 常用命令

- 导入导出

 | command                                       | desc     |
 | --------------------------------------------- | -------- |
 | docker save <image id>  >  image.tar          | 保存镜像 |
 | docker load < image.tar                       | 加载镜像 |
 | docker export <container id>  > container.tar | 导出容器 |
 | docker import container.tar                   | 导入容器 |


- image 相关：

 | command                   | desc                                |
 | ------------------------- | ----------------------------------- |
 | docker images             | 查看本地所有 image                  |
 | docker search <name>      | 在 registry 中搜索镜像              |
 | docker pull <name>:<tag>  | 从 registry 中获取镜像（默认latest) |
 | docker tag <imgid> <name> | 给 image 打 tag                     |
 | docker push <name>        | 把本地 image 上传到 registry 中     |
 | docker rmi <image>        | 删除本地 image                      |

- container 相关：

| command                        | desc         |
| ------------------------------ | ------------ |
| docker create                  | 创建        |
| docker run                     | 运行         |
| docker ps                      | 列表         |
| docker logs -f [container]     |
| docker port [container] [port] |
| docker top [container]         | 查看进程     |
| docker inspect [container]     | 查看容器信息 |
| docker stop [container]        |
| docker kill [container]        |
| docker start [container]       |
| docker restart [container]     |
| docker rm [container]          |              |
