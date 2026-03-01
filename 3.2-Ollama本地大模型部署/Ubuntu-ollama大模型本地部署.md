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



# <span class="wathet"><font size=4> Ubuntu 下的 Ollama 的本地部署 </font></span>

## <span class="wathet"><font size=3> 简要概述 </font></span>

<div style="background:#e8f5e8;padding:10px;border-radius:6px;color:#333;">

<font size=2>
OpenClaw 的核心卖点就是“能够操作电脑文件、跑命令、整理资料”，所以它设计上就是要访问文件的。但是如果让 openclaw 直接部署在宿主机，也就是使用者常用的 Windows 环境中，存在很高的安全风险，因此需要把 openclaw 部署进行隔离。
</font>
</div>

<br>

## <span class="wathet"><font size=3> 部署前准备 </font></span>




