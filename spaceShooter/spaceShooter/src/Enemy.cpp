
#include "Enemy.hpp"
#include <GL\glut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Shader.hpp"


#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

Enemy::Enemy(float life, int mode, float posX) 
{
	x_ = 0;
	srand(time(0));
	random_ = rand() % 40 - 20;
	rand2_ = rand() % 20;

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
	translateVec_ = glm::vec3(posX, 0.0f, -500.0f);

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
		eShader_.initShaders("Shaders/red");
		
	}

	//sinus
	if (this->mode_ == 1) 
	{
		eShader_.initShaders("Shaders/phong");
		
	}
	
	//cosinus
	if (this->mode_ == 2) 
	{
		
		GLint texSampler;
		texSampler = glGetUniformLocation(eShader_.getProg(), "enemy");
		glUniform1i(texSampler, 0);
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

	//matrix_ = glm::translate(glm::mat4(), glm::vec3(0.0f, 10.0f, -500.0f));

	

}

void Enemy::privateRender()
{ 
	
	eShader_.enable();
	//normal
	
	if (this->mode_ == 0) 
	{

		glutSolidSphere(6.f, 20, 20);

	}
	//sin
	if (this->mode_ == 1) 
	{

		glutSolidSphere(3.f, 20, 20);

	}
	//cos
	else
	{

		glutSolidCube(6.f);


	}
	
	eShader_.disable();

  glColor3f(1.0f, 0.0f, 1.0f);  
  
 
}

void Enemy::privateUpdate()
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
		x_ = glm::sin(float(i) / 150.0f);
	}

	if (this->mode_ == 2)
	{
		static int i = 0;
		i++;
		x_ = glm::cos(float(i) / 150.0f);
	}

	matrix_ = glm::translate(matrix_, glm::vec3(x_, 0.0f, -0.50f));


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
