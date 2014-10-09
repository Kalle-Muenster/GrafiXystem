#ifndef _____IRR__KLANG_____
#define _____IRR__KLANG_____


#include "projectMacros.h"
using namespace irrklang;

union SndTps
{
	irrklang::ik_f32 As_f32;
	irrklang::ik_u32 As_u32;
	irrklang::ik_s16 As_s16[2];
	irrklang::ik_c8  As_sByte[4];
	irrklang::ik_u8  As_Byte[4];
};



void* AudioBuffer;
void initializeAudio(void);
void loadeTrack(const char* filepath);
void pause(void);
void play(void);
ISound* play3D(void);
ISoundSource* GetSoundSource(const char*);


class IrrReader : public irrklang::IFileReader
{
public:
	
bool logToStdOut;

			IrrReader(FILE* file,const ik_c8* filename)
			{
				logToStdOut = true;
				BUFFER_LENGTH=0;
				File = file;
			//	strcpy(FileName,filename);

				int i= 0;
				while(filename[i]!='\0')
				{
					
					Filename[i]=filename[i];
					i++;
				}
				Filename[i]='\0';

				fseek(File, 0, SEEK_END);
				FileSize = ftell(File);
				fseek(File, 0, SEEK_SET);
			
				
			
					printf("AUDIO: -> Stream Created !..  %i bytes..\n",FileSize);
		
			
		
			}
			
			virtual ~IrrReader(void)
			{
				
			}
			


			//void SetBufferLength(ik_u32 sizeInStereoSamples)
			//{
			//	BUFFER_LENGTH = sizeInStereoSamples;
			//	//printf("AUDIO: -> Buffer Size Changed... %i byte",BUFFER_LENGTH/4);
			//}
			//void SetBuffer(void *startAdress,int sizeInBytes)
			//{
			//	AudioBuffer = startAdress;
			//	BUFFER_LENGTH = sizeInBytes/4;
			//	//printf("AUDIO: -> Buffer Size Changed... %i byte",sizeInBytes);
			//}
			virtual ik_s32 read(void * buffer,ik_u32 sizeToRead)
			{
	
				AudioBuffer =  buffer;
				return (BUFFER_LENGTH = (ik_s32)fread(buffer,1,sizeToRead,File));
	
			}

			virtual bool seek(ik_s32 finalPos,bool  relativeMovement = false) 	
			{
				return fseek(File, finalPos, relativeMovement ? SEEK_CUR : SEEK_SET) == 0;
				if(logToStdOut)
					printf("AUDIO: -> Seek to position: %i ",getPos());
				
			}

			virtual const ik_c8* getFileName()
			{
				return Filename;
			}

			virtual ik_s32 getPos()
			{
				return ftell(File);
			}

			virtual ik_s32 getSize()
			{
				return FileSize;
			}
			SndTps* GetCurrentPlayingBuffer(void)
			{
				return (SndTps*) AudioBuffer;
			}

			ik_u32 GetBufferLength()
			{
				return BUFFER_LENGTH;
			}
		ik_u32 BUFFER_LENGTH;
		FILE* File;
		char Filename[1024];
		ik_s32 FileSize;
};


class IrrFactured :	public IFileFactory
{
public:

	virtual IFileReader* createFileReader(const ik_c8* filename)
	{
		FILE* file=fopen(filename,"rb");
		if (!file)
			return 0;

		return new IrrReader(file,filename);
	}

};

class irrAudio : public IInteractive
{
private:
	
	ISoundSource* isource;
public:
	irrAudio(void);
	//static irrAudio* GetInstance()
	//{
	//	if(!auInstance)
	//		auInstance=new irrAudio();
	//	return auInstance;
	//}
	void init(void);
	virtual ~irrAudio(void);
	void Loade(char* name)
{
	init();


	
	loadSource();
	printf("trackLoadedt");
//	Controls = controlls = 
//	Controls->setIsPaused(false);
}
	void loadSource(void);
	IrrReader* irrReader;
	IrrFactured* irrFactory;

	ISoundDeviceList* irrDeviceList();
	ISoundEngine* irrEngine();
	ISoundSource* irrSource();
	ISound* irrControls(); 

	bool CanGetNewBuffer();
	SndTps* GetThePlayingBuffer();
	int GetNumberOfSamplesInBuffer();

	
};

bool Active;

int AudioBufferLength;
irrklang::ISoundDeviceList* deviceList;
irrklang::ISoundEngine* engine; 
irrklang::ISound* controlls;
irrklang::ISoundSource* source;
IrrFactured* factory;
IrrReader* reader;
irrAudio* audio;



void
initializeAudio(void)
{
///	audio = new irrAudio();
	deviceList = irrklang::createSoundDeviceList(irrklang::ESOD_AUTO_DETECT);
	factory = new IrrFactured();

	engine = irrklang::createIrrKlangDevice(irrklang::ESOD_AUTO_DETECT,irrklang::ESEO_LINEAR_ROLLOFF|irrklang::ESEO_MULTI_THREADED,deviceList->getDeviceID(0));
	////
	engine->addFileFactory(factory);
	//factory->drop();
	Active=true;
}

bool trackLoaded = false;
void
loadeTrack(const char* filepath)
{
	if(Active)
	{
		source = engine->addSoundSourceFromFile(filepath,ESM_AUTO_DETECT,false);
		
	//	engine->play2D(source,false,false,false,false);
		
		trackLoaded=true;
	}
}

void
play(void)
{
engine->play2D(source,false,false,false,false);
}





void
pause(void)
{
	if(Active && trackLoaded && !controlls->getIsPaused())
	{
		controlls->setIsPaused(true);
	}
}
#endif
