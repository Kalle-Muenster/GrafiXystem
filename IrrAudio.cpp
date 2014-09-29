#include "IrrAudio.h"

bool Active;
//irrAudio* audio;
SndTps* AudioBuffer;
int AudioBufferLength;
irrklang::ISoundEngine* engine; 
irrklang::ISound* controlls;
irrklang::ISoundSource* source;
IrrReader* irrreader;
irrAudio* audio;

irrAudio::irrAudio(void)
{

		//reader = (IrrReader*)factory->createFileReader("sinus441.wav");
		//factory->SetFacturedReader(factory);
		//reader->drop();
		

	ISoundDeviceList* deviceList = irrklang::createSoundDeviceList(irrklang::ESOD_AUTO_DETECT);
	engine = irrEngine = irrklang::createIrrKlangDevice(irrklang::ESOD_AUTO_DETECT,irrklang::ESEO_DEFAULT_OPTIONS,deviceList->getDeviceID(0));
	factory = new IrrFactured();
	irrreader = (IrrReader*)factory->createFileReader("testtrack2.mp3");
	irrEngine->addFileFactory(factory);
	factory->drop();
	Active=true;
	
#//	delete deviceList;
	}


irrAudio
irrAudio::GetInstance()
{
	if(!audio)
		audio=new irrAudio();

	return *audio;
}

void
irrAudio::Loade(char* name)
{
		irrEngine = engine;
	
	source = irrSource = irrEngine->addSoundSourceFromFile("testtrack.wav",irrklang::ESM_STREAMING,false);
	irrEngine->play2D(irrSource,false,false,false,false);
	printf("trackLoadedt");
//	Controls = controlls = 
//	Controls->setIsPaused(false);
}

irrAudio::~irrAudio(void)
{
	Controls->drop();
	delete Controls;
	irrSource->drop();
	delete irrSource;
	irrEngine->drop();
	delete irrEngine;
}


UINT32
irrAudio::GetNumberOfSamplesInBuffer(void)
{
	return reader->GetBufferLength();
}

SndTps* 
irrAudio::GetThePlayingBuffer(void)
{
	return reader->GetCurrentPlayingBuffer();
}
