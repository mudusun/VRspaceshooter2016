#include "Water.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>


Water::Water(glm::vec3 startPos, glm::vec3 step, int id) 
{
	waterX_ = 128;
	waterZ_ = 512;

	pos_ = startPos;
	step_ = step;
	mode_ = id;

	waveTime = 0.5;
	waveWidth = 0.6;
	waveHeight = 1.0;
	waveFreq = 0.1;

}

Water::~Water() 
{
}

void Water::privateInit() 
{

	matrix_ = glm::translate(matrix_, getPos());
	
	// Create vertex arrays
	glm::vec3 v;
	glm::vec2 t;
	for (int z = 0; z < waterZ_; z++)
	{
		for (int x = 0; x < waterX_; x++)
		{
			v[0] = float(x)*10.0f - ((waterX_ / 2.0f) * 10);     // 定义landscape的点的坐标， v[0]是x点坐标，公式用于把landscape放在中间位置
			v[1] = -100.0f;                                    //v[1]是y点坐标， 一直不变
			v[2] = float(z)*(-10.0f);                        //v[2]是z点坐标，是让landscape一直向后延伸
			vertexArray_.push_back(v);

			t[0] = float(x) / float(waterX_);              // texture 的坐标
			t[1] = float(z) / float(waterZ_);
			texCoordArray_.push_back(t);

		}
	}


	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(MAXINT);

	for (int i = 0; i < vertexArray_.size() - waterX_; i++)
	{

		indexArray_.push_back(i + waterX_);
		indexArray_.push_back(i);

		if ((i + 1) % (waterX_) == 0)
		{
			indexArray_.push_back(MAXINT);
		}

	}

	glDisable(GL_PRIMITIVE_RESTART);

	shader_.initShaders("shaders/water");
	shader_.enable();

	

	glUniform3f(glGetUniformLocation(shader_.getProg(), "objColor"), 0.0, 0.0, 1.0);
	glUniform1f(glGetUniformLocation(shader_.getProg(), "waveTime"), waveTime);
	glUniform1f(glGetUniformLocation(shader_.getProg(), "waveWidth"), waveWidth);
	glUniform1f(glGetUniformLocation(shader_.getProg(), "waveHeight"), waveHeight);

	shader_.disable();
}

void Water::privateRender() 
{

	shader_.enable();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glDisable(GL_CULL_FACE);

	if (mode_ == 1)
	{
		field();
	}
	else if (mode_ == 2)
	{
		field();
	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	shader_.disable();
}

void Water::privateUpdate() 
{
	shader_.enable();
	waveTime += waveFreq;
	glUniform1f(glGetUniformLocation(shader_.getProg(), "waveTime"), waveTime);

	pos_ += step_;
	if (pos_.z < waterZ_*10.0f) 
	{
		matrix_ = glm::translate(matrix_, getStep());
		
	}
	else 
	{
		pos_.z = -waterZ_*10.0f;
		matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -waterZ_*20.0f));
	}

	shader_.disable();
}

glm::vec3 Water::getStep() 
{
	return step_;
}
glm::vec3 Water::getPos() 
{
	return pos_;
}



void Water::field() 
{
	shader_.enable();
	glEnable(GL_PRIMITIVE_RESTART);

	glEnableClientState(GL_VERTEX_ARRAY);										// enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);								// enable texture coord arrays
	glVertexPointer(3, GL_FLOAT, 0, &vertexArray_[0]);							// set vertex pointer
	glTexCoordPointer(2, GL_FLOAT, 0, &texCoordArray_[0]);						// set texture coord pointer
	glDrawElements(GL_QUAD_STRIP, indexArray_.size(), GL_UNSIGNED_INT, &indexArray_[0]);	// draw quads
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);								// disable texture coord arrays
	glDisableClientState(GL_VERTEX_ARRAY);										// disable vertex arrays

	glDisable(GL_PRIMITIVE_RESTART);
	shader_.disable();
}