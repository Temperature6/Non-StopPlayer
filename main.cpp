/*
        Copyright (C) 2003-2021 AQin Lab
*/
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <thread>
#include "function.h"
#pragma comment (lib, "winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
using namespace std;

int VolumeLevel = 100;
int music_length = 10;

void SetVolume();
void PlayMusic();

int main()
{
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
		Sleep(200);
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
