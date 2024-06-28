//----------------------------------------------------------------------
// @filename UIManager.cpp
// @author: saito ko
// @explanation
// �X�R�A�{�[�h��`�悷��UI�N���X
//----------------------------------------------------------------------
#include "../../../Header/UI/Score/UIScoreBoard.h"
#include "../../../Header/UI/Score/UIScore.h"
#include "../AppFrame/MemoryLeak.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../../Header/Manager/UIManager.h"
#include "dxlib.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param �ʒu
// @param ���O
// @param �X�R�A�N���X
// @return ����
//----------------------------------------------------------------------
UIScoreBoard::UIScoreBoard(const Vector3D& pos, const std::string& name, Score* score) :
	UIRotaBase()
{
	_handle = LoadGraph("Res/GoalAnimation/scoreBoard.png");
	_pos = pos;
	_layer = 10;
	_name = "scoreBoard";
	int sizeX, sizeY;
	GetGraphSize(_handle, &sizeX, &sizeY);
	_center = Vector3D(sizeX/2, sizeY/2, 0);
	_score = NEW UIScore(pos, name, score);
	SuperManager::GetInstance()->GetManager("uiManager")->Add(this);
};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
UIScoreBoard::~UIScoreBoard(){
	_score = nullptr;
};