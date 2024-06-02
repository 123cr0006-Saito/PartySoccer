#pragma once
#include "appframe.h"
#include "../Manager/SuperManager.h"
#include "../Manager/RenderManager.h"
class ApplicationMain : public ApplicationBase
{
	typedef ApplicationBase base;
public:
	virtual bool Initialize(HINSTANCE hInstance);
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Process();
	virtual bool Render();

	virtual bool AppWindowed() { return true; }

protected:
	Fps* _fpsController;
	SuperManager* _superManager;
	RenderManager* _renderManager;
}; 
