#pragma once

#include <GL/glew.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Bullet.hpp"
#include "Input.hpp"
#include "SceneObject.hpp"
#include "Shader.hpp"
#include "glm/glm.hpp"
#include "ParticleGenerator.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

class SpaceShip : public SceneObject
{
	public:
		SpaceShip();
		~SpaceShip();

		void moveRight();
		void moveLeft();
		void moveUp();
		void moveDown();

		float Radius();
		glm::vec3 TranslateVec();

		void die(float life);
		float getLife();
		void setLife(float l);

		int getScores();
		void addScores(int score);
	    

  protected:
        void privateInit();
		void privateRender();
		void privateUpdate();

	private:
		GLuint texture;
	    float speed_;
        float life_;
        float armor_;
	    int scores_;
	    glm::vec3 translateVec_;
	    float radius_;
	    int list_id;

		Shader shaderActive_;

		GLuint particle;
		std::shared_ptr<ParticleGenerator> particleImg_;

		std::vector<glm::vec3> vertexArray_;
		std::vector<glm::vec3> normalArray_;
		std::vector<unsigned int> indexArray_;

		
		float shieldRegen_;
		float getShieldRegen() const;

		float shieldRegenTimer_;
};

