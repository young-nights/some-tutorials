
<style>
.red-text {
  color: #ff0000;
  font-weight: bold;
}
.green-text {
  color:rgb(0, 162, 255);
  border: 1px solid gray;
}
</style>

<style>
.red {
  color: #ff0000;
}
.green {
  color:rgb(0, 162, 225);
}
.blue {
  color:rgb(17, 0, 255);
}
.cyan {
  color:rgba(119, 255, 0, 0.73);
}
</style>


# <span class="green"><font size=4>搭建Clion开发环境</font></span>
## <font size=3>下载FubeMX</font>
<font size=2>1. 点击进入FubeMX界面，点击下载STM32CubeCTL安装包，该安装包安装后在文件夹下会包含ST官方打包的STM32开发工具链，包含ARM-GCC、CMake、Ninja等工具；</font>
![下载FubeMX](./images/PGN1.png)

<br>

<font size=2>2. 点击进入Clion工作界面，点击"新建项目"，在左侧的选项栏中有针对嵌入式的STM32CubeMX选项，点击该选项，弹出配置页面；
<span class="red">注：这里Clion会自动检索CubeMX文件路径和CubeCTL编译器工具集路径，如果在安装STM32CubeMX和STM32CubeCTL时不是默认路径的话，需要自己手动修改路径！！！</span></font>

![设置路径](./images/PGN2.png)


## <font size=3>下载OpenOCD</font>
[OpenOCD下载链接](https://gnutoolchains.com/arm-eabi/openocd/ "OpenOCD下载链接")




# <span class="green"><font size=4>STM32CubeMX软件开发</font></span>
## <font size=3>生成代码</font>
### <font size=2>生成hal库代码</font>
<font size=2>1. 点击"启动STM32CubeMX",开始进行芯片配置，然后生成Hal库代码文件
<span class="red"><font size=2>注：这里重点说明一下生成代码配置页的一些配置</font></span>
- ==在配置生成代码页面，对生成环境设置为CMake，否则Clion对项目编译会报错==<br></font>

![代码生成配置](./images/PGN3.png)

<br>

- <font size=2>==粘贴代码路径，并将项目代码路径配置到CLion中==</font><br>
![复制路径](./images/PGN4.png)
![粘贴路径](./images/PGN5.png)


<font size=2>2. 配置完成，点击继续，会弹出"是否信任xx文件夹下的所有项目"以及“信任'xx'文件夹”,这里设置成全部信任</font>
![信任文件夹](./images/PGN6.png)
<br>

<font size=2>3. 配置默认工具链</font>
![配置工具链](./images/PGN7.png)

- <font size=2>==这里展示一下配置CubeCLT中的工具链==
(1)添加一个新的MinGW工具链，并修改其中的链接路径，都修改为CubeCLT中的工具链或者自己安装扩展的工具链
![新建工具链](./images/PGN8.png)
(2)选择修改工具链
![选择新工具链](./images/PGN9.png)
4. 点击确定即可进行HAL库的代码编程</font>

### <font size=2>添加FreeRTOS
1. 步骤一：修改基准定时器时钟源，将默认的Systick改为TIM2，即使用定时器2为FreeRTOS提供心跳
![修改基准定时器](./images/PGN12.png)

2. 步骤二：添加FreeRTOS组件
==配置CMSIS_V1版本，然后生成，不会报错；==
==配置CMSIS_V2版本，然后生成，产生报错；==
<span style="background-color: cyan;">原因：</span>在V1.8.6的版本框架中，根据编译器的错误提示可以定位到freertos_os2.h文件的如下位置
![编译报错](./images/PGN13.png)
在该版本的框架中可以看到cmsis_os2.c文件包含了以下两个库文件，这两个文件在V1.8.6版本中缺失了，导致报错。
![编译报错](./images/PGN14.png)
<span style="background-color: cyan;">解决：</span>把在CubeMX把框架切换成V1.8.5之后，cmsis_os2.c文件就不会包含这两个库文件，软件框架的不同就规避掉了这个问题。
![编译报错](./images/PGN15.png)

3. CLion设置RTOS集成
![设置选项](./images/PGN10.png)
![添加RTOS集成](./images/PGN11.png)

4. 给CLion添加FreeRTOS的调试功能</font>
![使能调试](./images/PGN16.png)





## <font size=3>调试代码</font>
### <font size=2>OpenOCD调试</font>

<font size=2> 1. 添加OpenOCD工具链</font>
<font size=2> 2. 将Clion上方的调试服务器改为"原生"</font>


### <font size=2>STLink调试</font>
<font size=2> 1. 将Clion上方的调试服务器改为"STLink"</font>

