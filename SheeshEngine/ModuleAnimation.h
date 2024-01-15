#pragma once
#include "Module.h"
#include "Globals.h"

#include <string>

struct Channels {

	std::map<double, float3> positionKeys;
	std::map<double, Quat> rotationKeys;
	std::map<double, float3> scaleKeys;
	std::map<double, float3>::const_iterator GetNextPosKey(double currentKey) const;
	std::map<double, Quat>::const_iterator GetNextRotKey(double currentKey) const;
	std::map<double, float3>::const_iterator GetNextScaleKey(double currentKey) const;
	std::map<double, float3>::const_iterator GetPreviousPosKey(double currentKey) const;
	std::map<double, Quat>::const_iterator GetPreviousRotKey(double currentKey) const;
	std::map<double, float3>::const_iterator GetPreviousScaleKey(double currentKey) const;

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