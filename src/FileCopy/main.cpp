/*
        Copyright (C) 2003-2021 AQin Lab
        2021/12/11

        When you want to deploy "Player.exe" to a new computer,click this executable file,everyting will be done soon
*/
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <atlstr.h>
#include <io.h>
#include "shlwapi.h"
#pragma comment(lib,"shlwapi.lib")
#pragma warning(disable:4996)

CString default_path = "C:\\Non-StopPlayer"; //要复制到的文件默认路径,实际运行时需要读取“setting.txt”
char _src_dir[20] = "file\\"; //要复制的文件的文件夹(以“\\”结尾)
char temp[200] = "";

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("FileCopy.exe [IconFilePath]");
        exit(0);
        return 0;
    }
    //读取默认目录设置
    std::ifstream setting_file;
    setting_file.open("setting.txt");
    setting_file.read(temp, 100);
    default_path = temp;
    //创建目录
    if (!PathFileExists(default_path))
    {
        CreateDirectory(default_path, NULL);
    }
    //遍历文件目录
    CString src_dir = _src_dir;
    intptr_t handle;
    _finddata_t data;
    strcat(_src_dir, "\\*.*");
    handle = _findfirst(_src_dir, &data); // 寻找第一个文件

    CString dst_file;
    if (handle == -1)
    {
        std::cout << "源目录为空" << std::endl;
        system("pause");
        exit(-1);
    }
    else
    {
        while (_findnext(handle, &data) != -1)
        {
            dst_file = default_path;
            if (strcmp(data.name, ".") == 0 || strcmp(data.name, "..") == 0)
            {
                continue;
            }
            else if (data.attrib == _A_SUBDIR)
            {
                printf("找到子目录:%s|跳过\n", data.name);
                continue;
            }
            else
            {
                CString file_name = data.name;
                CString t_src_file = src_dir + (CString)data.name;
                dst_file = dst_file + "\\" + file_name;
                printf("找到文件:%S\n复制到:%S\n", t_src_file.GetBuffer(0), dst_file.GetBuffer(0));
                CopyFile(t_src_file, dst_file, false);
            }
        }
    }

    //处理其他文件
    CString shortcutFile = default_path + "\\ShortcutCreator.exe";
    CString srcIcon = argv[1];
    CString Icon_name;
    for (int i = srcIcon.GetLength() - 1; i >= 0; i--)
    {
        if (srcIcon[i] == '\\' || srcIcon[i] == '/')
        {
            for (int j = i; j < srcIcon.GetLength(); j++)
            {
                Icon_name += srcIcon[j];
            }
            break;
        }
    }
    CString iconFile = default_path + Icon_name;
    CopyFile(srcIcon, iconFile, false);
    //调用命令创建快捷方式
    printf("\n调用外部程序创建快捷方式...\n");
    CString cmd = shortcutFile + " " + iconFile;
    char cmd_[200] = "";
    for (int k = 0; k < cmd.GetLength(); k++)
    {
        cmd_[k] = cmd[k];
    }
    system(cmd_);
    system("pause");
    return 0;
}