#pragma once

#include "Asset.hpp"
#include <fmod.hpp>
#include <fmod_common.h>
#include <fmod_errors.h>

class Sound :
	public Asset
#ifdef GUINITY_DEBUG
	, public StaticCounter<Sound>
#endif
{
public:
	Sound(string filename);
	virtual ~Sound();

	FMOD::Sound *soundHandle;
};

