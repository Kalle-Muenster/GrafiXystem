#include "projectMacros.h"
#include "AudioObject.h"
#include <vector>

#define DEBUG

#ifdef DEBUG


string debugStrings[50];
#endif

void initDebug(void)
{
#ifdef DEBUG
debugStrings[0]	= "all is OK									\n";
debugStrings[1]	= "memory error									\n";
debugStrings[2]	= "can't open the file							\n";
debugStrings[3]	= "can't find a free/valid driver				\n";
debugStrings[4]	= "the sample buffer was lost					\n";
debugStrings[5]	= "invalid handle								\n";
debugStrings[6]	= "unsupported sample format					\n";
debugStrings[7]	= "invalid position								\n";
debugStrings[8]	= "BASS_Init has not been successfully called	\n";
debugStrings[9]	= "BASS_Start has not been successfully called	\n";
debugStrings[14] = "already initialized/paused/whatever				\n" ;
debugStrings[18] = "can't get a free channel						\n" ;
debugStrings[19] = "an illegal type was specified					\n" ;
debugStrings[20] = "an illegal parameter was specified				\n" ;
debugStrings[21] = "no 3D support									\n" ;
debugStrings[22] = "no EAX support									\n" ;
debugStrings[23] = "illegal device number							\n" ;
debugStrings[24] = "not playing										\n" ;
debugStrings[25] = "illegal sample rate								\n" ;
debugStrings[27] = "the stream is not a file stream					\n" ;
debugStrings[29] = "no hardware voices available					\n" ;
debugStrings[31] = "the MOD music has no sequence data				\n" ;
debugStrings[32] = "no internet connection could be opened			\n" ;
debugStrings[33] = "couldn't create the file						\n" ;
debugStrings[34] = "effects are not available						\n" ;
debugStrings[37] = "requested data is not available					\n" ;
debugStrings[38] = "the channel is a \"decoding channel\"			\n" ;
debugStrings[39] = "a sufficient DirectX version is not installed	\n" ;
debugStrings[40] = "connection timedout								\n" ;
debugStrings[41] = "unsupported file format							\n" ;
debugStrings[42] = "unavailable speaker								\n" ;
debugStrings[43] = "invalid BASS version (used by add-ons)			\n" ;
debugStrings[44] = "codec is not available/supported				\n" ;
debugStrings[45] = "the channel/file has ended						\n" ;
debugStrings[46] = "the device is busy								\n" ;
debugStrings[49] = "some other mystery problem						\n" ;
#endif
}


char* _GetErrorString()
{
#ifdef DEBUG
	int error = BASS_ErrorGetCode();
	if(error == -1)
		error = 49;

	return debugStrings[error];
#endif
return "";
}


BassAudio* bassaudioInstance;
HSTREAM derAudio;
bool _IsPlaying = false;
bool _backgroundAudioLoadet = false;


HSTREAM
_getAudioStreamByFileName(const string filename)
{
	FILE* file;
	file = fopen(filename,"rb");
	long fileLength,offset;
	fseek(file,0,SEEK_END);
	fileLength=ftell(file);
	fseek(file,0,SEEK_SET);
	offset=0;
	return BASS_StreamCreateFile(false, filename,offset,fileLength,BASS_STREAM_AUTOFREE);
}

HCHANNEL
BassAudio::Loade3DSample(const char* filename)
{
	FILE* file;
	file = fopen(filename,"rb");
	long fileLength,offset;
	fseek(file,0,SEEK_END);
	fileLength=ftell(file);
	fseek(file,0,SEEK_SET);
	offset=0;
	HSAMPLE sample = BASS_SampleLoad(false,filename,offset,0,5,BASS_SAMPLE_LOOP|BASS_SAMPLE_3D);
	std::cout<<_GetErrorString();
	HCHANNEL channel = BASS_SampleGetChannel(sample,true);
	std::cout<<_GetErrorString();
	BASS_Apply3D();
	std::cout<<_GetErrorString();
	return channel;
}

BassAudio::BassAudio(void)
{
	initDebug();
	BASS_Init(-1,44100,BASS_DEVICE_3D|BASS_DEVICE_FREQ,0,NULL);
	HPLUGIN BASS_PluginLoad((HPLUGIN)"bass_fx.dll");
	BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 100);	
	std::cout<<_GetErrorString();
	BASS_SetEAXParameters(EAX_PRESET_ARENA);
	std::cout<<_GetErrorString();
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
BassAudio::LoadeMusic(const char* fileName)
{
	return _getAudioStreamByFileName((const string)fileName);
}
	

void 
BassAudio::SetListenerPosition(TransformA* cameraTranform)
{
	BASS_Set3DPosition(cameraTranform->position.asBassVector(),&cameraTranform->movement,cameraTranform->forward.asBassVector(),cameraTranform->up.asBassVector());
	BASS_Apply3D();
}

void
BassAudio::LoadeBackgroundAudio(const char* fileName)
{
	derAudio = _getAudioStreamByFileName((string)fileName);
	BASS_ChannelSetDevice(derAudio,-1);
	printf("\nAudio: %s loadet as Backgroundmusic !\n",fileName);
	_backgroundAudioLoadet = true;
}

void
BassAudio::Play(void)
{
	if(_backgroundAudioLoadet)
	{
		if(BASS_ChannelPlay(derAudio,true))
		{
			_IsPlaying=true;
			std::cout<<"\nAudio:  PLAYING\n";
		}
		else
			printf("Audio: %s",_GetErrorString());
	}
}

void 
BassAudio::Pause(void)
{
	if(_IsPlaying)
	{
		BASS_ChannelPause(derAudio);
		_IsPlaying= false;
		std::cout<<"\nAudio:  PAUSED\n";
	}
}

float
BassAudio::Volume(float vol)
{
	if (vol<=1)
		BASS_SetVolume(vol);
	
	return BASS_GetVolume();
}
