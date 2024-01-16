#pragma once
#include "Module.h"
#include <vector>
#include <string>
#include "ModuleAnimation.h"
#include "MathGeoLib/include/Math/float3.h"
#include <math.h>
#include <vector>
#include "glmath.h"

enum class ComponentType;
enum class GeometryType;
class Component;
class ComponentTransform;
class ComponentMesh;
class ComponentMaterial;
class ComponentCamera;

struct AnimationFragment
{
	AnimationFragment();
	char name[32];
	float startFrame, endFrame;
	bool loop;
	Animation* originalAnimation;
};

class GameObject
{
public:

	GameObject();
	GameObject(GameObject* parent);
	~GameObject();

	void AddComponent(Component* component);
	void Update();
	GameObject* GetParent();
	bool SetNewParent(GameObject* newParent);
	bool GameObject::SetAsChildOf(GameObject* gameObject);
	void AttachChild(GameObject* child);
	void PrintInspector();
	bool CheckChildOf(GameObject* parent);
	void DeleteChild(GameObject* child);



	ComponentMesh* GetMeshComponent();

	ComponentTransform* GetTransformComponent();

	ComponentMaterial* GetComponentTexture();

	ComponentCamera* GetComponentCamera();


	void SetPendingToDelete(bool delete1) { isTimetoDelete = delete1; };

	bool isTimetoDelete;
	bool isActive;
	float time = 0.f;
	std::string name;

	GameObject* mParent;
	std::vector<GameObject*> mChildren;
	std::vector<Component*> mComponents;

	ComponentTransform* transform;
	GeometryType Stype;

	//Animation stuff

	void StartAnimation();

	void UpdateAnimations(float dt);

	void DeleteSelectedAnimation(Animation* anim);

	void PauseAnimation();

	void ResumeAnimation();

	void PlayAnimation(Animation* anim, float blendDuration = 0.2f, float Speed = 1.0f);

	void PushAnimation(Animation* pushedAnimation);

	//void DrawAnimationBones(GameObject* p);
	void UpdateChannels(const Animation* settings, const Animation* blend, float blendRatio);

	float3	GetCurrentChannelPosition(const Channels& ch, float currentKey, float3 default) const;

	float3	GetCurrentChannelRotation(const Channels& ch, float currentKey, float3 default) const;

	float3	GetCurrentChannelScale(const Channels& ch, float currentKey, float3 default) const;

	void AddAnimationClip(Animation* anim);

	std::vector<AnimationFragment> clips;
	AnimationFragment* selectedClip = nullptr;

	Animation* AnimateFragment(AnimationFragment clip);

	void SaveBone(GameObject* bones);

	bool FindMainBone();

	bool animBonesLink = false;

	bool linkChannels = false;

	bool showAnimBones = false;

	float currentTime = 0.f;

	bool isAnimationPlaying = true;

	float animationSpeed = 1.f;

	bool hasAnimationStarted = false;

	float blendingCurrentTime = 0.f;

	float blendingDuration = 0.f;

	uint previousAnimation = 0;

	uint currentAnimation = 0;

	Animation* previousAnimationA = nullptr;

	Animation* currentAnimationA = nullptr;

	GameObject* rootBone = nullptr;

	uint rootBoneIDnum;

	Channels* oneBone;

	std::map <GameObject*, Channels*> currentAnimationBone;
	std::map <GameObject*, Channels*> previousAnimationBone;

	std::vector<GameObject*> allBones;
	std::vector<Animation*> animationsList;
};