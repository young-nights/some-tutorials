<style>
.red {
  color: #ff0000;
}
.blue {
  color:rgb(0, 162, 225);
}
.mazarine {
  color:rgb(17, 0, 255);
}
</style>




# <span class="blue"><font size=4>Github中拉去代码相关的指令说明</font></span>
<font size=3>在Github上拉取特定版本的代码时，可以通过指定分支(Branch)、标签(Tag)或提交哈希(Commit Hash)来实现</font>
```bash
# 拉取特定分支/标签（如master、develop等）
git clone -b <branch-name> <link>

# 比如拉取rt-thread的4.1版本的源码
git clone -b lts-v4.1.x git@github.com:RT-Thread/rt-thread.git
```






