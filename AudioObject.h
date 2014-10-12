#ifndef _AUDIO_OBJECT_H_
#define _AUDIO_OBJECT_H_


#include "Utility.h"



class IAudioEmitter
{
protected:
	HCHANNEL audioSource;
	void InitiateAudioEmitter(TransformA*,const char*);
	bool IsPlaying;
	void SetMyPosition(TransformA*);

public:
	IAudioEmitter(void);
//	IAudioEmitter(Transform*);
	virtual ~IAudioEmitter(void)=0;
	virtual void LoadeAudio(const char*);
	virtual void PlayAudio(void);
	virtual void AudioPause(void);
	virtual float AudioVolume(float=2);
	virtual float PitchAudio(float=2);

};

class AudioEmitter : public IConnectable , public IAudioEmitter
{
public:
	AudioEmitter(void);
	virtual void LoadeSample(const char*);
	

};


class IAudioListener
{
protected:
	float mutedVolume;
	bool IsMuted;
	void SetMyPosition(TransformA*);
public:
	IAudioListener(void);
	virtual ~IAudioListener(void);
	virtual void InitiateListener(TransformA*);
	virtual bool ToggleMute();
	virtual float AudioVolume(float=2);
	void DebugOutPosition(void);
};
#endif