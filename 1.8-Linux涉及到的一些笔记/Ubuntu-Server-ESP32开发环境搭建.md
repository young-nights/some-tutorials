<style>
.highlight{
  color: white;
  background: linear-gradient(90deg, #ff6b6b, #4ecdc4);
  padding: 5px;
  border-radius: 5px;
}

.mint_green{
  color: white;
  background: #adcdadf2; 
  padding: 5px;
  border-radius: 5px;
}

.red {
  color: #ff0000;
}
.green {
  color:rgb(10, 162, 10);
}
.blue {
  color:rgb(17, 0, 255);
}

.wathet {
  color:rgb(0, 132, 255);
}
</style>


<font size=2>

```bash
1.安装工具链
sudo apt-get install git wget flex bison gperf python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0 net-tools

2.新建esp32文件夹
mkdir esp32

3.进入esp32文件夹安装esp-gitee-tools工具
git clone https://gitee.com/EspressifSystems/esp-gitee-tools.git

4.执行gitee工具切换镜像脚本
cd esp-gitee-tools
./jihu-mirror.sh set

5.进入esp32文件夹并安装esp-idf工具
git clone --recursive https://github.com/espressif/esp-idf.git

6.进入esp-idf文件夹并切换ESP32的版本为v5.2版本
git checkout v5.2
git submodule update --init --recursive

7.更换pip源
pip config set global.index-url http://mirrors.aliyun.com/pypi/simple
pip config set global.trusted-host mirrors.aliyun.com

8.安装编译工具
../esp-gitee-tools/install.sh

9.配置esp-idf环境
【方法一】
ESP32环境配置idf.py的环境变量配置方法（永久有效）
1.切换在根目录下，输入ls -al
2.可以看到有一个.profile文件
3.输入vim .profile使用vim对该文件进行编译
4.在文中中插入 source esp32/esp-idf/export.sh
	
【方法二】
ESP32环境配置idf.py的环境变量配置方法（永久有效）						
1.在根目录下输入   echo $SHELL	 查询命令行语言
2.输入   nano ~/.bashrc	打开文件
3.将 alias get_idf='. $HOME/esp32/esp-idf/export.sh' 加入到文件中
4.每次进入时需要idf.py时，输入  get-idf   就可以配置环境了
```

</font>


---

## <font size=3>创建ESP32开发环境的Docker镜像</font>
<font size=2>

### 1. Dockerfile 的编写

<span class="red">遇到的问题：</span>当步骤5-6中最后不叫 --force 时，docker build 会构建失败，原因是使用的 jihu-mirror 镜像站中的子模块内容与 github 中的版本不一致导致的
<span class="red">解决的方法：</span>在整个 submodule update 前加 --force


```bash

FROM ubuntu:24.04

# 避免交互式提示
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && apt-get install -y \
    git wget flex bison gperf \
    python3 python3-pip python3-venv \
    cmake ninja-build ccache \
    libffi-dev libssl-dev dfu-util libusb-1.0-0 net-tools \
    && rm -rf /var/lib/apt/lists/*

# 创建工作目录（这个工作目录是在容器内部的）
WORKDIR /esp32

# 步骤3-4: 克隆 esp-gitee-tools 并切换极狐镜像
RUN git clone https://gitee.com/EspressifSystems/esp-gitee-tools.git \
    && cd esp-gitee-tools \
    && ./jihu-mirror.sh set

# 步骤5-6: 克隆 ESP-IDF v5.2（使用 --recursive）
RUN git clone --recursive https://github.com/espressif/esp-idf.git \
    && cd esp-idf \
    && git checkout v5.2 \
    && git submodule update --init --recursive --force

# 步骤7: 更换 pip 为阿里云源
RUN pip config set global.index-url http://mirrors.aliyun.com/pypi/simple \
    && pip config set global.trusted-host mirrors.aliyun.com

# 步骤8: 安装 ESP-IDF 工具链（只针对 esp32，加速下载）
RUN cd esp-idf \
    && ./install.sh esp32  

# 配置环境（类似你的方法二：添加 alias）
RUN echo "alias get_idf='. /esp32/esp-idf/export.sh'" >> /root/.bashrc

# 默认进入交互式 shell
CMD ["/bin/bash"]

```



### 2. images的构建 
Docker 构建镜像时，需要知道 Dockerfile 在哪里，以及 构建上下文（context） 是什么目录。

```bash
# 正确的用法
docker build [选项] -t 镜像名:标签  路径
# 其中的 路径 必须明确指定，通常是：
#  . 表示当前目录（最常用）
#  或者具体路径，如 /home/user/esp32/docker
```
现在在 ~/esp32/docker 目录下，正确执行：

```bash
docker build -t my-esp32-idf:v5.2 .
```

### 3. esp32-docker的使用


</font>

