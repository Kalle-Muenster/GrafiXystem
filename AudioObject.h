#ifndef _AUDIO_OBJECT_H_
#define _AUDIO_OBJECT_H_


#include "Utility.h"






class IAudioEmitter
{
protected:
	HSTREAM audioSource;
	bool IsPlaying;
	void SetMyPosition(Transform*);
public:
	IAudioEmitter(void);
	IAudioEmitter(Transform*);
	virtual ~IAudioEmitter(void)=0;
	virtual void LoadeAudio(const char*);
	virtual void PlayAudio(void);
	virtual void AudioPause(void);
	virtual float AudioVolume(float=2);
	virtual float PitchAudio(float=2);

};

class IAudioListener
{
protected:
	float mutedVolume;
	bool IsMuted;
	void SetMyPosition(Transform*);
public:
	IAudioListener(Transform*);
	IAudioListener(void);
	virtual ~IAudioListener(void);
	virtual void UpdatePosition(Transform*)=0;
	virtual bool ToggleMute();
	virtual float AudioVolume(float=2);
};
#endif