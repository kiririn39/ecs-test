//
// Created by Vlad Boroday on 2023-11-26.
//

#ifndef UNTITLED1_GAME_COMPONENTS_OBJECTTREE_H_
#define UNTITLED1_GAME_COMPONENTS_OBJECTTREE_H_

#include "Game/Core/Types.h"
#include "Object.h"

namespace SEngine
{
	class ObjectTree
	{
		SEngine::ObjectRef<Object> AddGameObject();

		void DeleteGameObject(SEngine::ObjectRef<Object> object);

		void TickTree(Time delta);

	 private:
		std::vector<std::shared_ptr<Object>> m_objects;
	};
}

#endif //UNTITLED1_GAME_COMPONENTS_OBJECTTREE_H_
