#pragma once
#include <GL/glew.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "SceneObject.hpp"

class Bullet : public SceneObject
{
public:
    Bullet(int mode, glm::mat4 spaceShipMatrix, int type);
    ~Bullet();

    void SetPosition(glm::vec3 pos);
    float Radius();
    glm::vec3 TranslateVec();
    void SetDirection(glm::vec3 dir);



protected:
    void privateInit();
    void privateRender();
    void privateUpdate();

private:
    int list_id;

    glm::vec3 translateVec_;
    float radius_;
    glm::vec3 direction_;

	int mode_;
	float speed_;


};
