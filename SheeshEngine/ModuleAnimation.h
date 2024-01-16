#pragma once
#include "Module.h"
#include "Globals.h"

#include <string>
#include <math.h>
#include <iostream>
#include "MathGeoLib/include/Math/float3.h"

struct Channels {

	std::map<double, float3> positionKeys;
	std::map<double, Quat> rotationKeys;
	std::map<double, float3> scaleKeys;
	std::string name;
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

	bool loop = true;

	std::vector<Channels> channels, bakedChannels;
};

struct aiAnimation;

class ModuleAnimation : public Module
{
public:
	ModuleAnimation(Application* app, bool start_enabled = true);
	~ModuleAnimation() {};

	Animation* LoadAnimation(aiAnimation* animation);
	uint ChannelSizeNumber(const Channels& channel);
	void SaveCurrentChannel(const Channels& channel, char** cursor);
	void SaveCurrentChannelKeys(const std::map<double, float3>& map, char** cursor);
	void SaveCurrentChannelKeysWithQuaternion(const std::map<double, Quat>& map, char** cursor);
	void LoadNewChannel(Channels& channel, const char** cursor);
	void LoadNewChannelKeys(std::map<double, float3>& map, const char** cursor, uint size);
	void LoadNewChannelKeys(std::map<double, Quat>& map, const char** cursor, uint size);
};