#include "GameManager.hpp"
#include <iostream>
#include <exception>

GameManager::GameManager()
{
	counter_1 = 0;
	counter_2 = 0;
}

GameManager::~GameManager()
{
}

void GameManager::privateInit()
{
  // Set default OpenGL states
  glEnable(GL_CULL_FACE);

  // Adding the camera to the scene
  cam_.reset(new Camera());
 
  skybox_.reset(new Skybox(cam_));
  this->addSubObject(skybox_);

  bf1_.reset(new BattleField(glm::vec3(0.0f, 160.0f, 0.0f), glm::vec3(0.0f, 0.0f, 5.0f), 1));
  this->addSubObject(bf1_);

  bf2_.reset(new BattleField(glm::vec3(0.0f, 160.0f, -5120.0f),glm::vec3(0.0f, 0.0f, 5.0f), 2));
  this->addSubObject(bf2_);

  water1_.reset(new Water(glm::vec3(20.0f, -200.0f, 0.0f),glm::vec3(0.0f, 0.0f, 5.0f), 1));
  this->addSubObject(water1_);

  water2_.reset(new Water(glm::vec3(20.0f, -200.0f, -5120.0f),glm::vec3(0.0f, 0.0f, 5.0f), 2));
  this->addSubObject(water2_);

  spaceship_.reset(new SpaceShip());
  this->addSubObject(spaceship_);

  addEnemy();

  
  
  bitmap_.reset(new BitmapText());
  this->addSubObject(bitmap_);

  

  fpsCount_ = std::to_string(fps_);
}

void GameManager::privateRender()
{
	try
	{

		float life_;
		float enemysLife_;


		for (int i = 0; i < bulletsPlayer_.size(); i++)
			if (bulletsPlayer_[i]->TranslateVec()[2] < -1000)
			{
				this->removeSubObject(bulletsPlayer_[i]);
				bulletsPlayer_.erase(bulletsPlayer_.begin() + i);
			}

		for (int i = 0; i < bullets_.size(); i++)
			if (bullets_[i]->TranslateVec()[2] > 50)
			{
				this->removeSubObject(bullets_[i]);
				bullets_.erase(bullets_.begin() + i);
			}


	 //collision between enemies and spaceship
		for (int i = 0; i < enemies_.size(); i++)
			if (Collision(enemies_[i]->Radius(), spaceship_->Radius(), enemies_[i]->TranslateVec(), spaceship_->TranslateVec()))
			{
				this->removeSubObject(enemies_[i]);
				enemies_.erase(enemies_.begin() + i);

				spaceship_->setLife(0);
				this->removeSubObject(spaceship_);
			}

	 // //collision between bullets and spaceship
		for (int i = 0; i < bullets_.size(); i++)
			if (Collision(bullets_[i]->Radius(), spaceship_->Radius(), bullets_[i]->TranslateVec(), spaceship_->TranslateVec()))
			{
				this->removeSubObject(bullets_[i]);
				bullets_.erase(bullets_.begin() + i);

				spaceship_->die(10);
				life_ = spaceship_->getLife() - 10;
				spaceship_->setLife(life_);

				spaceship_->addScores(-50);


				if (spaceship_->getLife() <= 0) 
				{
					this->removeSubObject(spaceship_);
				}
			}

			////collision between enemies's bullet and enemies
		for (int i = 0; i < enemies_.size(); i++)
			for (int j = 0; j < bulletsPlayer_.size(); j++)
				if (Collision(bulletsPlayer_[j]->Radius(), enemies_[i]->Radius(), bulletsPlayer_[j]->TranslateVec(), enemies_[i]->TranslateVec()))
				{
					this->removeSubObject(bulletsPlayer_[j]);
					bulletsPlayer_.erase(bulletsPlayer_.begin() + i);
					enemies_[i]->die(2);
					enemysLife_ = enemies_[i]->getLife() - 2;
					enemies_[i]->setLife(enemysLife_);
					spaceship_->addScores(100);
					if (enemies_[i]->getLife() <= 0) 
					{
						this->removeSubObject(enemies_[i]);
						enemies_.erase(enemies_.begin() + i);
					}

				}

	}
	catch (int i )
	{}

	
	}

void GameManager::privateUpdate()
{
	// Instead of adding all objects in the scene as subobject to the camera they are added as subobjects
	// to the game manager. Therefore, we set the game manager matrix equal to the camera matrix. 
	this->matrix_ = cam_->getMatrix();

	counter_1++;
	if (counter_1 > 50)
	{
		counter_1 = 0;
		fpsCount_ = std::to_string(fps_);
	}
	bitmap_->drawBitmapText(fpsCount_.c_str(), glutGet(GLUT_WINDOW_HEIGHT) - 100, glutGet(GLUT_WINDOW_WIDTH) - 100);



	counter_2++;
	if (counter_2 > 60)
	{
		counter_2 = 0;
	}
	fpsCount_ = std::to_string(counter_2);
	bitmap_->drawBitmapText(fpsCount_.c_str(), glutGet(GLUT_WINDOW_HEIGHT) - 200, glutGet(GLUT_WINDOW_WIDTH) - 200);


}

std::shared_ptr<Camera> GameManager::getCam()
{
  return cam_;

}
std::shared_ptr<SpaceShip> GameManager::getShip()
{
	return spaceship_;
}

void GameManager::addEnemy()
{
	// Normal enemy
	for (int i = -4; i < -1; i++)
	{
		auto enemy = std::make_shared<Enemy>(100, loader_.getEnemyModel(), 0, float(i) * 40.f);
		this->addSubObject(enemy);

		enemies_.push_back(enemy);
		

		
	}
	
	// Sin enemy
	for (int i = -1; i < 1; i++)
	{
		auto enemy1 = std::make_shared<Enemy>(100, loader_.getBossModel(), 1, float(i) * 30.f);
		this->addSubObject(enemy1);

		enemies_.push_back(enemy1);
		

	}
	// Cos enemy
	for (int i = 1; i < 4; i++)
	{
		enemy_ = std::make_shared<Enemy>(100, loader_.getEnemyModel(), 2, float(i) * 40.f);
		this->addSubObject(enemy_);

		enemies_.push_back(enemy_);
		enemyFire_.push_back(enemy_);
		
	}
	addBullet();

}

void GameManager::addBullet()
{
	for (int i=0; i < enemies_.size(); i++) {
		std::shared_ptr<Bullet> bullet_;
		glm::vec3 dir(0, 0, 0.1);
		bullet_.reset(new Bullet(0, enemies_[i]->getMatrix(), 0));
		bullet_->SetPosition(enemies_[i]->TranslateVec());
		bullet_->SetDirection(dir);
		this->addSubObject(bullet_);
		bullets_.push_back(bullet_);
	}
}

void GameManager::addBulletPlayer()   //bullet from enemy
{
	std::shared_ptr<Bullet> bullet_;
	glm::vec3 dir(0, 0, -1);
	bullet_.reset(new Bullet(1, spaceship_->getMatrix(), 1));
	bullet_->SetPosition(spaceship_->TranslateVec());
	bullet_->SetDirection(dir);
	this->addSubObject(bullet_);
	bulletsPlayer_.push_back(bullet_);
}



bool GameManager::Collision(float radius_1, float radius_2, glm::vec3 translateVec1, glm::vec3 translateVec2)
{
	float d = glm::length(translateVec1 - translateVec2);
	if (d <= radius_1 + radius_2) return true;
	return false;
}
