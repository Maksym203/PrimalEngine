#pragma once
#include "Module.h"
#include <vector>
#include <string>

enum class ComponentType;
enum class GeometryType;
class Component;
class ComponentTransform;
class ComponentMesh;
class ComponentMaterial;
class ComponentCamera;
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


	void SetPendingToDelete(bool deleteGO) { isTimetoDelete = deleteGO; };

	bool isTimetoDelete;
	bool isActive;
	std::string name;

	GameObject* mParent;
	std::vector<GameObject*> mChildren;
	std::vector<Component*> mComponents;

	ComponentTransform* transform;
	GeometryType Stype;

	//Animation stuff

	void PushAnimation(Animation* pushedAnimation);

	std::vector<Animation*> animationsList;
	bool animBonesLink = false;
	bool linkChannels = false;
	bool showAnimBones = false;
	float currentTime = 0.f;
	bool isAnimationPlaying = false;
	bool hasAnimationStarted = false;
	float blendingCurrentTime = 0.f;
	float blendingDuration = 0.f;
	uint previousAnimation = 0;
	uint currentAnimation = 0;
	Animation* previousAnimationA = nullptr;
	Animation* currentAnimationA = nullptr;


};