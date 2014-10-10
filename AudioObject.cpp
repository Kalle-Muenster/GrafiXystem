#include "projectMacros.h"
#include "AudioObject.h"

#include <bass.h>
#include <bass_fx.h>

IAudioEmitter::IAudioEmitter(void)
{

}

IAudioEmitter::IAudioEmitter(Transform* myTransform)
{
	SetMyPosition(myTransform);
	BASS_Apply3D();
}


IAudioEmitter::~IAudioEmitter(void)
{

}

void
IAudioEmitter::AudioPause(void)
{
	if(IsPlaying)
	{
		BASS_ChannelPause(audioSource);
		IsPlaying=false;
	}
}

void
IAudioEmitter::PlayAudio(void)
{
	if(!IsPlaying)
	{
		BASS_ChannelPlay(audioSource,false);
		IsPlaying=true;
	}
}

float
IAudioEmitter::AudioVolume(float setter)
{
	if(setter<=1)
		BASS_ChannelSetAttribute(audioSource,BASS_ATTRIB_VOL,setter);

	return BASS_ChannelGetAttribute(audioSource,BASS_ATTRIB_VOL,&setter);
}

float
IAudioEmitter::PitchAudio(float pitcher)
{
	if(pitcher<=1)
		
		//todo..

	throw "mach ich später...";
}

void
IAudioEmitter::LoadeAudio(const char* filename)
{
	AUDIO->LoadeAudio(filename);
}


void
IAudioEmitter::SetMyPosition(Transform *myTransform)
{
//	BASS_ChannelSet3DPosition((DWORD)audioSource,&myTransform->position,&myTransform->rotation,&myTransform->scale);
	BASS_Apply3D();
}











IAudioListener::IAudioListener(void)
{

}
IAudioListener::~IAudioListener(void)
{

}
void
IAudioListener::InitiateListener(TransformA* myTransform)
{
	this->SetMyPosition(myTransform);
	BASS_Apply3D();
}


void
IAudioListener::SetMyPosition(TransformA* myTranform)
{
	BASS_Set3DPosition(&myTranform->position, &myTranform->movement,&myTranform->forward,&myTranform->up);
}


bool
IAudioListener::ToggleMute(void)
{
	if(!IsMuted)
	{
		mutedVolume=BASS_GetVolume();
		BASS_SetVolume(0);
		this->IsMuted=true;
	}
	else
	{
		BASS_SetVolume(mutedVolume);
		IsMuted=false;
	}
	return IsMuted;
}

float
IAudioListener::AudioVolume(float setter)
{
	if(setter<=1)
		BASS_SetVolume(setter);
	return BASS_GetVolume();

}