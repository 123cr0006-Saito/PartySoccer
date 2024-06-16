#include "../../Header/Other/Score.h"
#include "../AppFrame/source/Application/UtilMacro.h"
Score* Score::_instance = nullptr;
Score::Score(){
	if(_instance != nullptr){
		DebugErrar();
		return ;
	}
	_instance = this;
	_score["goal_1"] = 0;
	_score["goal_2"] = 0;
};

Score::~Score(){
	_score.clear();
};