//
// Created by Vlad Boroday on 2023-11-23.
//

#include "Object.h"

SEngine::ObjectRef<SEngine::Object> SEngine::Component::GetOwner()
{
	return m_owner;
}

void SEngine::TransformComponent::SetLocalPosition(SEngine::Vector2 position)
{
	m_localPosition = position;
}

SEngine::Vector2 SEngine::TransformComponent::GetLocalPosition()
{
	return m_localPosition;
}

void SEngine::TransformComponent::SetPosition(SEngine::Vector2 position)
{
	ObjectRef<SEngine::Object> obj = GetOwner();
	
	//obj->GetComponent<TransformComponent>();
}

SEngine::Vector2 SEngine::TransformComponent::GetPosition()
{
	return SEngine::Vector2();
}

