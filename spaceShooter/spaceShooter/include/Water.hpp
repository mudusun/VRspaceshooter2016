#pragma once


#include <GL/glew.h>
#include <windows.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>


#include "SceneObject.hpp"
#include "glm/glm.hpp"
#include "Shader.hpp"
#include "C:/Users/hxu001/Documents/visual studio 2015/Projects/spaceShooter/spaceShooter/soil/SOIL.h"

class Water : public SceneObject 
{
public:
	Water(glm::vec3 startPos, glm::vec3 step, int id);
	~Water();

protected:
	glm::vec3 getStep();
	glm::vec3 getPos();
	void field();
	

private:
	void privateInit();
	void privateRender();
	void privateUpdate();
	std::vector< glm::vec3 > vertexArray_;
	std::vector<unsigned int> indexArray_;
	std::vector< glm::vec2 > texCoordArray_; // texture coord array
	int waterX_;
	int waterZ_;
	int mode_;

	GLfloat waveTime;
	GLfloat waveWidth;
	GLfloat waveHeight;
	GLfloat	waveFreq;

	GLfloat fogColor_[4] = { 0.5f, 0.5f, 0.5f, 0.5f };

	glm::vec3 pos_, step_;
	
	Shader shader_;
};