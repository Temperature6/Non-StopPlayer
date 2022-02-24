/*
        Copyright (C) 2003-2021 AQin Lab
		Unknown Date

		This is a program will play a period of music, and you can't stop it until you start task manger or restart the computer
*/
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <thread>
#include <time.h>
#include <fstream>
#include "function.h"
#pragma comment (lib, "winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#pragma warning(disable:4996)
using namespace std;

int VolumeLevel = 30; //锁定的音量(0~100)
double music_length = 0;//延迟时间(ms)
double delay = 0.1;
char music_path[MAX_PATH] = { 0 };
char cfg_file_name[20] = "audio_cfg.txt";

void SetVolume();
void PlayMusic();

int main()
{
	//运行日志
	fstream log_file;
	log_file.open("Log.txt", ios::out|ios::app);
	//获取启动时间
	char time_str[MAX_PATH];
	time_t current_sec = time(NULL);
	tm* current;
	current = localtime(&current_sec);
	strftime(time_str, 100, "[%Y/%m/%d %H:%M:%S]", current);
	//获得要播放的文件的路径
	FILE* path_cfg;
	path_cfg = fopen(cfg_file_name, "rb");
	if (path_cfg == nullptr)
	{
		fstream cfg_file;
		cfg_file.open(cfg_file_name, ios::out | ios::app);
		cfg_file << ".\\audio.wav";
		cfg_file.close();

		log_file << time_str << "Can't find configure file" << endl;
		log_file.close();
		return -1;
	}
	fread(music_path, sizeof(char), MAX_PATH, path_cfg);
	fclose(path_cfg);
	RemoveTabSymbols(music_path);
	//FILE *music_file;
	if (!fopen(music_path, "rb"))
	{
		log_file << time_str << "Can't find audio file in \"" << cfg_file_name << "\"" << endl;
		log_file.close();
		return -1;
	}
	//写入日志
	strcat_s(time_str, "程序开始运行");
	log_file << time_str << endl;
	log_file.close();
	//获取音频文件长度
	music_length = GetPlayTime(music_path);
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
		PlaySound(music_path, NULL, SND_FILENAME | SND_ASYNC);
		Sleep(music_length);
	}
	return;
}
