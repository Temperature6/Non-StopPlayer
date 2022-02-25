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
    //��õ�ǰĿ¼
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
    cout << "��õ�ǰ����Ŀ¼:" << current_path << endl;
    memccpy(exe_file, current_path, 0, MAX_PATH);

    //�������·��
    LPITEMIDLIST ppidl;
    char desktop_path[MAX_PATH];
    HRESULT Desk_P = SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &ppidl);
    SHGetPathFromIDList(ppidl, desktop_path); //ת�ַ���
    cout << "��ñ�������·��:" << desktop_path << endl;

    //������ݷ�ʽ
    HRESULT hr;
    IShellLink* pLink;
    IPersistFile* ppf;

    hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pLink);
    hr = pLink->QueryInterface(IID_IPersistFile, (void**)&ppf);
    
    strcat(exe_file, exeName);
    pLink->SetPath(exe_file);
    cout << "Ŀ��:" << exe_file << endl;

    pLink->SetWorkingDirectory(current_path);
    cout << "����Ŀ¼:" << current_path << endl;

    pLink->SetDescription("��ϣ������Ӧ�ó����������Ի���������������е���ѡ�С�Player.exe������������������");
    cout << "����:��򿪿�ݷ�ʽ����ҳ�鿴" << endl;

    if (argv[1] != NULL) //������ó���ʱδ����ͼƬ·����Ϊ��������ʹ��Ŀ����������ͼ��
    {
        pLink->SetIconLocation(argv[1], 0);
        cout << "��ݷ�ʽͼƬ:" << argv[1] << endl;
    }

    char dist[100];
    sprintf(dist, "%s\\%s", desktop_path, argv[2]);
    cout << "��ݷ�ʽ����·��:" << dist << endl;
    if (fopen(dist, "r"))
    {
        cout << "�ļ�:" << dist << "����,��Ҫ����" << endl;
    }
    WCHAR  dist_[MAX_PATH];  //����Unicode�ַ���
    MultiByteToWideChar(CP_ACP, 0, dist, -1, dist_, MAX_PATH);
    hr = ppf->Save(dist_, TRUE);
    ppf->Release();
    cout << "\n�������\n\n";
    CoUninitialize();
   
    return 0;
}