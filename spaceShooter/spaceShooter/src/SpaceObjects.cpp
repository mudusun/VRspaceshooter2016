#include "SpaceObjects.hpp"


//Spaceship
SpaceObjects::SpaceObjects(glm::vec3 speed, glm::vec3 position, float life,
	                       float armor, int size, int id) 
{
	this->step_ = speed;
	this->speedX_ = speed.x;
	this->speedZ_ = speed.z;
	this->posX_ = position.x;
	this->posY_ = position.y;
	this->posZ_ = position.z;
	this->life_ = life;
	this->armor_ = armor;
	this->size_ = size;
	this->id_ = id;
	this->outOfBounds_ = false;
}
//Enemy
SpaceObjects::SpaceObjects(glm::vec3 speed, glm::vec3 position, float life,
	                       float armor, int size, int mode, int id) 
{
	this->step_ = speed;
	this->speedX_ = speed.x;
	this->speedZ_ = speed.z;
	this->posX_ = position.x;
	this->posY_ = position.y;
	this->posZ_ = position.z;
	this->life_ = life;
	this->armor_ = armor;
	this->size_ = size;
	this->mode_ = mode;
	this->id_ = id;
	this->outOfBounds_ = false;
}
//weapon mode
SpaceObjects::SpaceObjects(glm::vec3 speed, glm::vec3 position,
	                       int size, int damage, int mode, glm::mat4 matrix, int id) 
{
	this->step_ = speed;
	this->speedX_ = speed.x;
	this->speedZ_ = speed.z;
	this->posX_ = position.x;
	this->posY_ = position.y;
	this->posZ_ = position.z;
	this->size_ = size;
	this->damage_ = damage;
	this->mode_ = mode;
	this->id_ = id;
	this->outOfBounds_ = false;

	this->matrix_ = matrix;
	this->posX_ = matrix_[3][0];
	this->posZ_ = matrix_[3][2];
}
SpaceObjects::~SpaceObjects() 
{
}

glm::vec3 SpaceObjects::getPosition()
{
	return glm::vec3(posX_, posY_, posZ_);
}
glm::vec3 SpaceObjects::getStep() 
{
	return step_;
}
float SpaceObjects::getLife() 
{
	return life_;
}
float SpaceObjects::getArmor()
{
	return armor_;
}
int SpaceObjects::getSize() 
{
	return size_;
}
float SpaceObjects::getDuration()
{
	return duration_;
}
int SpaceObjects::getMode()
{
	return mode_;
}
int SpaceObjects::getDamage() 
{
	return damage_;
}
bool SpaceObjects::getOutOfBounds()
{
	return outOfBounds_;
}
void SpaceObjects::updateSpeed(glm::vec3 speed)
{
	speedX_ = speed.x;
	speedZ_ = speed.z;
}
void SpaceObjects::updatePosition(glm::vec3 position) 
{
	posX_ = position.x;
	posZ_ = position.z;
}
void SpaceObjects::reduceLife(int hit) 
{
	life_ -= hit;
}
void SpaceObjects::reduceArmor(int hit)
{
	armor_ -= hit;
}

void SpaceObjects::privateInit()
{
}

void SpaceObjects::privateRender() {
}

void SpaceObjects::privateUpdate() 
{
	step_ = glm::vec3(speedX_, 0.0f, speedZ_);
	if (posZ_ > 0) 
    {
		outOfBounds_ = true;
	}
}