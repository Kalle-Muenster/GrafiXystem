#include "projectMacros.h"
#include "AudioObject.h"

#include <bass.h>
#include <bass_fx.h>

IAudioEmitter::IAudioEmitter(void)
{
	IsPlaying=false;

}

void
IAudioEmitter::InitiateAudioEmitter(TransformA* myTransform,const char *audioFileName)
{
	LoadeAudio(audioFileName);
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
		BASS_ChannelPlay(audioSource,true);
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
	audioSource = AUDIO->Loade3DSample(filename);

}


void
IAudioEmitter::SetMyPosition(TransformA *myTransform)
{
	BASS_ChannelSet3DPosition((DWORD)audioSource,myTransform->position.asBassVector(),myTransform->rotation.asBassVector(),&myTransform->movement);
	BASS_Apply3D();
}


AudioEmitter::AudioEmitter(void)
{
	
}


void
AudioEmitter::LoadeSample(const char* audioFileName)
{
	
	audioSource = AUDIO->Loade3DSample(audioFileName);
	SetMyPosition(&this->Connection()->transform);
	this->AudioVolume(0.8);

}





IAudioListener::IAudioListener(void)
{
	this->IsMuted=false;
}
IAudioListener::~IAudioListener(void)
{

}
void
IAudioListener::InitiateListener(TransformA* myTransform)
{
	this->SetMyPosition(myTransform);
	
}


void
IAudioListener::SetMyPosition(TransformA* myTranform)
{
	BASS_Set3DPosition(myTranform->position.asBassVector(), &myTranform->movement,myTranform->forward.asBassVector(),myTranform->up.asBassVector());
//	BASS_Set3DPosition(&(BASS_3DVECTOR)myTranform->position, &myTranform->movement,&(BASS_3DVECTOR)myTranform->forward,&(BASS_3DVECTOR)myTranform->up);
	BASS_Apply3D();
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

void
IAudioListener::DebugOutPosition(void)
{
	BASS_3DVECTOR temp1 = BASS_3DVECTOR(0,0,0);
	BASS_3DVECTOR temp2 = BASS_3DVECTOR(0,0,0);
	BASS_3DVECTOR temp3 = BASS_3DVECTOR(0,0,0);
	BASS_3DVECTOR temp4 = BASS_3DVECTOR(0,0,0);
	BASS_Get3DPosition(&temp1,&temp2,&temp3,&temp4);
	BASS_Apply3D();
	printf("\nposition: %f,%f,%f",temp1.x,temp1.y,temp1.z);
}