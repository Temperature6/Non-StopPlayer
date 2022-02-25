/*
        Copyright (C) 2003-2022 AQin Lab


		This is a program will play a period of music, and you can't stop it until you start task manger or restart the computer
*/
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <thread>
#include <time.h>
#include <fstream>
#include <json.h>
#include "function.h"
#pragma comment (lib, "winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#pragma warning(disable:4996)

#define CONFIG_LEN 200

using namespace std;

int VolumeLevel = 0; //锁定的声音大小(%)
double music_length = 0; //音乐长度(S)
double delay = 0.1; //调整音量延迟(S)
char music_path[MAX_PATH] = { 0 };
char cfg_file_name[20] = "config.json";
char cfg_str[200] = { 0 };

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
	//读取json文件
	
	fstream cfg;
	cfg.open(cfg_file_name);
	if (!cfg)
	{
		cfg.open(cfg_file_name, ios::app | ios::out);
		Json::Value root;
		Json::FastWriter writer;
		root["Path"] = ".\\audio.wav";
		root["Volume"] = VolumeLevel;
		root["delay"] = delay;
		string json_doc = writer.write(root);
		cfg << json_doc.c_str();
		cfg.close();

		log_file << time_str << "Can't find configure file, we have created" << endl;
		log_file.close();
		return -1;
	}
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(cfg, root))
	{
		log_file << time_str << "Fail to parse json document" << endl;
		log_file.close();
		return -1;
	}
	string t_music_path;
	t_music_path = root["Path"].asString();
	VolumeLevel = root["Volume"].asInt();
	delay = root["delay"].asDouble();

	std::strcpy(music_path, t_music_path.c_str());
	RemoveTabSymbols(music_path); //移除特殊字符
	//FILE *music_file;
	if (!fopen(music_path, "rb"))
	{
		log_file << time_str << "Can't find audio file in \"" << cfg_file_name << "\"" << endl;
		log_file.close();
		return -1;
	}
	//获取音频文件长度
	music_length = GetPlayTime(music_path);
	//写入日志
	char log[MAX_PATH] = { 0 };
	sprintf(log, "程序成功运行,使用文件 %s ,音量 %d %", music_path, VolumeLevel);
	strcat_s(time_str, log);
	log_file << time_str << endl;
	log_file.close();
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
		Sleep(delay * 1000);
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
