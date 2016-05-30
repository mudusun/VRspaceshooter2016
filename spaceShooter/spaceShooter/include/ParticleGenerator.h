#pragma once
/*
*		This Code Was Created By Jeff Molofee 2000
*		If You've Found This Code Useful, Please Let Me Know.
*		Visit My Site At nehe.gamedev.net
*/

#include <windows.h>				// Header File For Windows
#include <stdio.h>					// Header File For Standard Input/Output
#include <gl\gl.h>					// Header File For The OpenGL32 Library
#include <gl\glu.h>					// Header File For The GLu32 Library
#include <SceneObject.hpp>
#include "C:/Users/hxu001/Documents/visual studio 2015/Projects/spaceShooter/spaceShooter/soil/SOIL.h"


#define	MAX_PARTICLES	3000		// Number Of Particles To Create



class ParticleGenerator : public SceneObject
{
public:
	ParticleGenerator(int mode, glm::mat4 matrix);
	~ParticleGenerator();

	
protected:
	void privateInit();
	void privateRender();
	void privateUpdate();
	

private:
	typedef struct						// Create A Structure For Particle
	{
		bool	active;					// Active (Yes/No)
		float	life;					// Particle Life
		float	fade;					// Fade Speed
		float	r;						// Red Value
		float	g;						// Green Value
		float	b;						// Blue Value
		float	x;						// X Position
		float	y;						// Y Position
		float	z;						// Z Position
		float	xi;						// X Direction
		float	yi;						// Y Direction
		float	zi;						// Z Direction
		float	xg;						// X Gravity
		float	yg;						// Y Gravity
		float	zg;						// Z Gravity
	}
	particles;							// Particles Structure

	particles particle[MAX_PARTICLES]; // Particle Array (Room For Particle Info)
	GLfloat colors[12][3];
	GLuint tex_id;
	float slowdown = 2.0;
	int mode_;
	glm::mat4 matrix;

};






