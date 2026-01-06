

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



# <span class="wathet"><font size=4>OpenMV-Linux环境配置</font></span>
## <font size=3>一、Docker Build</font>
<font size=2>

- <span class="blue">安装Docker在Ubuntu上运行</span>
  
```bash
sudo apt update
sudo apt install -y docker.io
sudo usermod -aG docker $USER  # 添加当前用户到 docker 组，重启终端生效
```

- <span class="blue">使用官方 Docker 构建固件</span>

 **1. 克隆 OpenMV 仓库（使用浅克隆加速）**

```bash
git clone --depth=50 git@github.com:openmv/openmv.git
cd openmv
```


**2. 配置Docker的镜像源**


<div style="background:#bff3f0;padding:10px;border-radius:6px;color:#333;">
在中国网络环境下：Docker Hub 的服务器在美国，受网络限制（GFW）影响，直接访问经常超时、连接失败或速度极慢。
</div>

在中国，最可靠的办法是配置 Docker 的 registry-mirrors，让 Docker 自动从国内镜像站拉取镜像。

```bash
# 1. 创建并编辑 Docker 配置文件
sudo mkdir -p /etc/docker
sudo nano /etc/docker/daemon.json

# 2. 粘贴复制以下内容到daemon.json文件中
{
  "registry-mirrors": [
    "https://docker.m.daocloud.io",
    "https://docker.1panel.live",
    "https://hub.rat.dev",
    "https://docker-cf.registry.cyou",
    "https://docker-0.unsee.tech",
    "https://hub.rat.dev",
    "https://dockerproxy.net",
    "https://docker.xuanyuan.me"
  ]
}

# 3. 保存退出（Ctrl+O → Enter → Ctrl+X），然后重启 Docker 服务
sudo systemctl daemon-reload
sudo systemctl restart docker
```

**3. 进入 Docker 目录并构建**

<spam class="red">这里要使用docker内部构建的编译器，就必须使用进入到docker文件夹中的make进行构建</span>

- OpenMV 项目专门在 docker/ 目录下提供了一个包装用的 Makefile（就是那个 make 文件，没有后缀）
- 这个 Makefile 的作用是：
  (1) 自动拉起（或进入）一个预配置好的 Docker 容器
  (2) 把整个 openmv 仓库挂载到容器内部
  (3) 在容器里执行真正的编译命令（使用 ARM 工具链、MicroPython 端口等）
- 如果调用仓库其他目录下的普通 make（比如根目录的 Makefile），它会尝试在宿主机本地直接编译，而不是在 Docker 容器里运行。这会导致：
  (1) 缺少 ARM GCC 工具链、依赖库等，报错一大堆;
  (2) 即使手动安装了工具链，也很容易因为环境不一致而出错;



<spam class="red">必须在 OpenMV 仓库的 boards/ 文件夹中添加自定义板子配置，才能使用 Docker 构建方式（make TARGET= 板型）来编译固件</span>

- OpenMV 的构建系统（Makefile 和 ports/stm32 的配置）会自动扫描根目录下的 boards/ 文件夹，寻找子文件夹作为支持的板型（TARGET）;
- 每个官方板型（如 OPENMV4、OPENMV4P、OPENMV_N6 等）都是 boards/ 下的一个独立子文件夹，里面包含：
  (1) mpconfigboard.h（板级 MicroPython 配置）;
  (2) mpconfigboard. mk（构建选项，如引脚定义、闪存布局等）;
  (3) omv_boardconfig.h（OpenMV 特定硬件配置，如传感器引脚、LED、存储等）;
  (4) 有时还有其他文件如 README 或特定脚本;
- 当运行 make TARGET=MYBOARD 时，构建脚本会将 boards/MYBOARD 作为 BOARD_DIR 使用。如果你的板子配置不在这个文件夹下，构建系统根本找不到它，无法设置正确的 TARGET.

```bash
cd ~/openmv/docker
# make TARGET=<你的板型>
make TARGET=OPENMV4 #针对H7
```

<div style="background:#e8f5e8;padding:10px;border-radius:6px;color:#333;">
ℹ️ TARGET 参数：指定你的 OpenMV 相机型号。常见选项（查看仓库 src/omv/boards/ 目录确认最新）：<br>
✅ 官方 OpenMV 系列（STM32）

| BSP名称     | 对应板子           | MCU              |
| ----------- | ------------------ | ---------------- |
| OPENMV2     | OpenMV Cam M4      | STM32F427        |
| OPENMV3     | OpenMV Cam M7      | STM32F767        |
| OPENMV4     | OpenMV Cam M7 Plus | STM32F769        |
| OPENMV4_H7  | OpenMV Cam H7      | STM32H743 / H750 |
| OPENMV4P    | OpenMV Cam M7 Pro  | STM32F769        |
| OPENMV_NANO | OpenMV Nano        | STM32F411        |

✅ OpenMV RT 系列（NXP）

| BSP名称       | 对应板子      | MCU             |
| ------------- | ------------- | --------------- |
| OPENMV_RT     | OpenMV RT1060 | NXP i.MX RT1062 |
| OPENMV_RT1020 | OpenMV RT1020 | NXP i.MX RT1020 |

</div>

<br>

**4. 自定义板级包的创建与编译**

<span class="blue">1. 复制一个最相似的官方板子作为模板</span>

```bash
# 在 openmv 仓库外面创建一个文件夹
mkdir ~/my_openmv_boards
cp -r ~/openmv/boards/OPENMV4 ~/my_openmv_boards/MY_OPENMV_H7
```

<span class="blue">2. 修改配置（进入这个新文件夹，修改以下关键文件）</span>

```bash
cd ~/my_openmv_boards/MY_OPENMV_H7
nano omv_boardconfig.h     # 修改传感器 DCMI 引脚、LED、存储等
nano mpconfigboard.h       # MicroPython 板级配置
nano mpconfigboard.mk      # 编译选项、闪存分区等
# 根据你的硬件差异修改对应内容
```

<span class="blue">3. 使用 Docker 构建（关键：用 GENERIC 作为 TARGET）</span>

```bash
cd ~/openmv/docker
# 正确方式：指定外部 BOARD 目录
make TARGET=GENERIC BOARD=~/my_openmv_boards/MY_OPENMV_H7
# 或者用相对路径（假设你当前在 openmv 根目录）
make TARGET=GENERIC BOARD=../my_openmv_boards/MY_OPENMV_H7
```


</font>

