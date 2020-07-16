#include "Player.h"
#include "Math/Math.h"
#include <fstream>

bool Player::Load(const std::string& filename) {
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

void Player::Update(float dt) {
	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * m_thrust; }
	force = nc::Vector2::Rotate(force, m_transform.angle);

	m_velocity = m_velocity + (force * dt);
	m_velocity = m_velocity * 0.98f;

	m_transform.position = m_transform.position + (m_velocity * dt);

	if (m_transform.position.x > 800) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = 800;
	if (m_transform.position.y > 600) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = 600;
	//if (Core::Input::IsPressed('A')) position += nc::Vector2::left * (speed * dt);
	//if (Core::Input::IsPressed('D')) position += nc::Vector2::right * (speed * dt);

	if (Core::Input::IsPressed('A')) m_transform.angle -= dt * nc::DegreesToRadians(360.0f);
	if (Core::Input::IsPressed('D')) m_transform.angle += dt * nc::DegreesToRadians(360.0f);

	m_transform.Update();
}
