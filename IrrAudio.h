#ifndef _____IRR__KLANG_____
#define _____IRR__KLANG_____
#include "projectMacros.h"
#include "ik_ifilefactory.h"

#include <windows.h>

#define IK_AUDIO_BUFFER_LENGTH (4096)


class IrrReader : public irrklang::IFileReader
{
public:

bool logToStdOut;

			IrrReader(FILE* file,const ik_c8* filename)
			{
				BUFFER_LENGTH = IK_AUDIO_BUFFER_LENGTH;
				File = file;
				strcpy(FileName,filename);
				FileSize = File->_bufsiz;
				File = fopen(filename,"r");
				logToStdOut = true;
				Position=0;
				printf("AUDIO: -> Stream Created !...");
				delete file;
				delete filename;
			}
			
			virtual ~IrrReader(void)
			{
				
			}
			
			SndTps* GetCurrentPlayingBuffer(void)
			{
				return (SndTps*) &MultiBuffer[0];
			}

			ik_u32 GetBufferLength()
			{
				return IK_AUDIO_BUFFER_LENGTH;
			}

			void SetBufferLength(ik_u32 sizeInStereoSamples)
			{
				BUFFER_LENGTH = sizeInStereoSamples;
				printf("AUDIO: -> Buffer Size Changed... %i byte",BUFFER_LENGTH/4);
			}
			void SetBuffer(void *startAdress,int sizeInBytes)
			{
				MultiBuffer = (SndTps*)startAdress;
				BUFFER_LENGTH = sizeInBytes/4;
				printf("AUDIO: -> Buffer Size Changed... %i byte",sizeInBytes);
			}
			virtual ik_s32 read(void * buffer,ik_u32 sizeToRead)
			{
				buffer = &MultiBuffer[0];
				Position += (ik_s32)fread(MultiBuffer,4,IK_AUDIO_BUFFER_LENGTH,File);
				if(logToStdOut)
					printf("AUDIO: -> streamed %i bytes...  ",Position);
				return Position;
			}

			virtual bool seek(ik_s32 finalPos,bool  relativeMovement = false) 	
			{
				Position = relativeMovement?Position+finalPos:finalPos;
				if(logToStdOut)
					printf("AUDIO: -> Seek to position: %i ",Position);
				return fseek(File,finalPos,relativeMovement?SEEK_CUR:SEEK_SET);
			}

			virtual const ik_c8* getFileName()
			{
				return FileName;
			}

			virtual ik_s32 getPos()
			{
				return Position;
			}

			virtual ik_s32 getSize()
			{
				return FileSize;
			}
protected:
	ik_u32 BUFFER_LENGTH;
	FILE * File;
	ik_s32 FileSize;
	ik_c8 FileName[1024];
	SndTps* MultiBuffer;
	unsigned Position;
};

bool Active;

class IrrAudio :
	public irrklang::IFileFactory
{

	

public:
	ISound* WaveOut;

	IrrAudio()
	{
		
		deviceList = irrklang::createSoundDeviceList(E_SOUND_OUTPUT_DRIVER::ESOD_AUTO_DETECT,NULL);
		irrEngine = irrklang::createIrrKlangDevice(E_SOUND_OUTPUT_DRIVER::ESOD_AUTO_DETECT,E_SOUND_ENGINE_OPTIONS::ESEO_DEFAULT_OPTIONS,0,NULL);
		
	}
	virtual ~IrrAudio(void);

	virtual IFileReader* createFileReader(const ik_c8* filename)
	{
		new IrrReader(fopen(filename,"r"),filename);
	}

	void SetFacturedReader(IFileFactory* factured)
	{
		irrEngine->addFileFactory(factured);
	}

	ISound* Loade(ik_c8* fileName)
	{
		irrSource = irrEngine->addSoundSourceFromFile(fileName,E_STREAM_MODE::ESM_AUTO_DETECT,false);
		return irrEngine->play2D(irrSource,true,true,true,true);
	}

	private:
	ISoundDeviceList* deviceList;
	ISoundEngine* irrEngine;
	ISoundSource* irrSource;
};




union SndTps
{
	irrklang::ik_f32 As_f32;
	irrklang::ik_u32 As_u32;
	irrklang::ik_s16 As_s16[2];
	irrklang::ik_c8  As_sByte[4];
	irrklang::ik_u8  As_Byte[4];
};

class irrAudio : public IInteractive
{
public:
	IrrReader* reader;
	irrAudio(void)
	{
		factory = IrrAudio();
		reader = (IrrReader*)factory.createFileReader("sinus441.wav");
		factory.SetFacturedReader(&factory);
		//reader->drop();
		Active=true;

		
	}
	virtual ~irrAudio(void)
	{

	}

	ISound* Controls; 

	ISound* OpenAudioFile(ik_c8* fileName)
	{
		if(Active)
			return(Controls = factory.Loade(fileName));
		else return NULL;
	}
private:
	IrrAudio factory;
};





#endif