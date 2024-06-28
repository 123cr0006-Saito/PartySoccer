//----------------------------------------------------------------------
// @filename Score.cpp
// @author: saito ko
// @explanation
// �_�����Ǘ�����N���X
//----------------------------------------------------------------------
#include "../../Header/Other/Score.h"
#include "../AppFrame/source/Application/UtilMacro.h"
Score* Score::_instance = nullptr;
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
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
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
Score::~Score(){
	_instance = nullptr;
	_score.clear();
};

