#pragma once

#include "Asset.hpp"
#include <fmod.hpp>
#include <fmod_common.h>
#include <fmod_errors.h>

/** Sound is an Asset that encapsulates a FMOD Sound. It's still in very early development stage */
class Sound :
public Asset
#ifdef GUINITY_DEBUG
, public StaticCounter<Sound>
#endif
{
private:
    /** Reference to the FMOD Sound */
    FMOD::Sound* soundHandle;
public:
    /** Constructor
     @param filename the filename of the audio
     */
	Sound(string filename);
    /** Default Destructor */
	virtual ~Sound();
    
    /** soundHandle Getter
     @return FMOD Sound handle
     */
    FMOD::Sound *const getSoundHandle();
    
    
	
};

