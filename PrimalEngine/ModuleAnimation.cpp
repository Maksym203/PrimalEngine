#include "Application.h"
#include "ModuleAnimation.h"

ModuleAnimation::ModuleAnimation(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

Animation* ModuleAnimation::LoadAnimation(aiAnimation* anim) {

	std::string animName = anim->mName.C_Str();
	Animation* animation = new Animation(animName, anim->mDuration, anim->mTicksPerSecond);

	for (int i = 0; i < anim->mNumChannels; i++) {
		Channels channel;
		channel.name = anim->mChannels[i]->mNodeName.C_Str();
		uint pos = channel.name.find("_$AssimpFbx$_");
		if (pos != std::string::npos)
		{
			channel.name = channel.name.substr(0, pos);
		}
		for (int j = 0; j < anim->mChannels[i]->mNumPositionKeys; j++)
		{
			aiVector3D aiValue = anim->mChannels[i]->mPositionKeys[j].mValue;
			float3 positionKey = float3(aiValue.x, aiValue.y, aiValue.z);
			channel.positionKeys[anim->mChannels[i]->mPositionKeys[j].mTime] = positionKey;
		}
		for (int j = 0; j < anim->mChannels[i]->mNumRotationKeys; j++)
		{
			aiQuaternion aiValue = anim->mChannels[i]->mRotationKeys[j].mValue;
			Quat q = Quat(aiValue.x, aiValue.y, aiValue.z, aiValue.w);
			float3 rotationKey;
			double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
			double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
			rotationKey.x = std::atan2(sinr_cosp, cosr_cosp);
			double sinp = std::sqrt(1 + 2 * (q.w * q.x - q.y * q.z));
			double cosp = std::sqrt(1 - 2 * (q.w * q.x - q.y * q.z));
			rotationKey.y = 2 * std::atan2(sinp, cosp) - M_PI / 2;
			double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
			double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
			rotationKey.z = std::atan2(siny_cosp, cosy_cosp);
			channel.rotationKeys[anim->mChannels[i]->mRotationKeys[j].mTime] = rotationKey;
		}
		for (int j = 0; j < anim->mChannels[i]->mNumScalingKeys; j++)
		{
			aiVector3D aiValue = anim->mChannels[i]->mScalingKeys[j].mValue;
			float3 scaleKey = float3(aiValue.x, aiValue.y, aiValue.z);
			channel.scaleKeys[anim->mChannels[i]->mScalingKeys[j].mTime] = scaleKey;
		}

		animation->channels[channel.name] = channel;
	}
	return animation;
}

std::map<double, float3>::const_iterator Channels::GetNextPosKey(double currentKey) const
{
	return positionKeys.upper_bound(currentKey);
}

std::map<double, float3>::const_iterator Channels::GetNextRotKey(double currentKey) const
{
	return rotationKeys.upper_bound(currentKey);
}

std::map<double, float3>::const_iterator Channels::GetNextScaleKey(double currentKey) const
{
	return scaleKeys.upper_bound(currentKey);
}



std::map<double, float3>::const_iterator Channels::GetPreviousPosKey(double currentKey) const {
	std::map<double, float3>::const_iterator ret = positionKeys.lower_bound(currentKey);
	if (ret != positionKeys.begin())
		ret--;
	return ret;
}

std::map<double, float3>::const_iterator Channels::GetPreviousRotKey(double currentKey) const
{
	std::map<double, float3>::const_iterator ret = rotationKeys.lower_bound(currentKey);
	if (ret != rotationKeys.begin())
		ret--;
	return ret;
}

std::map<double, float3>::const_iterator Channels::GetPreviousScaleKey(double currentKey) const
{
	std::map<double, float3>::const_iterator ret = scaleKeys.lower_bound(currentKey);
	if (ret != scaleKeys.begin())
		ret--;
	return ret;
}

uint ModuleAnimation::ChannelSizeNumber(const Channels& channel) {

	uint ret = sizeof(uint) + channel.name.size() + sizeof(uint) * 3;

	ret += sizeof(double) * channel.positionKeys.size() + sizeof(float) * channel.positionKeys.size() * 3;
	ret += sizeof(double) * channel.rotationKeys.size() + sizeof(float) * channel.rotationKeys.size() * 4;
	ret += sizeof(double) * channel.scaleKeys.size() + sizeof(float) * channel.scaleKeys.size() * 3;

	return ret;
}

void ModuleAnimation::SaveCurrentChannel(const Channels& channel, char** cursor) {

	uint nameSize = channel.name.size();
	memcpy(*cursor, &nameSize, sizeof(uint));
	*cursor += sizeof(uint);

	memcpy(*cursor, channel.name.c_str(), channel.name.size());
	*cursor += channel.name.size();

	uint range[3] = { channel.positionKeys.size(), channel.rotationKeys.size(), channel.scaleKeys.size() };
	memcpy(*cursor, range, sizeof(uint) * 3);
	*cursor += sizeof(uint) * 3;

	SaveCurrentChannelKeys(channel.positionKeys, cursor);
	SaveCurrentChannelKeys(channel.rotationKeys, cursor);
	SaveCurrentChannelKeys(channel.scaleKeys, cursor);
}

void ModuleAnimation::SaveCurrentChannelKeys(const std::map<double, float3>& map, char** cursor) {
	std::map<double, float3>::const_iterator it = map.begin();

	for (it = map.begin(); it != map.end(); it++)
	{
		memcpy(*cursor, &it->first, sizeof(double));
		*cursor += sizeof(double);

		memcpy(*cursor, &it->second, sizeof(float) * 3);
		*cursor += sizeof(float) * 3;
	}
}

void ModuleAnimation::LoadNewChannel(Channels& channel, const char** cursor)
{
	uint bytes = 0;

	uint nameSize = 0;
	memcpy(&nameSize, *cursor, sizeof(uint));
	*cursor += sizeof(uint);

	if (nameSize > 0)
	{
		char* string = new char[nameSize + 1];
		bytes = sizeof(char) * nameSize;

		memcpy(string, *cursor, bytes);
		*cursor += bytes;
		string[nameSize] = '\0';

		channel.name = string;

		RELEASE_ARRAY(string);
	}

	uint range[3];
	memcpy(&range, *cursor, sizeof(uint) * 3);
	*cursor += sizeof(uint) * 3;

	LoadNewChannelKeys(channel.positionKeys, cursor, range[0]);
	LoadNewChannelKeys(channel.rotationKeys, cursor, range[1]);
	LoadNewChannelKeys(channel.scaleKeys, cursor, range[2]);
}

void ModuleAnimation::LoadNewChannelKeys(std::map<double, float3>& map, const char** cursor, uint size) {
	for (uint i = 0; i < size; i++)
	{
		double time;
		memcpy(&time, *cursor, sizeof(double));
		*cursor += sizeof(double);
		float data[3];
		memcpy(&data, *cursor, sizeof(float) * 3);
		*cursor += sizeof(float) * 3;

		map[time] = float3(data);
	}
}