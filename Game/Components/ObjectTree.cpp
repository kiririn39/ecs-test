//
// Created by Vlad Boroday on 2023-11-26.
//

#include "ObjectTree.h"

void SEngine::ObjectTree::TickTree(SEngine::Time delta)
{

}

SEngine::ObjectRef<SEngine::Object> SEngine::ObjectTree::AddGameObject()
{
	m_objects.emplace_back(std::make_shared<SEngine::Object>());

	return m_objects.back();
}

void SEngine::ObjectTree::DeleteGameObject(SEngine::ObjectRef<SEngine::Object> object)
{
	if (object.expired())
		return;

	auto it = std::find_if(m_objects.begin(), m_objects.end(), [&](std::shared_ptr<Object>& obj)
	{
	  return obj == object.lock();
	});

	if (it != m_objects.end())
	{
		m_objects.erase(it);
	}
}
