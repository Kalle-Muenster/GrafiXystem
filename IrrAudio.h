#ifndef _____IRR__KLANG_____
#ifndef __IK_IRR_READER___
#include "IrrReader.h"
#endif
#define _____IRR__KLANG_____


#include "projectMacros.h"





class IrrFactured :	public IFileFactory
{
public:

	virtual IFileReader* createFileReader(const ik_c8* filename)
	{
		FILE* f=fopen(filename,"rb");
		return new IrrReader(f,filename);
	}

};

class irrAudio : public IInteractive
{
private:
	irrAudio(void);

public:
	static irrAudio GetInstance();
	
	virtual ~irrAudio(void);
	void Loade(char*);
	IrrFactured* factory;
	IrrReader* reader;
	ISoundDeviceList* deviceList;
	ISoundEngine* irrEngine;
	ISoundSource* irrSource;
	ISound* Controls; 

	bool CanGetNewBuffer();
	SndTps* GetThePlayingBuffer();
	UINT32 GetNumberOfSamplesInBuffer();

	
};


#endif
