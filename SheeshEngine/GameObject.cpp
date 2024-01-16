#include "GameObject.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "OurPrimitive.h"
#include "Application.h"
#include "ModuleAnimation.h"


GameObject::GameObject()
{
	name = "GameObject";
	mParent = nullptr;
	transform = new ComponentTransform(this);
	isTimetoDelete = false;
	Stype = GeometryType::NONE;
	mComponents.push_back(transform);
}

GameObject::~GameObject()
{
	name = "";
	transform = nullptr;

	if (isTimetoDelete && mParent != nullptr) {
		mParent->DeleteChild(this);
	}


	for (size_t i = 0; i < mComponents.size(); ++i)
	{
		delete mComponents[i];
		mComponents[i] = nullptr;
	}

	for (size_t i = 0; i < mChildren.size(); ++i)
	{
		delete mChildren[i];
		mChildren[i] = nullptr;
	}

	mComponents.clear();

}

GameObject::GameObject(GameObject* parent)
{
	name = "GameObject";
	this->mParent = parent;
	isTimetoDelete = false;
	Stype = GeometryType::NONE;

	if (parent != nullptr)
	{
		parent->mChildren.push_back(this);
	}

	transform = new ComponentTransform(this);
	

	mComponents.push_back(transform);
}

void GameObject::AddComponent(Component* component)
{
	mComponents.push_back(component);
	component->mOwner = this;
}


void GameObject::Update()
{
	// No tots els children o components tenen un update
	for (size_t i = 0; i < mChildren.size(); ++i)
	{
		mChildren[i]->Update();
	}

	for (size_t i = 0; i < mComponents.size(); ++i)
	{
		mComponents[i]->Update();
	}
}

GameObject* GameObject::GetParent()
{
	return mParent;
}

ComponentMesh* GameObject::GetMeshComponent()
{
	for (size_t i = 0; i < mComponents.size(); i++)
	{
		if (mComponents[i]->type == ComponentType::MESH)
		{
			return (ComponentMesh*)mComponents[i];
		}
	}
	return nullptr;
}

ComponentTransform* GameObject::GetTransformComponent()
{
	for (size_t i = 0; i < mComponents.size(); i++)
	{
		if (mComponents[i]->type == ComponentType::TRANSFORM)
		{
			return (ComponentTransform*)mComponents[i];
		}
	}
	return nullptr;
}

ComponentMaterial* GameObject::GetComponentTexture()
{
	for (size_t i = 0; i < mComponents.size(); i++)
	{
		if (mComponents[i]->type == ComponentType::MATERIAL) {

			return (ComponentMaterial*)mComponents[i];
		}
	}

	return nullptr;
}

ComponentCamera* GameObject::GetComponentCamera()
{
	for (size_t i = 0; i < mComponents.size(); i++)
	{
		if (mComponents[i]->type == ComponentType::CAMERA) {

			return (ComponentCamera*)mComponents[i];
		}
	}

	return nullptr;
}


bool GameObject::CheckChildOf(GameObject* parent)
{
	if (parent == this)
	{
		return true;
	}
	if (parent->mChildren.empty())
	{
		return false;
	}
	for (size_t i = 0; i < parent->mChildren.size(); i++)
	{
		if (CheckChildOf(parent->mChildren[i])) return true;
	}
	return false;
}

void GameObject::DeleteChild(GameObject* child)
{
	for (int i = 0; i < mChildren.size(); i++) {
		if (mChildren[i] == child) {
			mChildren.erase(mChildren.begin() + i);
			child->mParent = nullptr;
		}
	}
}

bool GameObject::SetNewParent(GameObject* newParent)
{
	if (mParent != nullptr) {
		if (newParent->CheckChildOf(this)) return false;

		mParent->DeleteChild(this);
	}

	mParent = newParent;
	newParent->mChildren.push_back(this);

	return true;
}

bool GameObject::SetAsChildOf(GameObject* gameObject)
{
	if (CheckChildOf(gameObject))
	{
		return false;
	}
	gameObject->mParent = this;
	mChildren.push_back(gameObject);
	return true;
}

void GameObject::AttachChild(GameObject* child)
{
	child->mParent = this;
	mChildren.push_back(child);
	//child->transform
	//child->transform
}



void GameObject::PrintInspector()
{


	char* listComponenets[]{ "Add Component", "Mesh Component", "Texture Component" };
	char aux[255] = { ' ' }; 


	if (mParent != nullptr)
	{
		strcpy(aux, this->name.c_str());


		ImGui::BulletText("Name:");
		ImGui::SameLine();

		
		ImGui::InputText("##Name", aux, 255, ImGuiInputTextFlags_EnterReturnsTrue);

		if (ImGui::IsKeyDown(ImGuiKey_Enter))
			name = aux;


		if (ImGui::Button("Delete") || isTimetoDelete) {
			
			isTimetoDelete = true;
			delete App->hierarchy->objSelected;
			App->hierarchy->objSelected = nullptr;
		}

		for (size_t i = 0; i < mComponents.size(); i++)
		{
			ImGui::Separator();

			mComponents[i]->PrintInspector();
		}

		ImGui::Separator();
		ImGui::Text("");
		ImGui::Text("");
		ImGui::Text("");

		ImGui::Text("");
		ImGui::SameLine(ImGui::GetWindowWidth() / 6);


	}


}

void GameObject::PushAnimation(Animation* pushedAnimation) {

	this->animationsList.push_back(pushedAnimation);

}


void GameObject::StartAnimation() {
	if (rootBone == nullptr) {
		if (!allBones.empty()) {
			rootBone == allBones[0];
		}
		else {
			return;
		}
	}
}

void GameObject::UpdateAnimations(float dt, bool playing) {

	// Update Current Animation
	if (playing) {
		if (!hasAnimationStarted) { StartAnimation(); }
		else {

			if (currentAnimationA != nullptr) {

				//Updating animation blend // Este comentario tiene ya 3 generaciones
				float blendRatio = 0.0f;
				if (blendingDuration > 0.0f)
				{
					previousAnimation += dt;
					blendingCurrentTime += dt;

					if (blendingCurrentTime >= blendingDuration)
					{
						blendingDuration = 0.0f;
					}
					else if (previousAnimationA && previousAnimation >= previousAnimationA->duration)
					{
						if (previousAnimationA->loop == true)
						{
							previousAnimation = 0.0f;
						}
					}

					if (blendingDuration > 0.0f)
						blendRatio = blendingCurrentTime / blendingDuration;
				}
				//time += dt;

				currentAnimation = dt * currentAnimationA->TicksPerSec;

				UpdateChannels(currentAnimationA, blendRatio > 0.0f ? previousAnimationA : nullptr, blendRatio);
			}
		}
	}

	// Draw bones if needed
	if (showAnimBones) {
		/*DrawAnimationBones(rootBone);*/
	}
}

//void GameObject::DrawAnimationBones(GameObject* p)
//{
//	if (!p->mChildren.empty()) {
//		for (int i = 0; i < p->mChildren.size(); i++) {
//			p->mChildren[i]->DrawAnimationBones(p->mChildren[i]);
//
//			std::vector<float3> line;
//
//		}
//	}
//}

void GameObject::UpdateChannels(const Animation* settings, const Animation* blend, float blendRatio) {

}

float3	GameObject::GetCurrentChannelPosition(const Channels& ch, float currentKey, float3 default) const {
	return default;
}

Quat	GameObject::GetCurrentChannelRotation(const Channels & ch, float currentKey, Quat default) const {
	return default;
}

float3	GameObject::GetCurrentChannelScale(const Channels & ch, float currentKey, float3 default) const {
	return default;
}