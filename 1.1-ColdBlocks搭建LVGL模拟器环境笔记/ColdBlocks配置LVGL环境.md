<style>
.highlight {
  color: white;
  background: linear-gradient(90deg, #ff6b6b, #4ecdc4);
  padding: 5px;
  border-radius: 5px;
}
</style>
<span class="highlight">配置流程对于CodeBlocks 20.03版本以下的较为重要，对于最新版本的CodeBlocks可直接跳至“LVGL-V9移植”这一目录节点</span>



<style>
.red-text { 
  color: #ff0000; 
  font-weight: bold;
}
.green-text {
  color: #00ff00;
  border: 1px solid gray;
}
</style>


<style>
.red { 
  color: #ff0000; 
}
.green {
  color: #00ff00;
}
.blue {
  color:rgb(17, 0, 255);
}

</style>

# CodeBlocks 配置 LVGL 环境

## 搭建MinGW-w64环境
- 下载MinGW-w64安装包 
- 官方：https://www.mingw-w64.org

1. 进入官方页面后，点击Downloads按钮
![官网首页](./images/mingw_1.png)

<br>
<br>

2. 点击<span class="red">Pre-built Toolchains</span>选项，然后进入下载选择页面，选择<span class="red">MinGW-W64-builds</span>选项

![选择下载类型](./images/mingw_2.png)

<br>
<br>

3. 选择 **MinGW-W64-builds** 方式进行下载
![进入github页面](./images/mingw_3.png)

<br>
<br>

4. 选择**msvcrt**的类型进行下载
![选择MinGW的类型](./images/mingw_4.png)

<br>
<br>

5. 下载后解压文件到本地，然后复制路径后进入电脑环境变量配置，添加路径
![添加环境变量](./images/mingw_5.png)

<br>
<br>

6. 验证 **MinGW-W64编译**，命令提示符返回版本信息代表配置成功
![添加环境变量](./images/mingw_6.png)

<br>
<br>
<br>
<br>

## 搭建cmake环境

- 下载 Windows-cmake 安装包 
- 官方：https://www.cmake.org

1. 进入官方页面，点击Downloads按钮
![cmake主页](./images/cmake_Step_1.png)

<br>
<br>

2. 选择 **.msi** 的安装包进行下载
![cmake安装包选择](./images/cmake_Step_2.png)
   
<br>
<br>

3. 随后进行傻瓜式安装，一路确定即可
![cmake安装](./images/cmake_Step_3.png)

<br>
<br>

4. 验证Cmake是否安装成功
![cmake验证](./images/cmake_Step_4.png)



<br>
<br>


## SDL2下载与环境搭建
**截止2025年4月20日，LVGL目前只支持SDL2，因此下载SDL2依赖包进行环境配置**
<br>
- 下载SDL2依赖包 
- 官方：https://www.libsdl.org

1. 进入SDL主页，点击SDL Releases 进入版本选择下载页面
 ![SDL主页](./images/SDL2_1.png)

<br>
<br>

2. 当前跳转的页面是SDL更新到的最新的版本页，点击Releases去上一个页面翻找之前的版本
 ![SDL当前的最新页面](./images/SDL2_2.png)
<br>
<br>

3. 随便找一个SDL2的版本进行下载
  ![下载SDL2](./images/SDL2_3.png)
<br>
<br>






## LittleVGL-V8构架导入
1. 在lv_pc_simulator文件夹中创建一个CodeBlocks文件夹，在文件夹中创建新工程，移除project中自动生成的main.c文件，删除在工程路径中的main.c文件
![创建工程](./images/codeblocks_1.png)
<br>
<br>
2. 解压lv_pc_simulator文件夹，找到Comment文件夹，将Comment文件夹中的三个压缩文件解压，移动到蓝色框选的相应的文件夹中
![工程移植](./images/codeblocks_2.png)
<br>
<br>

3. 递归添加
![递归添加](./images/codeblocks_3.png)
<br>
<br>

4. 选择最外层根目录，即 lv_pc_simulator 文件夹，添加过程中会弹出两个配置窗口，我们默认设置就行，添加成功
![递归添加](./images/codeblocks_4.png)
<br>
<br>


5. 随后在**x86_64-w64-mingw32**文件夹中找到**include**文件夹，将include文件夹中的SDL2粘贴复制到工程文件路径下
![下载SDL2](./images/SDL2_6.png)
![下载SDL2](./images/SDL2_7.png)
<br>
<br>


6. 到下载好解压后的SDL文件中，找到**x86_x64-w64-mingw32**文件下的**lib**文件夹中的7个<span class="red">.a</span>后缀的文件，全部复制
  ![解压复制文件](./images/SDL2_4.png)

<br>
<br>

7. 将复制的7个.a文件粘贴到Codeblocks安装目录下的MinGW文件夹中的lib文件夹下<span class="red">（注意：当前版本使用的CodeBlocks的版本应当<=20.03，此时将上面下载的MinGW-W64的全部内容粘贴到CodeBlocks安装目录下的MinGW文件夹中，安装自带的MinGW全部删掉进行替换）</span>
![粘贴文件到指定文件夹](./images/SDL2_5.jpg)
<br>
<br>

8. 最后对CodeBlocks进行配置，选中工程文件，单击右键，选择<span class="blue">“Bulid Options”</span>,在<span class="blue">linker settingsh</span>中的<span class="blue">Other linker options</span>中添加<span class="red-text">-lmingw32 -lSDL2main -lSDL2</span>
![下载SDL2](./images/SDL2_8.png)
<br>
<br>

9. 选择<span class="blue">"Search directories"</span>，在Compiler中添加头文件路径，我们选中最外层根目录即可
![下载SDL2](./images/SDL2_9.png)
<br>
<br>

10.  运行试调，产生SDL2.dll丢失类型报错，我们需要将SDL2文件夹中的SDL2.dll添加到工程Debug文件夹中
![下载SDL2](./images/SDL2_10.png)
![下载SDL2](./images/SDL2_11.png)
<br>
<br>

11. 配置完成，若第一次编译报错，退出CodeBlocks，对环境配置进行更改，要把上一次工程生成的文件删除，否则容易引发报错
![下载SDL2](./images/codeblocks_5.png)
<br>
<br>

12. 运行模拟器
![下载SDL2](./images/codeblocks_6.png)
<br>
<br>
<br>
<br>




## LVGL-V9源码文件说明

![SDL主页](./images/lvgl_1.png)

**目录说明：**

- demos： 存放的是LVGL一些综合的内置示例，部分示例可以再https://lvgl.io/demos体验
- docs: 存放LVGL的开发文档，阅读时一般不在这里直接阅读，而是在LVGL的文档站点阅读：https://docs.lvgl.io/9.2
- env_support: 一些环境或者平台的支持，比如我们所使用的RT-Thread就在其中
- examples：存放LVGL的内置示例
- scripts：存放一些处理脚本，我们在使用LVGL时基本不会用到
- src：存放LVGL实际的源码，我们使用LVGL进行开发时，都是使用这里的代码文件
- tests：存放一些CI测试文件，我们在使用LVGL时不会用到

<br>
<br>


## LVGL-V9移植
1. 官方针对codeblocks在github上有一个移植例程，首先通过上面的LVGL文档站点阅读链接进入v9.2版本阅读站
![LVGL阅读站点](./images/lvgl_2.png)


<br>
<br>

2. 选择LVGL的移植平台
![LVGL移植平台链接选择](./images/lvgl_3.png)


<br>
<br>

3. 通过点击链接就进入到了github页面，然后选择当前的版本分支v9.2，下载这个代码架构
![下载代码架构](./images/lvgl_4.png)


<br>
<br>


4. 将下载的lvgl-v9.2的核心代码驱动（就是上面的代码目录所展示的所有的文件）直接全部剪切到这个codeblocks代码构架目录中的lvgl文件夹中，然后就可以直接通过编译运行LVGL的测试例程了
![代码移植](./images/lvgl_5.png)







