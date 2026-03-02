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

# <span class="wathet"><font size=4> Windows 下的 OpenClaw 的本地部署 </font></span>

## <span class="wathet"><font size=3> 简要概述 </font></span>

<div style="background:#e8f5e8;padding:10px;border-radius:6px;color:#333;">

<font size=2>
OpenClaw 的核心卖点就是“能够操作电脑文件、跑命令、整理资料”，所以它设计上就是要访问文件的。但是如果让 openclaw 直接部署在宿主机，也就是使用者常用的 Windows 环境中，存在很高的安全风险，因此需要把 openclaw 部署进行隔离。
</font>
</div>

<br>

## <span class="wathet"><font size=3> 部署前准备 </font></span>

<div style="background:#e8f5e8;padding:10px;border-radius:6px;color:#333;">

<font size=2>

- **Docker Desktop：** 推荐启用 WSL2 后端，以获得更好性能和兼容性
- **Git：** 用于克隆仓库
- **Windows特定注意：** Docker Desktop 会自动处理路径映射，但 Windows 路径使用反斜杠（\），在 Docker Compose 中需转换为正斜杠（/）。如果使用 WSL2，确保 WSL2 已启用（在 PowerShell 中运行 wsl --install）
- **权限：** 以管理员身份运行命令提示符或 PowerShell

### **<span class="wathet"><font size=2> Step1：克隆 OpenClaw 仓库**</font></span>

1. 打开 PowerShell 或 命令提示符
2. 克隆官方仓库 & 进入仓库目录

```bash
# 1. 克隆仓库
git clone https://github.com/openclaw/openclaw

# 2. 进入仓库目录
cd openclaw
```

### **<span class="wathet"><font size=2> Step2：设置 Docker 脚本**</font></span>
OpenClaw 提供了一个脚本 `docker-setup.sh` 来自动化构建和启动 Docker 环境。这会构建 gateway 镜像、运行 onboarding 向导，并通过 Docker Compose 启动服务。

1. 因为是 Windows，`docker-setup.sh` 是 Bash 脚本。因此需要在 WSL2 中运行，或者使用 Git Bash。如果未安装 Git Bash，从 Git 官网下载。
2. 设置三个环境变量

```bash
# 1. 安装额外 apt 包（构建 gateway 镜像时永久安装）
# 示例：安装 git、curl、jq（常用工具），可以加更多，用空格分隔
$env:OPENCLAW_DOCKER_APT_PACKAGES = "git curl jq ffmpeg ripgrep build-essential"

# 2. 额外主机目录绑定挂载（让 OpenClaw 能访问 Windows 的特定文件夹）
# 格式：Windows路径:/容器内路径:权限（ro=只读，rw=读写），多个用逗号分隔
# 注意：路径用正斜杠 /，不要用反斜杠 \
# 示例：映射你的 Work 文件夹（读写）、Documents 文件夹（只读）
$env:OPENCLAW_EXTRA_MOUNTS = "C:/Users/YourName/Work:/home/node/workspace:rw,C:/Users/YourName/Documents:/home/node/docs:ro"

# 替换 YourName 为你的实际 Windows 用户名，例如：
# $env:OPENCLAW_EXTRA_MOUNTS = "C:/Users/Administrator/Pictures:/home/node/pictures:rw"

# 3. 使用命名卷持久化整个 /home/node 目录（包含 .openclaw 配置等）
# 推荐使用一个有意义的名字，例如 openclaw_home
$env:OPENCLAW_HOME_VOLUME = "openclaw_home"

#-------------------------------------------------------------------------------------------------------------------------

# 验证是否映射成功
# 列出容器里 pictures 目录的内容，应该看到你 Windows Pictures 文件夹里的文件
docker compose exec openclaw-gateway ls -la /home/node/pictures

# 如果想看前几个文件示例
docker compose exec openclaw-gateway ls /home/node/pictures | head -n 10

# 如果路径映射设置错误，使用指令取消
Remove-Item Env:OPENCLAW_EXTRA_MOUNTS -ErrorAction SilentlyContinue
```

3. 运行 docker-setup.sh

```bash
# 如果用 PowerShell，可能需要用 bash 执行脚本
bash ./docker-setup.sh

# 或者直接（如果已安装 Git Bash 或 WSL）
./docker-setup.sh
```
<div style="background:#ffcc99;padding:10px;border-radius:6px;color:#333;">

**<span class="red">报错： 此处运行  bash ./docker-setup.sh 会出现报错</span>**

![运行报错](./images/openclaw-widnows-1.png)

