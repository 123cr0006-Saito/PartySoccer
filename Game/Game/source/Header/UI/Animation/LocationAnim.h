#pragma once
#include <string>

#include "AnimationBase.h"
class LocationAnim : public AnimationBase
{
public:
	LocationAnim(class UIRotaBase* ui,const std::string& name);
	virtual ~LocationAnim();
	void Load(const std::string& path)override;
	void Update()override;

	void ChangeX(float, float, int, int);
	void ChangeY(float, float, int, int);
	void ChangeAngle(float, float, int, int);
	void ChangeAlpha(float, float, int, int);
	void ChangeExtrateX(float, float, int, int);
	void ChangeExtrateY(float, float, int, int);
protected:
	std::vector<std::pair<void (LocationAnim::*)(float, float, int, int), std::tuple<float, float, int, int>>> _changeValueList;
};

