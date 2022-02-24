# Non-StopPlayer


### 注意
还是希望大家如果拿来开玩笑一定要适度。
不要广泛传播以免造成不必要的麻烦。

### 不会停下！

​	本程序双线程持续运行，只能用任务管理器或者关机的方式结束

### 烦人！！

每隔100ms将系统音量调整至最大值

每次运行会写入运行日志（没有则创建）

类似于以前的“送给最爱的TA.apk”

### 快速部署！！！

警告⚠：源代码中默认锁定音量为 30 ，您可以适当调整

下载src中的Visual Studio工程，编译解决方案，按下面目录结构布置文件

双击“install.bat”即可快速部署

无需手动设置快捷方式，只需将你喜欢的图标文件(*.ico)拖入到“ShortcutCreator.exe”后松手即可！

但这代表着您没有输入快捷方式的名称，则使用默认名称“小礼物”

若您希望在别人的电脑上部署，则应使用U盘作为介质

用命令行:

```
.\FileCopy.exe [icon file path] [Link Name]
```

FileCopy.exe会将\file目录下的所有文件(不包括文件夹)复制到目标位置，具体目标位置应在“setting.txt”中输入，

若"setting.txt"不存在，则使用默认位置“C:\\Non-StopPlayer\\

请使用绝对路径

你还可以按下面所示编写install.bat,省去调用命令行的时间

### 目录结构

```
 |--file
      |--audio_.wav
      |--Player.exe
      |--ShortcutCreator.exe
      |--audio_cfg.txt
 |--gift0.ico
 |--FileCopy.exe
 |--setting.txt
 |--install.bat
```

### 部署操作

在“install.bat”中，写入以下代码用于更方便的部署

```
cd /d %~dp0
start "" "FileCopy.exe" .\beast.ico "不要打开我啊"
```
.\beast.ico 是图标文件的路径，不能空

"不要打开啊" 是创建的快捷方式的名称，不填写则默认为"小礼物"

使用中文时最后加上双引号“”


在”audio_cfg.txt"中，应写入同级目录下的一个音频文件的相对路径

例如

```
.\audio_.wav
```



### 程序参数

使用命令：

```
FileCopy.exe [IconPath] [Link Name]
```

其中，[Icon Path] 为快捷方式的图标文件

​	    [Link Name] 为快捷方式的名称(不要带 ".lnk")

程序将把同级文件夹"file"中的文件复制到在"setting.txt"中指定的目录

如果目录下没有“setting.txt"，则默认复制到:”C:\\Non-StopPlayer\\“

如果有，则复制到”setting.txt"中写入的路径，必须使用双下划线，例如 C:\\\file\\\dst

### 播放设置

Player.exe运行时，会读取“audio_cfg.txt”中的内容作为音频文件的路径

音频文件最好在Player.exe的统计目录下，方便使用FileCopy.exe进行部署

程序每次运行都会写入日志，若无法正常运行，可以看看日志的输出

### 参考
调整音量的代码来自
https://blog.csdn.net/yu_20501253/article/details/103068278

### 免责声明

源代码中默认音量为 30

本代码仅供学习讨论，您可以自己研究、改动

请确保被恶搞方的身心安全，我们不希望出现意外

若您使用源代码编译的程序对被恶搞方造成了某些损失，本人对一切损失概不负责
