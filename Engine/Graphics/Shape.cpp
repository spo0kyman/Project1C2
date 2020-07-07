#include "pch.h"
#include "Shape.h"
#include <fstream>


namespace nc {



	bool nc::Shape::Load(const std::string& filename) {
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open()) {
			success = true;

			while (!stream.eof()) {
				Vector2 point;
				stream >> point;

				if (!stream.eof()) {
					m_points.push_back(point);
				}
			}

			stream.close();
		}
		return success;
	}

	void nc::Shape::Draw(Core::Graphics& graphics, nc::Vector2 position, float scale, float angle) {

		for (size_t i = 0; i < m_points.size() - 1; i++)
		{
			nc::Vector2 p1 = m_points[i];
			nc::Vector2 p2 = m_points[i + 1];

			//transform
			//scale
			p1 = p1 * scale;
			p2 = p2 * scale;
			//rotate
			p1 = nc::Vector2::Rotate(p1, angle);
			p2 = nc::Vector2::Rotate(p2, angle);
			//translate
			p1 = p1 + position;
			p2 = p2 + position;

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}

	}
}
