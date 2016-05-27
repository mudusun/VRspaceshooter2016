
#include "SpaceShip.hpp"



SpaceShip::SpaceShip()
{
	radius_ = 12.0f; // Collision sphere radius
	translateVec_ = glm::vec3(0.0f, 0.0f, 4.0f);
	life_ = 100;
	scores_ = 0;
	
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::privateInit()
{
	glm::mat4 m =getMatrix();
	particleImg_.reset(new ParticleGenerator(0, m));
	this->addSubObject(particleImg_);

	vertexArray_ = {
		glm::vec3(-24, -6, 10), glm::vec3(-4, 0, 0), glm::vec3(0, 0, -32), glm::vec3(0, 4, 0),
		glm::vec3(0, -4, 0), glm::vec3(4, 0, 0), glm::vec3(24, -6, 10)
	};

	indexArray_ = { 0, 1, 2,	5, 6, 2,	1, 3, 2,	3, 5, 2,	1, 4, 3,	3, 4, 5 };

	// Calculate normals 
	normalArray_ = std::vector<glm::vec3>(vertexArray_.size(), glm::vec3(0, 0, 0));

	for (int i = 0; i < indexArray_.size(); i += 3) {

		auto p1 = vertexArray_[indexArray_[i + 0]];
		auto p2 = vertexArray_[indexArray_[i + 1]];
		auto p3 = vertexArray_[indexArray_[i + 2]];

		glm::vec3 v1 = p2 - p1;
		glm::vec3 v2 = p3 - p1;

		glm::vec3 v3 = p3 - p2;
		glm::vec3 v4 = p1 - p2;

		glm::vec3 v5 = p1 - p3;
		glm::vec3 v6 = p2 - p3;

		glm::vec3 normal = glm::cross(v1, v2);

		float w1 = std::acos(glm::dot(v1, v2) / (glm::length(v1) * glm::length(v2)));
		float w2 = std::acos(glm::dot(v3, v4) / (glm::length(v3) * glm::length(v4)));
		float w3 = std::acos(glm::dot(v5, v6) / (glm::length(v5) * glm::length(v6)));

		normalArray_[indexArray_[i + 0]] += w1 * normal;
		normalArray_[indexArray_[i + 1]] += w2 * normal;
		normalArray_[indexArray_[i + 2]] += w3 * normal;
	}

	for each (auto n in normalArray_) {
		n = glm::normalize(n);
	}

	float g = 5.f;

}

void SpaceShip::privateRender()
{
	shaderActive_.enable();
	glColor3f(0.0f, 1.0f, 1.0f);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);
	glNormalPointer(GL_FLOAT, 0, &normalArray_[0]);
	glDrawElements(GL_TRIANGLES, indexArray_.size(), GL_UNSIGNED_INT, &indexArray_[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_CUBE_MAP);

	shaderActive_.disable();

}

float SpaceShip::getShieldRegen() const
{

	return shieldRegen_;
}

void SpaceShip::privateUpdate()
{
	if (getShieldRegen() > 0.f) 
	{

		if (life_ < 100) 
		{

			if (shieldRegenTimer_ > 1.f)
			{

				life_++;
				shieldRegenTimer_ = 0.f;
			}
			shieldRegenTimer_ += getShieldRegen();
		}
	}
}

void SpaceShip::moveRight()
{
	if (translateVec_[0] < 50) {
		glm::vec3 v = glm::vec3(0.3f, 0.0f, 0.0f);
		matrix_ = glm::translate(matrix_, v);

		translateVec_ += v;
	}

}
void SpaceShip::moveLeft()
{
	if (translateVec_[0] > -50) {
		glm::vec3 v = glm::vec3(-0.3f, 0.0f, 0.0f);
		matrix_ = glm::translate(matrix_, v);

		translateVec_ += v;
	}
}

void SpaceShip::moveUp()
{
	if (translateVec_[1] < 3) {
		glm::vec3 v = glm::vec3(0.0f, 0.1f, 0.0f);
		matrix_ = glm::translate(matrix_, v);

		translateVec_ += v;
	}
}
void SpaceShip::moveDown()
{
	if (translateVec_[1] > -3) {
		glm::vec3 v = glm::vec3(0.0f, -0.1f, 0.0f);
		matrix_ = glm::translate(matrix_, v);

		translateVec_ += v;
	}
}

float SpaceShip::Radius()
{
	return radius_;
}

glm::vec3 SpaceShip::TranslateVec()
{
	return translateVec_;
}

void SpaceShip::die(float life)
{
	life_ -= life;
}

float SpaceShip::getLife()
{
	return life_;
}

void SpaceShip::setLife(float l)
{
	life_ = l;
}

int SpaceShip::getScores()
{
	return scores_;
}

void SpaceShip::addScores(int score)
{
	scores_ += score;
}
