
#include "Enemy.hpp"
#include <GL\glut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Shader.hpp"


#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

Enemy::Enemy(float life, Model * model, int mode, float posX)
{
	x_ = 0;
	srand(time(0));
	random_ = rand() % 40 - 20;
	rand2_ = rand() % 20;

	model_ = model;
	this->mode_ = mode;

	if (rand2_> 15) 
	{
		radius_ = 1.0;
		life_ = 20;
	}
	else 
	{
		radius_ = 0.5;
		life_ = 10;
	}
	translateVec_ = glm::vec3(posX, 0.0f, -1000.0f);

	matrix_ = glm::translate(matrix_, translateVec_);

	privateInit();
}

Enemy::~Enemy()
{
}

void Enemy::privateInit()
{
	//normal
	if (this->mode_ == 0) 
	{
		
	}

	//sinus
	if (this->mode_ == 1) 
	{
		
	}
	
	//cosinus
	if (this->mode_ == 2) 
	{
		
		
	}

	list_id = glGenLists(1);   // list_idis an integer
	float z = rand2_ / 4 - 2;

	glNewList(list_id, GL_COMPILE);

	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 16.0f, 0.0f);
	glVertex3f(1.0f, 16.0f, 0.0f);
	glVertex3f(1.0f, 20.0f, 0.0f);
	glEnd();
	glEndList();


}

void Enemy::privateRender()
{ 
	if (this->mode_ == 0)
	{
		//moves automatically
		x_ = 0.f;
	}

	if (this->mode_ == 1)
	{
		static int i = 0;
		i++;
		x_ = glm::sin(float(i) / 50.0f);
	}

	if (this->mode_ == 2)
	{
		static int i = 0;
		i++;
		x_ = glm::cos(float(i) / 100.0f);
	}

	matrix_ = glm::translate(matrix_, glm::vec3(x_, 0.0f, 10.0f));


	model_->Render();
  
 
}

void Enemy::privateUpdate()
{
	

}


float Enemy::Radius() const
{
	return radius_;
}

glm::vec3 Enemy::TranslateVec() const
{
	return translateVec_;
}

void Enemy::die(float life)
{
	life_ -= life;
}

float Enemy::getLife()
{
	return life_;
}

void Enemy::setLife(float li)
{
	life_ = li;
}
