#pragma once
#include "ManagerBase.h"
class RenderManager
{
	static RenderManager* _instance;
public :
	RenderManager();
	~RenderManager();
	bool Init();
	bool Update();
	bool Draw();
	static RenderManager* GetInstance() { return _instance; }
};

