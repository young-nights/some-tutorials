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


# <span class="wathet"><font size=4> OpenClaw的本地部署 </font></span>
<font size=3>

## <font size=3>Docker的安装</font>

### <font size=2>前置条件检查</font>
```bash
# 1. 刷新本地 APT 软件源索引
sudo apt update

# 2. 安装4个关键工具
#     - ca-certificates ：提供 HTTPS 证书信任链（让 curl 等工具能安全访问 https 网站）
#     - curl            ：命令行下载工具，用于抓取 Docker 的 GPG 公钥
#     - gnupg           ：处理 GPG 密钥的工具（用于验证软件源签名，防止中间人攻击）
#     - lsb-release     ：查询当前 Ubuntu 发行版代号（如 focal），用于动态生成 repo 地址
sudo apt install -y ca-certificates curl gnupg lsb-release

# 3. 现代 APT（Ubuntu 20.04+）推荐把第三方源的 GPG 密钥统一放在这个目录下
sudo mkdir -p /etc/apt/keyrings

# 4. 这个密钥是 Docker 签名所有 deb 包的“身份证”。APT 用它验证下载的 docker-ce 等包是否被篡改
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg

# 5. 告诉 APT “去哪里找 Docker 的包”。没有这一步，系统不知道 Docker 包的存在
echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

# 6. 第一次 update 的时候 Docker 源还没加，所以必须再跑一次才能看到 docker-ce 等包
sudo apt update

# 7. 真正安装 Docker
#     - docker-ce             ：Docker Engine 主程序（daemon）
#     - docker-ce-cli         ：命令行客户端（docker 命令）
#     - containerd.io         ：容器运行时（Docker 底层依赖）
#     - docker-compose-plugin ：Docker Compose v2 插件（就是我们需要的 docker compose 命令）
sudo apt install -y docker-ce docker-ce-cli containerd.io docker-compose-plugin


# 8. 验证版本
docker --version
docker compose version

# 9. 把当前用户加进 docker 组（避免每次 sudo）
sudo usermod -aG docker $USER
newgrp docker
```

### <font size=2>Docker Compose 安装</font>

<span class="red"><font size=2>如果之前系统上安装了docker，但是没有安装docker compose，就执行以下操作</font></span>



```bash
# 1. 如果之前是用官方 Docker 仓库安装的 Docker（即有 /etc/apt/sources.list.d/docker.list 文件）
sudo apt update
sudo apt install docker-compose-plugin -y

# 2. 安装验证
docker compose version

# 3.  如果上面命令提示包找不到（常见于用 snap/apt install docker.io 安装的 Docker）
# 3.1 创建插件目录（针对当前用户）
mkdir -p ~/.docker/cli-plugins/

# 下载最新版 Compose v2 的二进制文件（amd64/x86_64 架构，大部分服务器都是这个）
# 可以去 https://github.com/docker/compose/releases 看最新版本，替换下面 v2.24.7 为当前最新
curl -SL https://github.com/docker/compose/releases/download/v2.24.7/docker-compose-linux-x86_64 -o ~/.docker/cli-plugins/docker-compose

# 赋予执行权限
chmod +x ~/.docker/cli-plugins/docker-compose

# 验证
docker compose version

```


## <font size=3>推荐部署方式：官方一键脚本（最简单）</font>

```bash
# 克隆官方仓库（包含 docker-compose.yml 和 docker-setup.sh）
git clone https://github.com/openclaw/openclaw.git
cd openclaw

# 赋予执行权限并运行（会自动 build 镜像 + 运行 onboarding）
chmod +x docker-setup.sh
./docker-setup.sh
```

![onboard面板](./images/openclaw-config-1.png)

### 1. 等待部署完成，进入onbaord配置
**<span class="red">这里选择Yes</span>**
![onboard配置1](./images/openclaw-config-2.png)

**<span class="red">重新进入 onboarding 界面</span>**
```bash
# 在配置过程中如果不小心退出了 onboarding 界面，输入以下命令，重新启动 onboarding
# --rm          ：跑完自动清理临时容器（干净）
# openclaw-cli  ：这是 docker-compose.yml 里定义的 CLI 服务名，用于跑 openclaw 命令
# onboard       ：就是 onboarding wizard 的子命令
docker compose run --rm openclaw-cli onboard

```

**<span class="red">选择QuickStart（快速开始）</span>**
![onboarding 配置2](./images/openclaw-config-3.png)

**<span class="red">选择大模型（推荐使用minimax）</span>**
![onboarding 配置3](./images/openclaw-config-4.png)

**<span class="red">选择连接的设备用于对话</span>**
![onboarding 配置4](./images/openclaw-config-5.png)


</font>

