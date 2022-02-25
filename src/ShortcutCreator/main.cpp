/*
        Copyright (C) 2003-2021 AQin Lab
        2021/10/20

        This program is aim at creating a shortcut to "Non-StopPlayer",
        instead of operating the computer frequently which may be caught by teacher
*/
#include <iostream>
#include <Windows.h>
#include <ShlObj.h>
#include <atlstr.h>
#pragma warning(disable:4996)
#pragma comment(lib, "shell32.lib")
using namespace std;

char exeName[20] = "Player.exe";

int main(int argc, char* argv[])
{
    int temp = CoInitialize(NULL);
    char exe_file[MAX_PATH];
    //获得当前目录
    char current_path[MAX_PATH];
    GetModuleFileName(NULL, current_path, 100);
    for (int i = sizeof(current_path) - 1; i >= 0; i--)
    {
        if (current_path[i] == '\\')
        {
            break;
        }
        else
        {
            current_path[i] = '\0';
        }
    }
    cout << "获得当前工作目录:" << current_path << endl;
    memccpy(exe_file, current_path, 0, MAX_PATH);

    //获得桌面路径
    LPITEMIDLIST ppidl;
    char desktop_path[MAX_PATH];
    HRESULT Desk_P = SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &ppidl);
    SHGetPathFromIDList(ppidl, desktop_path); //转字符串
    cout << "获得本机桌面路径:" << desktop_path << endl;

    //创建快捷方式
    HRESULT hr;
    IShellLink* pLink;
    IPersistFile* ppf;

    hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pLink);
    hr = pLink->QueryInterface(IID_IPersistFile, (void**)&ppf);
    
    strcat(exe_file, exeName);
    pLink->SetPath(exe_file);
    cout << "目标:" << exe_file << endl;

    pLink->SetWorkingDirectory(current_path);
    cout << "工作目录:" << current_path << endl;

    pLink->SetDescription("如希望结束应用程序，重启电脑或者在任务管理器中单击选中“Player.exe”并单击“结束任务”");
    cout << "描述:请打开快捷方式属性页查看" << endl;

    if (argv[1] != NULL) //如果调用程序时未传入图片路径作为参数，则使用目标程序自身的图标
    {
        pLink->SetIconLocation(argv[1], 0);
        cout << "快捷方式图片:" << argv[1] << endl;
    }

    char dist[100];
    sprintf(dist, "%s\\%s", desktop_path, argv[2]);
    cout << "快捷方式绝对路径:" << dist << endl;
    if (fopen(dist, "r"))
    {
        cout << "文件:" << dist << "存在,需要销毁" << endl;
    }
    WCHAR  dist_[MAX_PATH];  //定义Unicode字符串
    MultiByteToWideChar(CP_ACP, 0, dist, -1, dist_, MAX_PATH);
    hr = ppf->Save(dist_, TRUE);
    ppf->Release();
    cout << "\n创建完成\n\n";
    CoUninitialize();
   
    return 0;
}