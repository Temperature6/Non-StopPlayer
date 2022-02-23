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
下载压缩包之后解压，双击“install.bat”即可快速部署

无需手动设置快捷方式，只需将你喜欢的图标文件(*.ico)拖入到“ShortcutCreator.exe”后松手即可！

若您希望在别人的电脑上部署，则应使用U盘作为介质，将你喜欢的图标拖到“FileCopy.exe”上然后松手即可或使用命令行

```
.\FileCopy.exe [icon file path] [Link Name]
```

FileCopy.exe会将\file目录下的所有文件(不包括文件夹)复制到目标位置，具体目标位置应在“setting.txt”中输入，请使用绝对路径

这是最理想的目录结构

```
fc
 |--file
      |--audio.wav
      |--Player.exe
      |--ShortcutCreator.exe
      |--audio_cfg.txt
 |--src
 |--gift0.ico
 |--FileCopy.exe
 |--setting.txt
 |--install.bat
```

在“install.bat”中，写入以下代码用于更方便的部署

```
cd /d %~dp0
start "" "FileCopy.exe" .\gift0.ico "不要打开我啊"
```

### 程序参数

使用命令：

```
FileCopy.exe [IconPath] [Link Name]
```

其中，[Icon Path] 为快捷方式的图标文件

​	    [Link Name] 为快捷方式的名称(不要带 ".lnk")

如果目录下没有“setting.txt"程序将把文件复制到”C:\\\Non-StopPlayer“

如果有，则复制到”setting.txt"中写入的路径，名称，必须使用双下划线，例如 C:\\\file\\\dst

### 播放设置

Player.exe运行时，会读取“audio_cfg.txt”中的内容作为音频文件的路径

程序每次运行都会写入日志，若无法正常运行，可以看看日志的输出
