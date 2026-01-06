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


<font size=2>

```bash
1.安装工具链
sudo apt-get install git wget flex bison gperf python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0 net-tools

2.新建esp32文件夹
mkdir esp32

3.进入esp32文件夹安装esp-gitee-tools工具
git clone https://gitee.com/EspressifSystems/esp-gitee-tools.git

4.执行gitee工具切换镜像脚本
cd esp-gitee-tools
./jihu-mirror.sh set

5.进入esp32文件夹并安装esp-idf工具
git clone --recursive https://github.com/espressif/esp-idf.git

6.进入esp-idf文件夹并切换ESP32的版本为v5.2版本
git checkout v5.2
git submodule update --init --recursive

7.更换pip源
pip config set global.index-url http://mirrors.aliyun.com/pypi/simple
pip config set global.trusted-host mirrors.aliyun.com

8.安装编译工具
../esp-gitee-tools/install.sh

9.配置esp-idf环境
【方法一】
ESP32环境配置idf.py的环境变量配置方法（永久有效）
1.切换在根目录下，输入ls -al
2.可以看到有一个.profile文件
3.输入vim .profile使用vim对该文件进行编译
4.在文中中插入 source esp32/esp-idf/export.sh
	
【方法二】
ESP32环境配置idf.py的环境变量配置方法（永久有效）						
1.在根目录下输入   echo $SHELL	 查询命令行语言
2.输入   nano ~/.bashrc	打开文件
3.将 alias get_idf='. $HOME/esp32/esp-idf/export.sh' 加入到文件中
4.每次进入时需要idf.py时，输入  get-idf   就可以配置环境了
```

</font>
