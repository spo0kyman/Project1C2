#pragma once
#include "Graphics/Shape.h"


namespace nc {

	class Actor {
	public:
		Actor() {}
		Actor(const Transform& transform, const Shape& shape) : m_transform{ transform }, m_shape{ shape } {}
		~Actor() {}

		virtual bool Load(const std::string& filename);

		virtual void Update(float dt);

		void Draw(Core::Graphics& graphics);

		Transform& GetTransform() {	return m_transform;	}

		Shape& GetShape() {	return m_shape;	}

	protected:
		Transform m_transform;
		Shape m_shape;
	};
}