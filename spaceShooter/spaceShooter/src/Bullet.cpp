#include "Bullet.hpp"
#include <GL\glut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


Bullet::Bullet(int mode, glm::mat4 spaceShipMatrix, int type)
{
  //radius_ = 0.2;
	mode_ = mode;
	matrix_ = spaceShipMatrix;
	if (mode_ == 0)
	{
		speed_ = 5.0f;
	
	}
	if (mode_ == 1)
	{
		speed_ = 1.0f;
		
	}

	if (type == 1)//spaceship
	{
		speed_ *= -1.0;
	}
}

Bullet::~Bullet()
{
}

void Bullet::privateInit()
{
    list_id = glGenLists(1);
    glNewList(list_id, GL_COMPILE);
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 1.0f, 0.0f );
    glColor3f( 0.0f, 0.0f, 0.0f );
    glVertex3f(translateVec_[0] + 0.1, translateVec_[1] - 0.1, translateVec_[2] );
    glVertex3f(translateVec_[0] + 0.1, translateVec_[1] + 0.1, translateVec_[2] );
    glVertex3f(translateVec_[0] - 0.1, translateVec_[1] + 0.1, translateVec_[2] );
    glVertex3f(translateVec_[0] - 0.1, translateVec_[1] - 0.1, translateVec_[2] );
    glEnd();
    glEndList();

	
}

void Bullet::privateRender()
{

	if (this->mode_ == 0)   //bullet from enemy
	{
		glBegin(GL_QUADS);
		glVertex3f(1.f, 0.f, 0.f);
		glVertex3f(1.f, 0.f, -1.f);
		glVertex3f(-1.f, 0.f, -1.f);
		glVertex3f(-1.f, 0.f, 0.f);
		glEnd();
	}
	
	if (this->mode_ == 1)     //bullet from spaceship
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_DIFFUSE);
		glShadeModel(GL_SMOOTH);
		glColor3f(1.0f, 0.0f, 0.0f);
		int radius = 2;
		int slices = 50;
		GLint stacks = 100;
		glutSolidSphere(radius, slices, stacks);
		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL);
	}
}

void Bullet::privateUpdate()
{
	matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, speed_));
}

void Bullet::SetPosition(glm::vec3 pos)
{
    translateVec_ = pos;
    privateInit();
}

void Bullet::SetDirection(glm::vec3 dir)
{
    direction_= dir;
    privateInit();
}


float Bullet::Radius()
{
    return radius_;
}

glm::vec3 Bullet::TranslateVec()
{
    return translateVec_;
}




