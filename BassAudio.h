#ifndef _BASS_AUDIO_H_
#define _BASS_AUIDO_H_

#include "Utility.h"
#include <bass.h>
#include <bass_fx.h>

class BassAudio
{
private:
	BassAudio(void);


public:
	
	virtual ~BassAudio(void);
	static BassAudio* GetInstance(void);
	HSTREAM LoadeMusic(const char*);
	HCHANNEL Loade3DSample(const char*);
	void LoadeBackgroundAudio(const char*);// or musik...
	void Play(void);
	void Pause(void);
	void SetListenerPosition(TransformA*);
	float Volume(float=2);
};

#endif