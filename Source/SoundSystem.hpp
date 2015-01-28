#pragma once

#include <fmod.hpp>
#include <fmod_common.h>
#include <fmod_errors.h>
#include "Module.hpp"

class Sound;

class SoundSystem
{
public:
	SoundSystem();
	~SoundSystem();

	static SoundSystem* getInstance();
	
	int init();
	void shutdown();
	void playSound(shared_ptr<Sound> sound);


	FMOD_RESULT createSound(string filename, int mode, FMOD_CREATESOUNDEXINFO* exInfo, FMOD::Sound** sound);

	FMOD::System *system;
	FMOD::Channel *channel;
};

