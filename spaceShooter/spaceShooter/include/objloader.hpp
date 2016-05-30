#pragma once


#include "Model.hpp"

class Objloader
{
public:
	Objloader();
	~Objloader();

	
	Model* getEnemyModel();
	Model* getBossModel();
	

private:
	
	void loadEnemyModel();
	void loadBossModel();
	

	
	Model* enemyModel_;
	Model* bossModel_;
};


