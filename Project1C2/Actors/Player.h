#pragma once
#include "Object/Actor.h"

class Player : public nc::Actor {
public:
	Player() {}
	virtual ~Player() {}

	virtual eType GetType() override { return eType::PLAYER; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	void OnCollision(Actor* actor);

protected:
	float m_thrust{ 200 };
	float m_rotation{ 0 };
	float m_fireRate{ 0.2f };
	float m_fireTimer{ 1 };

	bool m_prevButtonPress{ false };

	nc::Vector2 m_velocity;
	float m_angularVelocity{ 0 };
};