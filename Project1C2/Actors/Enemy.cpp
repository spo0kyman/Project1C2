#include "Enemy.h"
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


	m_transform.Update();
}
