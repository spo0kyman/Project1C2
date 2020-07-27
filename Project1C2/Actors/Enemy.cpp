#include "Enemy.h"
#include "Math/Math.h"
#include "Graphics/ParticleSystem.h"
#include "Object/Scene.h"
#include "../Game.h"
#include <fstream>

bool Enemy::Load(const std::string& filename){
	bool success = false;
	std::ifstream stream(filename);
	if (stream.is_open()) {
		success = true;

		stream >> m_transform;

		std::string shapename;
		stream >> shapename;
		m_shape.Load(shapename);
	}
	return success;

}

void Enemy::Update(float dt){

	nc::Vector2 targetPosition = (m_target) ? m_target->GetTransform().position : nc::Vector2{ 400, 300 };
	nc::Vector2 direction = targetPosition -m_transform.position;
	direction.Normalize();
	nc::Vector2 velocity = direction * 0;//m_speed;
	m_transform.position = m_transform.position + (velocity * dt);
	m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(90.0f);
	m_transform.Update();
}

void Enemy::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::PROJECTILE) {
		m_destroy = true;
		m_scene->GetGame()->AddPoints(10);

		nc::Color colors[] = { {1,1,1}, nc::Color::red, {1,1,0}, {0,1,1} };
		nc::Color color = colors[rand() % 4];
		g_particleSystem.Create(m_transform.position, 0, 180, 30, 1, color, 100, 200);
	}
}
