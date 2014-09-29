#ifndef __IK_IRR_READER___
#define __IK_IRR_READER___

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

class IrrReader : public irrklang::IFileReader
{
public:

bool logToStdOut;

			IrrReader(FILE* file,const ik_c8* filename)
			{
				logToStdOut = true;
				BUFFER_LENGTH = IK_AUDIO_BUFFER_LENGTH;
				File = file;
			//	strcpy(FileName,filename);

				int i= 0;
				while(filename[i]!='\0')
				{
					
					FileName[i]=filename[i];
					i++;
				}
				FileName[i]='\0';

				fseek(File, 0, SEEK_END);
				FileSize = ftell(File);
				fseek(File, 0, SEEK_SET);
				Position=0;
				
			
					printf("AUDIO: -> Stream Created !..  %i bytes..\n",FileSize);
		
			
		
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
				return BUFFER_LENGTH;
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
				MultiBuffer =(SndTps*) buffer;
				Position += (ik_s32)fread(buffer,2,BUFFER_LENGTH,File);
				if(logToStdOut)
					printf("AUDIO: -> streamed %i bytes...  ",Position);
				return Position;
			}

			virtual bool seek(ik_s32 finalPos,bool  relativeMovement = false) 	
			{
				Position = relativeMovement?Position+finalPos:finalPos;
				if(logToStdOut)
					printf("AUDIO: -> Seek to position: %i ",Position);
				return fseek(File, finalPos, relativeMovement ? SEEK_CUR : SEEK_SET) == 0;
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

	ik_u32 BUFFER_LENGTH;
	FILE * File;
	ik_s32 FileSize;
	ik_c8 FileName[1024];
	SndTps* MultiBuffer;
	unsigned Position;
};

#endif
