#pragma once

#include <GL/glew.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <memory>
#include <sstream>
#include <algorithm>
#include <GL/freeglut.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "SceneObject.hpp"
#include "BattleField.hpp"
#include "SpaceShip.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Camera.hpp"
#include "ParticleGenerator.h"
#include "BitmapText.hpp"
#include "Skybox.hpp"
#include "Water.hpp"
#include "objloader.hpp"

class GameManager : public SceneObject
{
	public:
		GameManager();
		~GameManager();
    
    std::shared_ptr<Camera> getCam();
	std::shared_ptr<SpaceShip> getShip();

	void addEnemy();
	void addBullet();
	void addBulletPlayer();
	bool GameManager::Collision(float radius_1, float radius_2, glm::vec3 translateVec1, glm::vec3 translateVec2);

  protected:
        virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();

	private:
    std::shared_ptr<BattleField> bf1_;
	std::shared_ptr<BattleField> bf2_;

    std::shared_ptr<SpaceShip> spaceship_;

	std::shared_ptr<Water> water1_;
	std::shared_ptr<Water> water2_;

	std::shared_ptr<Skybox> skybox_;
	std::shared_ptr<Camera> cam_;

	std::shared_ptr<Enemy> enemy_; 
	std::vector< std::shared_ptr<Enemy> > enemies_;
	std::vector< std::shared_ptr<Enemy> > enemyFire_;

	std::vector< std::shared_ptr<Bullet> > bullets_;
	std::vector< std::shared_ptr<Bullet> > bulletsPlayer_;

	std::shared_ptr<ParticleGenerator> explosion_;

	std::shared_ptr<ParticleGenerator> particle_;
	std::shared_ptr<BitmapText> bitmap_;
	float counter_1;
	float counter_2;
	std::string fpsCount_;

	Objloader loader_;

};

