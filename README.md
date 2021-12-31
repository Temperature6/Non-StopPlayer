# Non-StopPlayer

### 不会停下！

​	本程序双线程持续运行，只能用任务管理器或者关机的方式结束

### 烦人！！

每隔100ms将系统音量调整至最大值

每次运行会写入运行日志（没有则创建）

类似于以前的“送给最爱的TA.apk”

### 快速部署！！！

无需手动设置快捷方式，只需将你喜欢的图标文件(*.ico)拖入到“ShortcutCreator.exe”后松手即可！

若您希望在别人的电脑上部署，则应使用U盘作为介质，将你喜欢的图标拖到“FileCopy.exe”上然后松手即可或使用命令行

```
.\FileCopy.exe [icon file path]
```

FileCopy.exe会将\file目录下的所有文件(不包括文件夹)复制到目标位置，具体目标位置应在“setting.txt”中输入，请使用绝对路径

这是最理想的目录结构

```
fc
 |--file
      |--audio.wav
      |--Player.exe
      |--ShortcutCreator.exe
 |--src
 |--gift0.ico
 |--FileCopy.exe
 |--setting.txt
 |--install.bat
```

在“install.bat”中，写入以下代码用于更方便的部署

```
cd /d %~dp0
start "" "FileCopy.exe" .\gift0.ico
```

