
#include "BitmapText.hpp"
#include <GL\glut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

BitmapText::BitmapText()
{
}

BitmapText::~BitmapText()
{
}


void BitmapText::drawBitmapText(const char *string, float x, float y)
{
	const char *c;
	
	glWindowPos2f(x, y);

	for (c = string; *c != '\0'; c++)
	{
		//iterate through the string character by character to display it by using the function,font type is GLUT_BITMAP_HELVETICA_12
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

//void  BitmapText::drawStrokeText(char*string, int x, int y, int z)
//{
//	char *c;
//	glPushMatrix();
//	glTranslatef(x, y + 8, z);
//	//glScalef(0.09f, -0.08f, z);
//
//	for (c = string; *c != '\0'; c++)
//	{
//		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c); //display each character , it iterates on all the characters and displays them
//	}
//	glPopMatrix();
//}



void BitmapText::privateInit()
{
	

}

//void BitmapText::reshape(int w, int h)
//{
//
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(0, w, h, 0);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//}

void BitmapText::privateRender()
{

	glColor3f(1, 0.5, 0);
	drawBitmapText("3D Space Shooting", 100, 600);

}



