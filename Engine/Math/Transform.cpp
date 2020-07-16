#include "pch.h"
#include "Transform.h"

namespace nc {
	std::istream& nc::operator>>(std::istream& stream, Transform& transform)
	{
		stream >> transform.position;

		std::string line;

		std::getline(stream, line);
		transform.scale = stof(line);

		std::getline(stream, line);
		transform.angle = stof(line);

		return stream;
	}
	void Transform::Update(){

		nc::Matrix33 mxScale;
		mxScale.Scale(scale);

		nc::Matrix33 mxRotate;
		mxRotate.Rotate(angle);

		Matrix33 mxt;
		mxt.Translate(position);

		nc::Matrix33 mx = mxScale * mxRotate * mxt;

	}
}
