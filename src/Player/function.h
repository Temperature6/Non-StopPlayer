#pragma warning(disable:4996)
#include <windows.h>
#include <mmdeviceapi.h> 
#include <endpointvolume.h>
#include <audioclient.h>


//参数:
//	-2 恢复静音
//	-1 静音
//	0~100:音量比例
bool SetVolumeLevel(int level)
{
	HRESULT hr;
	IMMDeviceEnumerator* pDeviceEnumerator = 0;
	IMMDevice* pDevice = 0;
	IAudioEndpointVolume* pAudioEndpointVolume = 0;
	IAudioClient* pAudioClient = 0;

	try {
		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pDeviceEnumerator);
		if (FAILED(hr)) throw "CoCreateInstance";
		hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);
		if (FAILED(hr)) throw "GetDefaultAudioEndpoint";
		hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pAudioEndpointVolume);
		if (FAILED(hr)) throw "pDevice->Active";
		hr = pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&pAudioClient);
		if (FAILED(hr)) throw "pDevice->Active";

		if (level == -2) {
			hr = pAudioEndpointVolume->SetMute(FALSE, NULL);
			if (FAILED(hr)) throw "SetMute";
		}
		else if (level == -1) {
			hr = pAudioEndpointVolume->SetMute(TRUE, NULL);
			if (FAILED(hr)) throw "SetMute";
		}
		else {
			if (level < 0 || level>100) {
				hr = E_INVALIDARG;
				throw "Invalid Arg";
			}

			float fVolume;
			fVolume = level / 100.0f;
			hr = pAudioEndpointVolume->SetMasterVolumeLevelScalar(fVolume, &GUID_NULL);
			if (FAILED(hr)) throw "SetMasterVolumeLevelScalar";

			pAudioClient->Release();
			pAudioEndpointVolume->Release();
			pDevice->Release();
			pDeviceEnumerator->Release();
			return true;
		}
	}
	catch (...) {
		if (pAudioClient) pAudioClient->Release();
		if (pAudioEndpointVolume) pAudioEndpointVolume->Release();
		if (pDevice) pDevice->Release();
		if (pDeviceEnumerator) pDeviceEnumerator->Release();
		throw;
	}
	pAudioClient->Release();
	pAudioEndpointVolume->Release();
	pDevice->Release();
	pDeviceEnumerator->Release();
	return false;
}

LPWSTR CharToLPWSTR(const char* c_str)
{
	int dwLen = strlen(c_str) + 1;
	int nwLen = MultiByteToWideChar(CP_ACP, 0, c_str, dwLen, NULL, 0);
	LPWSTR new_str = new WCHAR[dwLen];
	MultiByteToWideChar(CP_ACP, 0, c_str, dwLen, new_str, nwLen);
	return new_str;
}

double GetPlayTime(const char *filename)
{
	char buf[16];
	char msg[MAX_PATH];
	sprintf_s(msg, "open %s type waveaudio alias wave", filename);
	mciSendString(msg, NULL, 0, 0);
	mciSendString("status wave length", buf, 16, 0);
	mciSendString("close wave", NULL, 0, 0);
	printf("file duration is %0.3f seconds\n", atoi(buf) / 1000.0);

	return atoi(buf);
}

void RemoveTabSymbols(char* str)
{
	unsigned int str_lenth = strlen(str);
	for (unsigned int i = 0; i < str_lenth; i++)
	{
		if (str[i] == '\r' || str[i] == '\n') str[i] = '\0';
	}
	return;
}
