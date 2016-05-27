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

class BattleField : public SceneObject
{
	public:
		BattleField(glm::vec3 startPos, glm::vec3 step, int id);
		~BattleField();

  protected:
   
		glm::vec3 getStep();
		glm::vec3 getPos();
		void field1();
		void field2();
		void loadColorMap1();
		void loadColorMap2();
		void loadHeightMap1();
		void loadHeightMap2();
		void loadLightMap1();
		void loadLightMap2();

	private:
		virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();
		GLuint texture;
        std::vector< glm::vec3 > vertexArray_; // Maybe two-dim vector and several arrays
        std::vector<unsigned int> indexArray_; // normal array.
        std::vector< glm::vec2 > coordArray_; // texture coord array
	    int gridX_;
	    int gridZ_;
	    int mode_;
		

	    GLuint tex_2d[2];
		GLuint tex_2d_2[2];
		GLuint colorMap, heightMap, lightMap;

		glm::vec3 pos_, step_;
		Shader bShader_;
};

