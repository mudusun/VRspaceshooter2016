#include "LifebarEnemy.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
LifebarEnemy::LifebarEnemy(int mode)
{
	mode_ = mode;

}
LifebarEnemy::~LifebarEnemy()
{

}
void LifebarEnemy::privateInit()
{

}
void LifebarEnemy::privateRender()
{
	if (this->mode_ == 0)
	{
		drawArmor();
	}
	if (this->mode_ == 1)
	{
		drawHealth();
	}

}
void LifebarEnemy::drawHealth()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);

	glTexCoord2d(0, 0);
	glVertex3f(pos_[0], pos_[1], pos_[2]);

	glTexCoord2d(1, 0);
	glVertex3f(pos_[0] + health_ / 10, pos_[1], pos_[2]);

	glTexCoord2d(1, 1);
	glVertex3f(pos_[0] + health_ / 10, pos_[1] + 0.5, pos_[2]);

	glTexCoord2d(0, 1);
	glVertex3f(pos_[0], pos_[1] + 0.5, pos_[2]);

	glEnd();

	glm::vec3 newPos_ = glm::vec3(-2.0f, 13.0f, 0.0f);
	matrix_ = glm::translate(glm::mat4(), newPos_);


}
void LifebarEnemy::drawArmor()
{
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);

	glTexCoord2d(0, 0);
	glVertex3f(pos_[0], pos_[1], pos_[2]);

	glTexCoord2d(1, 0);
	glVertex3f(pos_[0] + armor_ / 10, pos_[1], pos_[2]);

	glTexCoord2d(1, 1);
	glVertex3f(pos_[0] + armor_ / 10, pos_[1] + 0.5, pos_[2]);

	glTexCoord2d(0, 1);
	glVertex3f(pos_[0], pos_[1] + 0.5, pos_[2]);

	glEnd();

	glm::vec3 newPos_ = glm::vec3(-2.0f, 13.0f, 0.0f);
	matrix_ = glm::translate(glm::mat4(), newPos_);

}
void LifebarEnemy::setArmorEnemy(float armor)
{
	armor_ = armor;
}
void LifebarEnemy::setHealthEnemy(float health)
{
	health_ = health;
}
void LifebarEnemy::privateUpdate()
{

}