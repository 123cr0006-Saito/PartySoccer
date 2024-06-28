//----------------------------------------------------------------------
// @filename Score.cpp
// @author: saito ko
// @explanation
// 点数を管理するクラス
//----------------------------------------------------------------------
#include "../../Header/Other/Score.h"
#include "../AppFrame/source/Application/UtilMacro.h"
Score* Score::_instance = nullptr;
//----------------------------------------------------------------------
// @brief コンストラクタ
// @return 無し
//----------------------------------------------------------------------
Score::Score(){
	if(_instance != nullptr){
		DebugError();
		return ;
	}
	_instance = this;
	_score["Goal_1"] = 0;
	_score["Goal_2"] = 0;
};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
Score::~Score(){
	_instance = nullptr;
	_score.clear();
};

