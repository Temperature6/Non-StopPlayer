/*
        Copyright (C) 2003-2021 AQin Lab
        2021/12/11

        When you want to deploy "Player.exe" to a new computer,click this executable file,everyting will be done soon
*/
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include "shlwapi.h"
#pragma comment(lib,"shlwapi.lib")
#pragma warning(disable:4996)
using namespace std;

string default_path = "C:\\Non-StopPlayer"; //要复制到的文件默认路径,实际运行时需要读取“setting.txt”
char _src_dir[20] = "file\\"; //要复制的文件的文件夹(以“\\”结尾)
char temp[200] = "";
char linkname[20] = "name";

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("FileCopy.exe [IconFilePath] [shortcut name]\n");
        system("pause");
        return 1;
    }
    if (argc >= 3)
    {
        memcpy(linkname, argv[2], 20);
    }
    strcat(linkname, ".lnk"); //拼接快捷方式后缀
    //读取默认目录设置
    std::ifstream setting_file;
    setting_file.open("setting.txt");
    if (!setting_file)
    {
        printf("没有找到 \"setting.txt\" 将使用默认路径%s\n", default_path.c_str());
    }
    else
    {
        setting_file.read(temp, 100);
        default_path = temp;
    }
    //创建目录
    if (!PathFileExists(default_path.c_str()))
    {
        CreateDirectory(default_path.c_str(), NULL);
    }
    //遍历文件目录
    string src_dir = _src_dir;
    intptr_t handle;
    _finddata_t data;
    strcat(_src_dir, "\\*.*");
    handle = _findfirst(_src_dir, &data); // 寻找第一个文件

    string dst_file;
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
                string file_name = data.name;
                string t_src_file = src_dir + (string)data.name;
                dst_file = dst_file + "\\" + file_name;
                printf("找到文件:%s\n复制到:%s\n", t_src_file.c_str(), dst_file.c_str());
                CopyFile(t_src_file.c_str(), dst_file.c_str(), false);
            }
        }
    }

    //处理其他文件
    string shortcutFile = default_path + "\\ShortcutCreator.exe";
    string srcIcon = argv[1];
    string Icon_name;
    bool slash_found = false;
    for (unsigned int i = srcIcon.length() - 1; i >= 0; i--)
    {
        if (srcIcon[i] == '\\' || srcIcon[i] == '/')
        {
            slash_found = true;
            for (int j = i; j < srcIcon.length(); j++)
            {
                Icon_name += srcIcon[j];
            }
            break;
        }
    }
    if (!slash_found)
    {
        Icon_name = srcIcon; //图标文件为相对路径
    }
    string iconFile = default_path + "\\" + Icon_name;
    CopyFile(srcIcon.c_str(), iconFile.c_str(), false);
    //调用命令创建快捷方式
    printf("\n调用外部程序创建快捷方式...\n");
    string cmd = shortcutFile + " " + iconFile + " " + linkname;
    char cmd_[MAX_PATH] = "";
    memcpy(cmd_, cmd.c_str(), cmd.length());
    //memcpy(cmd_, cmd.GetBuffer(cmd.GetLength()), cmd.GetLength());
    /*for (int k = 0; k < cmd.GetLength(); k++)
    {
        cmd_[k] = cmd[k];
    }*/
    system(cmd_);
    system("pause");
    return 0;
}