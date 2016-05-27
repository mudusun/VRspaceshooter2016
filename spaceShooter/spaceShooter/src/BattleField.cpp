#include "BattleField.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>


BattleField::BattleField(glm::vec3 startPos, glm::vec3 step, int id)
{
	gridX_=32;
	gridZ_=512;

	pos_ = startPos;
	step_ = step;
	mode_ = id;
}

BattleField::~BattleField()
{
}

void BattleField::privateInit()
{
	matrix_ = glm::translate(matrix_, getPos());

	
	// Create vertex arrays
	glm::vec3 v;
	glm::vec2 t;
	for (int z = 0; z < gridZ_; z++)
	{
		for (int x = 0; x < gridX_; x++)
		{
			v[0] = float(x)*10.0f - ((gridX_ / 2.0f) * 10);     // 定义landscape的点的坐标， v[0]是x点坐标，公式用于把landscape放在中间位置
			v[1] = 5.0f;                                    //v[1]是y点坐标， 一直不变
			v[2] = float(z)*(-10.0f);                        //v[2]是z点坐标，是让landscape一直向后延伸
			vertexArray_.push_back(v);

			t[0] = float(x) / float(gridX_);              // texture 的坐标
			t[1] = float(z) / float(gridZ_);
			coordArray_.push_back(t);
			
		}
	}


	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(MAXINT);

	for (int i = 0; i < vertexArray_.size() - gridX_; i++)
	{
		
		indexArray_.push_back(i + gridX_);
		indexArray_.push_back(i);
		
		if ((i + 1) % (gridX_) == 0)
		{
			indexArray_.push_back(MAXINT);
		}

	}

	glDisable(GL_PRIMITIVE_RESTART);

	
	bShader_.initShaders("shaders/Texture");
	
	bShader_.enable();
	GLint color;
	color = glGetUniformLocation(bShader_.getProg(), "color");
	glUniform1i(color, 0);

	GLint light;
	light = glGetUniformLocation(bShader_.getProg(), "light");
	glUniform1i(light, 1);

	GLint height;
	height = glGetUniformLocation(bShader_.getProg(), "height");
	glUniform1i(height, 2);

	
	if (mode_ == 1) 
	{
		loadColorMap1();
		loadLightMap1();
		loadHeightMap1();
	
		
	}
	else if (mode_ == 2) 
	{
		loadColorMap2();
		loadLightMap2();
		loadHeightMap2();
	}

	bShader_.disable();	
	
}

void BattleField::privateRender()
{
	bShader_.enable();
	glDisable(GL_CULL_FACE);
	if (mode_ == 1)
	{
		field1();
	}
	else if (mode_ == 2)
	{
		field2();
	}

	glEnable(GL_CULL_FACE);
	bShader_.disable();

}

void BattleField::privateUpdate()
{
	pos_ += step_;

	if (pos_.z < gridZ_*10.0f)
	{
		matrix_ = glm::translate(matrix_, getStep());
	}
	else
	{
		pos_.z = -gridZ_*10.0f;
		matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -gridZ_*20.0f));
	}

}

glm::vec3 BattleField::getStep()
{
	return step_;
}
glm::vec3 BattleField::getPos()
{
	return pos_;
}

void BattleField::field1()
{
	// Render the battlefield
	bShader_.enable();
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_PRIMITIVE_RESTART);

	// activate fog
	glEnable(GL_FOG);
	// specify the equation to be used
	glFogi(GL_FOG_MODE, GL_LINEAR);
	// specify parameters
	glFogf(GL_FOG_START, 100.0f);
	glFogf(GL_FOG_END, 800.0f);
	// per-pixel fog calculations
	glHint(GL_FOG_HINT, GL_NICEST);


	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_2d[0]);        // Activate texture object tex_2d
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_2d[1]);
	glActiveTexture(GL_TEXTURE2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_2d[2]);

	//GLenum err = glGetError();
	//if (err != GL_NO_ERROR)
	//	std::cout << "OpenGL error: " << gluErrorString(err) << std::endl;
	//std::cout.flush();

	glEnableClientState(GL_VERTEX_ARRAY);        // enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); // enable texture arrays
												 //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);   // set vertex pointer
	glTexCoordPointer(2, GL_FLOAT, 0, &coordArray_[0]);
	glDrawElements(GL_TRIANGLE_STRIP, indexArray_.size(), GL_UNSIGNED_INT, &indexArray_[0]);
	glDisableClientState(GL_VERTEX_ARRAY);       // disable vertex arrays
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glActiveTexture(GL_TEXTURE2);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);


	glDisable(GL_PRIMITIVE_RESTART);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	bShader_.disable();
}

