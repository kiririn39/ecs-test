//
// Created by Vlad Boroday on 2023-11-23.
//

#ifndef UNTITLED1_GAME_COMPONENTS_OBJECT_H_
#define UNTITLED1_GAME_COMPONENTS_OBJECT_H_

#include "vector"
#include "memory"
#include "Game/Core/Types.h"

namespace SEngine
{
	class Object
	{
	 public:
		template<class T>
		std::shared_ptr<T> GetOrAddComponent()
		{
			for (auto& component : m_components)
			{
				if (std::dynamic_pointer_cast<T>(component))
				{
					return component;
				}
			}

			std::shared_ptr<T> component = std::make_shared<T>();

			m_components.push_back(component);
			component.m_owner = this;

			return component;
		}

		template<class T>
		std::shared_ptr<T> GetComponent()
		{
			for (auto& component : m_components)
			{
				auto result = std::dynamic_pointer_cast<T>(component);
				if (result)
				{
					return result;
				}
			}

			return nullptr;
		}

	 private:
		std::vector<std::shared_ptr<class Component>> m_components;

		ObjectRef<Object> m_parent;
		std::vector<ObjectRef<Object>> m_children;
	};

	class Component
	{
		friend class Object;

	 public:
		virtual ~Component() = default;

		virtual void Update(Time timeDelta)
		{
		};

		ObjectRef<Object> GetOwner();

	 private:
		ObjectRef<Object> m_owner;

	};

	class TransformComponent : public SEngine::Component
	{
	 public:
		TransformComponent() = default;

		void SetLocalPosition(Vector2 position);
		Vector2 GetLocalPosition();

		void SetPosition(Vector2 position);
		Vector2 GetPosition();

	 private:
		Vector2 m_localPosition;
	};
}

#endif //UNTITLED1_GAME_COMPONENTS_OBJECT_H_
