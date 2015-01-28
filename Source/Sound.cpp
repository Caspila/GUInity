#include "Sound.hpp"
#include <fmod.hpp>
#include "SoundSystem.hpp"


Sound::Sound(string filename)
{
	FMOD_RESULT result = SoundSystem::getInstance()->createSound(filename, FMOD_DEFAULT, 0, &soundHandle);
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


Sound::~Sound()
{

	soundHandle->release();

#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Sound destroyed (" << nCount << " remaining)" << endl;
#endif
}