void BattleField::field2()
{
	// Render the battlefield
	bShader_.enable();
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_PRIMITIVE_RESTART);

	// activate fog
	glEnable(GL_FOG);
	// specify the equation to be used
	glFogi(GL_FOG_MODE, GL_LINEAR);
	// specify parameters
	glFogf(GL_FOG_START, 100.0f);
	glFogf(GL_FOG_END, 800.0f);
	// per-pixel fog calculations
	glHint(GL_FOG_HINT, GL_NICEST);


	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_2d_2[0]);        // Activate texture object tex_2d_2
	
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_2d_2[1]);
	glActiveTexture(GL_TEXTURE2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_2d_2[2]);

	//GLenum err = glGetError();
	//if (err != GL_NO_ERROR)
	//	std::cout << "OpenGL error: " << gluErrorString(err) << std::endl;
	//std::cout.flush();

	glEnableClientState(GL_VERTEX_ARRAY);        // enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); // enable texture arrays
												 //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);   // set vertex pointer
	glTexCoordPointer(2, GL_FLOAT, 0, &coordArray_[0]);
	glDrawElements(GL_TRIANGLE_STRIP, indexArray_.size(), GL_UNSIGNED_INT, &indexArray_[0]);
	glDisableClientState(GL_VERTEX_ARRAY);       // disable vertex arrays
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glActiveTexture(GL_TEXTURE2);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);


	glDisable(GL_PRIMITIVE_RESTART);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	bShader_.disable();
}

void BattleField::loadColorMap1()
{
	/* load an image file directly as a new OpenGL texture */
	tex_2d[0] = SOIL_load_OGL_texture
		(
			"../spaceShooter/texturePictures/colorMap2012.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
	/* check for an error during the load process */
	if (0 == tex_2d[0])
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	glBindTexture(GL_TEXTURE_2D, tex_2d[0]);        // Activate texture object
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}

void BattleField::loadColorMap2()
{
	/* load an image file directly as a new OpenGL texture */
	tex_2d_2[0] = SOIL_load_OGL_texture
		(
			"../spaceShooter/texturePictures/colorMap2012_2.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
	/* check for an error during the load process */
	if (0 == tex_2d_2[0])
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	glBindTexture(GL_TEXTURE_2D, tex_2d_2[0]);        // Activate texture object
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}

void BattleField::loadLightMap1()
{
	//2nd picture
	tex_2d[1] = SOIL_load_OGL_texture
		(
			"../spaceShooter/texturePictures/lightMap2012.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);

	/* check for an error during the load process */
	if (0 == tex_2d[1])
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	glBindTexture(GL_TEXTURE_2D, tex_2d[1]);        // Activate texture object
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}

void BattleField::loadLightMap2()
{
	//2nd picture
	tex_2d_2[1] = SOIL_load_OGL_texture
		(
			"../spaceShooter/texturePictures/lightMap2012_2.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);

	/* check for an error during the load process */
	if (0 == tex_2d_2[1])
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	glBindTexture(GL_TEXTURE_2D, tex_2d_2[1]);        // Activate texture object
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}

void BattleField::loadHeightMap1()
{
	/* load an image file directly as a new OpenGL texture */
	tex_2d[2] = SOIL_load_OGL_texture
		(
			"../spaceShooter/texturePictures/heightMap2012.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
	/* check for an error during the load process */
	if (0 == tex_2d[2])
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	glBindTexture(GL_TEXTURE_2D, tex_2d[2]);        // Activate texture object
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);


}

void BattleField::loadHeightMap2()
{
	/* load an image file directly as a new OpenGL texture */
	tex_2d_2[2] = SOIL_load_OGL_texture
		(
			"../spaceShooter/texturePictures/heightMap2012_2.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
	/* check for an error during the load process */
	if (0 == tex_2d_2[2])
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

	glBindTexture(GL_TEXTURE_2D, tex_2d_2[2]);        // Activate texture object
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);


}



