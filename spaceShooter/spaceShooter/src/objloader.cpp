#include "objloader.hpp"


Objloader::Objloader()
{
	
	loadEnemyModel();
	loadBossModel();
	
}

Objloader::~Objloader()
{
	
	delete enemyModel_;
	delete bossModel_;
	
}


void Objloader::loadEnemyModel()
{
	enemyModel_ = new Model();
	enemyModel_->loadModel("obj/enemy.obj");
	enemyModel_->setTexture("obj/enemy.png");
	
}

void Objloader::loadBossModel()
{
	bossModel_ = new Model();
	bossModel_->loadModel("obj/enemy1.obj");
	bossModel_->setTexture("obj/enemy1.png");
}



Model *Objloader::getEnemyModel()
{
	return enemyModel_;
}


Model *Objloader::getBossModel()
{
	return bossModel_;
}

