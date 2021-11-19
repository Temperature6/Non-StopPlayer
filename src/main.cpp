/*
        Copyright (C) 2003-2021 AQin Lab
*/
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <thread>
#include <time.h>
#include <fstream>
#include "function.h"
#pragma comment (lib, "winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#pragma warning(disable:4996)
using namespace std;

int VolumeLevel = 100;
int music_length = 10;
int delay = 100; //延迟时间(ms)

void SetVolume();
void PlayMusic();

int main()
{
	//运行日志
	fstream file;
	file.open("Log.txt", ios::out|ios::app);
	//获取运行时间
	char time_str[100];
	time_t current_sec = time(NULL);
	tm* current;
	current = localtime(&current_sec);
	strftime(time_str, 100, "[%Y/%m/%d %H:%M:%S]", current);
	//写入日志
	strcat_s(time_str, "程序开始运行");
	file << time_str << endl;
	file.close();
	//开始播放音乐
	thread volume_t(SetVolume);
	thread play_t(PlayMusic);
	play_t.join();
	return 0;
}

void SetVolume()
{
	while (true)
	{
		int temp = CoInitialize(0);
		try
		{
			SetVolumeLevel(-2);
			SetVolumeLevel(VolumeLevel);
		}
		catch (...)
		{

		}
		CoUninitialize();
		Sleep(delay);
	}
	return;
}

void PlayMusic()
{
	while (true)
	{
		PlaySound(TEXT("audio.wav"), NULL, SND_FILENAME | SND_ASYNC);
		Sleep(music_length * 1000);
	}
	return;
}