```bash
# 1. 在Powershell中执行查看默认发行版本
wsl --list --verbose
```
![执行结果](./images/openclaw-widnows-2.png)

```text
分析报错原因：
(1) docker-desktop 是 Docker Desktop 自动创建的极简 WSL 发行版（基于轻量工具链，比如 busybox 或 scratch 风格），它故意没有安装 /bin/bash（或其他完整 shell），目的是只跑 Docker 引擎的后端，不用于交互。
(2) Windows 把这个 docker-desktop 设成了默认 WSL distro（星号 * 表示默认）
(3) 任何时候你运行 bash、wsl（无参数）、或某些工具（如 OpenClaw/clawdock 的脚本）试图启动 bash 时，WSL relay 层就会去调用默认 distro 的 /bin/bash → 不存在 → 报错.
```

**<span class="green">解决问题方法：</span>**

```bash
# 1. 先检查/安装一个正常的 Ubuntu distro（如果已经有了就跳过安装）
wsl --install -d Ubuntu
# 这会从 Microsoft Store 下载并安装最新的 Ubuntu
# 安装完后，它会自动启动一次，让你设置用户名和密码

# 2. 把 Ubuntu 设置成默认
wsl --set-default Ubuntu

# 3. 启动 wsl中的 Ubuntu
wsl -d Ubuntu
# 4. 查看版本信息
lsb_release -a

# 5. 再次运行 bash ./docker_setup.sh
bash ./docker_setup.sh 
```

**<span class="red">Docker Compose not available 报错</span>**

![执行结果](./images/openclaw-widnows-3.png)

```text
问题分析：
OpenClaw 的 docker-setup.sh 脚本在检查 Docker Compose 时，用的是旧语法 docker-compose（V1 版本）。
但现代 Docker Desktop（4.10+ 以后，默认启用 Compose V2）用的是插件形式：命令是 docker compose（无连字符），而不是 docker-compose。
所以脚本检测不到旧的 docker-compose 命令 → 报错退出。

解决方案（在WSL Ubuntu 里操作）：
setp1：先确认 Docker Desktop 已运行，且 WSL 集成已开启（Docker Desktop → Settings → Resources → WSL Integration → 勾选你的 Ubuntu）
step2：重启 Docker Desktop
```
![step1](./images/openclaw-widnows-4.png)




**<span class="red">wsl代理网络问题</span>**

wsl: 检测到 localhost 代理配置，但未镜像到 WSL。NAT 模式下的 WSL 不支持 localhost 代理。
```text
原因分析:
由于 Windows 主机开启了本地代理（localhost 代理，比如 Clash、V2Ray、Shadowsocks 等工具设置的系统代理，通常是 127.0.0.1:1080/7890 等端口），WSL 默认用 NAT 网络模式，localhost (127.0.0.1) 在 Windows 和 WSL 之间不互通，所以 WSL 无法自动使用 Windows 的代理。

修复方式：
在 Windows 用户目录下创建或编辑 .wslconfig 文件，路径：C:\Users\你的用户名\.wslconfig，然后在 .wslconfig 中填写以下内容并保存

[experimental]
autoMemoryReclaim=gradual
networkingMode=mirrored
dnsTunneling=true
firewall=true
autoProxy=true

保存后，在 PowerShell（管理员）运行：

wsl --shutdown

之后，再次打开wsl，或者 bash，警告就会消除

```

</div>


1. 验证配置是否有效

```bash
# 1. 检查 apt 包是否安装成功 
docker compose exec openclaw-gateway bash -c "which git && which curl && which jq"
# 如果输出路径，说明安装成功

# 2. 检查额外挂载是否生效
docker compose exec openclaw-gateway ls -la /home/node/pictures
# 可以看到你 Windows Pictures 文件夹里的文件

# 3. 检查命名卷是否创建
docker volume ls | findstr openclaw_home
# 可以看到类似 openclaw_openclaw_home 的卷

# 4. 查看生成的 compose 文件
docker-compose.yml  # 基础配置
docker-compose.extra.yml # 包含你额外挂载和 home 卷的配置（不要手动编辑它，下次运行 setup 脚本会覆盖）

```

### **<span class="wathet"><font size=2> Step3：启用官方 Sandbox 模式**</font></span>

Sandbox 模式使用 Docker 容器隔离代理工具（如 exec、read、write），防止 AI 操作影响主机。默认下，它不要求 gateway 完全在 Docker 中运行，但既然你选择 Docker 部署，它会无缝集成。


</font>
</div>


sk-tziH8ddIWrvxfxmIspvjcET6g7ojV7dso5fZarS1ARY2uSSm