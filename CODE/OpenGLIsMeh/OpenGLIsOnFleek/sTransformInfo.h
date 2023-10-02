#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>


struct sTransformInfo
{
	sTransformInfo()
	{
		this->position = glm::vec3(0.0f);
		this->orientation = glm::vec3(0.0f);
		this->scale = 1.0f;
	}
	glm::vec3 position;
	glm::vec3 orientation;
	float scale;
	// 	glm::mat4 matModel;	// or matWorld
};
