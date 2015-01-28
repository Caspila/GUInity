#include <iostream>
#include "SoundSystem.hpp"
#include "Module.hpp"
#include "Sound.hpp"

SoundSystem::SoundSystem()
{
}


SoundSystem::~SoundSystem()
{
}

SoundSystem* SoundSystem::getInstance()
{
	static SoundSystem* instance; // Guaranteed to be destroyed.
		if (instance == nullptr)
			instance = new SoundSystem();
		return instance;
}

int SoundSystem::init()
{

		FMOD_RESULT result;
		system = nullptr;

		result = FMOD::System_Create(&system);      // Create the main system object.
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			return -1;
		}

		result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
		if (result != FMOD_OK)
		{
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			return -1;
		}
		

		//ERRCHECK(result);

		
	//ERRCHECK(result);

}

void SoundSystem::playSound(shared_ptr<Sound> sound)
{
	FMOD_RESULT result = system->playSound(sound->soundHandle, 0, false, &channel);
}

void SoundSystem::shutdown()
{
	//channel-->re
	system->release();
}

FMOD_RESULT SoundSystem::createSound(string filename, int mode, FMOD_CREATESOUNDEXINFO* exInfo, FMOD::Sound** sound)
{
	return system->createSound(filename.c_str(), FMOD_DEFAULT, 0, sound);
}