#include "BassAudio.h"
#include "AudioObject.h"



BassAudio* bassaudioInstance;
bool __IsPlaying = false;


BassAudio::BassAudio(void)
{
	BASS_Init(-1,44100,BASS_DEVICE_MONO|BASS_DEVICE_3D|BASS_DEVICE_FREQ,0,NULL);
	HPLUGIN BASS_PluginLoad((HPLUGIN)"bass_fx.dll");
	BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 100);
}


BassAudio::~BassAudio(void)
{
	delete bassaudioInstance;
}

BassAudio*
BassAudio::GetInstance(void)
{
	if(!bassaudioInstance)
		bassaudioInstance = new BassAudio();
	return
		bassaudioInstance;
}

HSTREAM
BassAudio::LoadeAudio(const char* fileName)
{
	FILE* file;
	file = fopen(fileName,"rb");
	long fileLength,offset;
	fseek(file,0,SEEK_END);
	fileLength=ftell(file);
	fseek(file,0,SEEK_SET);
	fileLength=ftell(file);
	offset=0;

	return BASS_StreamCreateFile(false, fileName,offset,fileLength,BASS_SAMPLE_MONO|BASS_SAMPLE_3D|BASS_SAMPLE_LOOP|BASS_SAMPLE_FX|BASS_STREAM_AUTOFREE|BASS_ASYNCFILE);
}

void 
BassAudio::SetListenerPosition(Transform* cameraTranform)
{
	//todo...
}

void
BassAudio::LoadeBackgroundAudio(const char* fileName)
{
	derAudio = LoadeAudio(fileName);

	BASS_ChannelSetDevice(derAudio,-1);
	
}

void
BassAudio::Play(void)
{
	if(derAudio)
	{
		BASS_ChannelPlay(derAudio,true);
		__IsPlaying=true;
	}
}

void 
BassAudio::Pause(void)
{
	if(__IsPlaying)
	{
		BASS_ChannelPause(derAudio);
		__IsPlaying= false;
	}
}
