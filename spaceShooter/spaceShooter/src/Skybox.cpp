#include "Skybox.hpp"



//enum {SKY_WEST=0,SKY_SOUTH,SKY_EAST,SKY_NORTH,SKY_UP,SKY_DOWN};
//unsigned int cubeBox[6];


Skybox::Skybox(std::shared_ptr<Camera> cam) 
{
	cam_ = cam;
}

Skybox::~Skybox() 
{
}

void Skybox::privateInit() 
{

	loadSkybox();
	shader_.initShaders("Shaders/skybox");
	shader_.enable();
	GLint texSampler;

	texSampler = glGetUniformLocation(shader_.getProg(), "skybox");
	glUniform1i(texSampler, 0);
	shader_.disable();

}

void Skybox::privateRender() 
{
	


	shader_.enable();
	glFrontFace(GL_CW);
	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeBox);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	float v[8][3] = 
	{

		{ -1.0f, -1.0f,  1.0f },
		{ 1.0f, -1.0f,  1.0f },
		{ 1.0f,  1.0f,  1.0f },
		{ -1.0f,  1.0f,  1.0f },
		{ -1.0f, -1.0f, -1.0f },
		{ 1.0f, -1.0f, -1.0f },
		{ 1.0f,  1.0f, -1.0f },
		{ -1.0f,  1.0f, -1.0f },
	};

	unsigned int i[24] = 
	{
		0,1,2,3,
		1,5,6,2,
		5,4,7,6,
		4,0,3,7,
		0,4,5,1,
		2,6,7,3
	};

	glBegin(GL_QUADS);
	for (int k = 0; k < 24; ++k) 
	{
		glTexCoord3f(v[i[k]][0], v[i[k]][1], v[i[k]][2]);
		glVertex3f(v[i[k]][0], v[i[k]][1], v[i[k]][2]);
	}
	glEnd();

	glDisable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	shader_.disable();
}

void Skybox::privateUpdate() 
{

	matrix_[3][0] = -cam_->getMatrix()[3][0];
	matrix_[3][1] = -cam_->getMatrix()[3][1];
	matrix_[3][2] = -cam_->getMatrix()[3][2];
}


//unsigned int loadTexture(const char* filename)
//{
//
//	unsigned int num;
//	glGenTextures(1, &num);
//	SDL_Surface* img = SDL_loadBMP(filename);
//	glBindTexture(GL_TEXTURE_2D, num);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);
//	SDL_FreeSurface(img);
//	return num;
//
//
//}

void Skybox::loadSkybox()
{
		cubeBox = SOIL_load_OGL_cubemap
			(
			"../spaceShooter/texturePictures/skybox_east.jpg",			/*x-positive*/
			"../spaceShooter/texturePictures/skybox_west.jpg",			/*x-negative*/
			"../spaceShooter/texturePictures/skybox_up.jpg",			/*y-positive*/
			"../spaceShooter/texturePictures/skybox_down.jpg",			/*y-negative*/
			"../spaceShooter/texturePictures/skybox_north.jpg",		/*z-positive*/
			"../spaceShooter/texturePictures/skybox_south.jpg",	    /*z-negative*/
			SOIL_LOAD_RGB,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS
			);

	// check for an error during the load process 
	if (0 == cubeBox)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}
}