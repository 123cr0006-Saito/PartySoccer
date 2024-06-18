#pragma once
#include <string>

class Animation
{
public:
	Animation(class UIRotaBase* ,std::string);
	~Animation();
	void Load(std::string);
	bool Update();
protected:
	int _currentTime;
	int _endTime;
	int _delayTime;
	bool _isEnd;
	class UIRotaBase* _ui;
	class UIRotaParam _startParam;
	class UIRotaParam _endParam;
};

