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


# <span class="wathet"><font size=4>Anaconda使用笔记 </font></span>
<font size=3>

## <font size=3>Anaconda指令</font>

### <font size=2>查看信息</font>
```bash
# 1. 查看 conda 版本
conda --version

# 2. 查看 conda 详细配置（渠道、路径等）
conda info

# 3. 列出所有虚拟环境（哪个是当前激活的用 * 标记）
conda info --envs
conda env list

# 4. 列出当前环境中所有已安装的包
conda list

# 5. 搜索某个包有哪些版本可用
conda search 包名
conda search --full --name 包名

```

### <font size=2>环境管理</font>

```bash
# 1. 创建环境
conda create -n 环境名 python=3.11

# 2. 激活环境

# 3. 退出当前环境（回到 base）
conda deactivate

# 4. 删除环境
conda env remove -n 环境名
conda remove -n 环境名 --all

# 5. 克隆环境（复制一个一模一样的）
conda create -n 新环境名 --clone 旧环境名

# 6. 重命名环境（conda 没有直接 rename，要两步） - 先克隆 → 再删旧的

```

### <font size=2>包管理</font>

```bash
# 1. 安装包（当前激活的环境）
conda install 包名

# 2.同时装多个包
conda install 包1 包2 包3


```


</font>













