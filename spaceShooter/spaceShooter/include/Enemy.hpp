#pragma once

#include <GL/glew.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "Shader.hpp"
#include "Model.hpp"

class Enemy : public SceneObject
{
	public:
		Enemy(float life, Model* model, int mode, float posX);
		~Enemy();
		float Radius() const;
		glm::vec3 TranslateVec() const;

		void die(float life);
		float getLife();
		void setLife(float l);
		int getSize() 
		{
			return size_;
		}

  protected:
        void privateInit();
		void privateRender();
		void privateUpdate();
		int list_id;
		int size_;

	private:
	  float speed_;
      float life_;
      float armor_;

	  float radius_;
	  int random_;
	  int rand2_;
	  float x_;
	  Model*      model_;
	  glm::vec3 translateVec_;
	  int mode_;
	  Shader eShader_;
};

