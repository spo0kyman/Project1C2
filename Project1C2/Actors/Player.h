#pragma once
#include "Object/Actor.h"

class Player : public nc::Actor {
public:
	Player() {}
	virtual ~Player() {}

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

protected:
	float m_thrust{ 200 };
	float m_rotation;
	nc::Vector2 m_velocity;
};