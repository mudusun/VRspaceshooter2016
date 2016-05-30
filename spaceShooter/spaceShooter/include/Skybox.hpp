#pragma once



#include "SceneObject.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "C:/Users/hxu001/Documents/visual studio 2015/Projects/spaceShooter/spaceShooter/soil/SOIL.h"

class Skybox : public SceneObject 
{
public:
	Skybox(std::shared_ptr<Camera> cam);
	~Skybox();

protected:
	void loadSkybox();
	//unsigned int loadTexture(const char*);

private:
	void privateInit(), privateRender(), privateUpdate();

	GLuint cubeBox;
	int width_, height_;
	unsigned char* image_;
	Shader shader_;

	std::shared_ptr<Camera> cam_;
};