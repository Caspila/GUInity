#include "Sound.hpp"
#include <fmod.hpp>
#include "SoundSystem.hpp"


/** Constructor
 @param filename the filename of the audio
 */
Sound::Sound(string filename)
{
	FMOD_RESULT result = SoundSystem::getInstance()->createSound(filename, FMOD_DEFAULT, 0, &soundHandle);
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


/** Default Destructor */
Sound::~Sound()
{
    
	soundHandle->release();
    
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Sound destroyed (" << nCount << " remaining)" << endl;
#endif
}

/** soundHandle Getter
 @return FMOD Sound handle
 */
FMOD::Sound *const  Sound::getSoundHandle()
{
    return soundHandle;
}