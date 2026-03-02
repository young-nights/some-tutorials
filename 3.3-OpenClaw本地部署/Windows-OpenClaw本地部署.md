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
```

3. 运行 docker-setup.sh

```bash
# 如果用 PowerShell，可能需要用 bash 执行脚本
bash ./docker-setup.sh

# 或者直接（如果已安装 Git Bash 或 WSL）
./docker-setup.sh
```

4. 验证配置是否有效

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

