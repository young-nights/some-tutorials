
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


# <span class="wathet"><font size=4>基于STM32H750VBT6的OpenMV固件烧录方法</font></span>
## <font size=3>一、OpenMV-Version1.0 版本的固件烧录方式</font>
<font size=2>
<div style="background:#e8f5e8;padding:10px;border-radius:6px;color:#333;">
ℹ️ 硬件电路详见立创EDA工程 <span class="red">"OpenMV4_STM32H705VBT6"</span>。
<br>
ℹ️ OpenMV 固件烧录方式采用 USB-DFU 方式进行烧录。
<br>
</div>


在 ST 官网下载 STM32CubeProgrammer，确保开发板进入 DFU 模式。打开计算机的设备管理会看到或在打开 OpenMV IDE 时会提示你当前处于 DFU 模式需要升级固件。如果无法进入试一下下面的方法：
调转一下type-c的接口再插入
按住BOOT键之后按下RST键最后全部松开
检查一下板子的焊接特别时type-c接口。




</font>
















