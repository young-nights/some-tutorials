

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

<div style="background:#fff3e0;padding:10px;border-radius:6px;color:#333;">
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
    "https://dockerproxy.com",
    "https://docker.mirrors.ustc.edu.cn",
    "https://docker.nju.edu.cn",
    "https://docker.m.daocloud.io"
  ]
}

# 3. 保存退出（Ctrl+O → Enter → Ctrl+X），然后重启 Docker 服务
sudo systemctl daemon-reload
sudo systemctl restart docker
```

**3. 进入 Docker 目录并构建**

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




</font>





