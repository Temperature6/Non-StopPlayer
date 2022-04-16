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

string default_path = "C:\\Non-StopPlayer"; //Ҫ���Ƶ����ļ�Ĭ��·��,ʵ������ʱ��Ҫ��ȡ��setting.txt��
char _src_dir[20] = "file\\"; //Ҫ���Ƶ��ļ����ļ���(�ԡ�\\����β)
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
    strcat(linkname, ".lnk"); //ƴ�ӿ�ݷ�ʽ��׺
    //��ȡĬ��Ŀ¼����
    std::ifstream setting_file;
    setting_file.open("setting.txt");
    if (!setting_file)
    {
        printf("û���ҵ� \"setting.txt\" ��ʹ��Ĭ��·��%s\n", default_path.c_str());
    }
    else
    {
        setting_file.read(temp, 100);
        default_path = temp;
    }
    //����Ŀ¼
    if (!PathFileExists(default_path.c_str()))
    {
        CreateDirectory(default_path.c_str(), NULL);
    }
    //�����ļ�Ŀ¼
    string src_dir = _src_dir;
    intptr_t handle;
    _finddata_t data;
    strcat(_src_dir, "\\*.*");
    handle = _findfirst(_src_dir, &data); // Ѱ�ҵ�һ���ļ�

    string dst_file;
    if (handle == -1)
    {
        std::cout << "ԴĿ¼Ϊ��" << std::endl;
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
                printf("�ҵ���Ŀ¼:%s|����\n", data.name);
                continue;
            }
            else
            {
                string file_name = data.name;
                string t_src_file = src_dir + (string)data.name;
                dst_file = dst_file + "\\" + file_name;
                printf("�ҵ��ļ�:%s\n���Ƶ�:%s\n", t_src_file.c_str(), dst_file.c_str());
                CopyFile(t_src_file.c_str(), dst_file.c_str(), false);
            }
        }
    }

    //���������ļ�
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
        Icon_name = srcIcon; //ͼ���ļ�Ϊ���·��
    }
    string iconFile = default_path + "\\" + Icon_name;
    CopyFile(srcIcon.c_str(), iconFile.c_str(), false);
    //�����������ݷ�ʽ
    printf("\n�����ⲿ���򴴽���ݷ�ʽ...\n");
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