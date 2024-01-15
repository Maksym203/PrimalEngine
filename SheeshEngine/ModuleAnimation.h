#pragma once
#include "Module.h"
#include "Globals.h"

#include <string>

struct Channels {
	std::string name;
	std::vector<float3> PosKeys;
	std::vector<Quat> RotKeys;
	std::vector<float3> ScaleKeys;
};

struct Animation {
	Animation(std::string name, float duration, float TicksPerSec)
	{
		this->name = name;
		this->duration = duration;
		this->TicksPerSec = TicksPerSec;
	};

	std::string name;
	float duration;
	float TicksPerSec;
	std::vector<Channels> channels, bakedChannels;
};

struct aiAnimation;

class ModuleAnimation : public Module
{
public:
	ModuleAnimation(Application* app, bool start_enabled = true);
	~ModuleAnimation() {};

	Animation* LoadAnimation(aiAnimation* anim);
};