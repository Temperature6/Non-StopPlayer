#include <windows.h> 
#include <mmdeviceapi.h> 
#include <endpointvolume.h>
#include <audioclient.h>


//²ÎÊý:
//	-2 »Ö¸´¾²Òô
//	-1 ¾²Òô
//	0~100:ÒôÁ¿±ÈÀý
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
	return false;
}