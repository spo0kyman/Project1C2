#pragma once
#include "Graphics/Shape.h"


namespace nc {
	class Scene;

	class Actor {
	public:
		enum class eType {
			PLAYER,
			ENEMY,
			PROJECTILE,
			LOCATOR
		};

	public:
		Actor() {}
		Actor(const Transform& transform, const Shape& shape) : m_transform{ transform }, m_shape{ shape } {}
		~Actor() {}

		virtual eType GetType() = 0;

		virtual bool Load(const std::string& filename);
		virtual void Load(std::istream& stream);

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

		virtual void OnCollision(Actor* actor) {}

		float GetRadius();

		bool IsDestroy() { return m_destroy; }
		void SetScene(Scene* scene) { m_scene = scene; }
		Transform& GetTransform() {	return m_transform;	}
		Shape& GetShape() {	return m_shape;	} 

		Actor* GetParent() { return m_parent; }
		Actor* GetChild() { return m_child; }

		void SetParent(Actor* parent) { m_parent = parent; parent->m_child = this; }
		void SetChild(Actor* child) { m_child = child; child->m_parent = this; }

	protected:
		bool m_destroy{ false };
		Scene* m_scene{ nullptr };
		Transform m_transform;
		Shape m_shape;

		Actor* m_parent{ nullptr };
		Actor* m_child{ nullptr };
	};
}