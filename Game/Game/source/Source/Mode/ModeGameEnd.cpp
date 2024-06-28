//----------------------------------------------------------------------
// @filename ModeGameEnd.cpp
// @author: saito ko
// @explanation
// �Q�[���I�����̉��o���s���N���X
//----------------------------------------------------------------------
#include "../../Header/Mode/ModeGameEnd.h"
#include "../../Header/UI/UIGameEnd.h"
#include "../AppFrame/source/Mode/ModeServer.h"
#include "../AppFrame/source/System/Header/Function/Easing.h"
#include "../../Header/Mode/ModeFadeComeBack.h"
#include "../AppFrame/MemoryLeak.h"
#include "../../Header/Mode/ModeResult.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/UIManager.h"
#include "../../Header/UI/Animation/LocationAnim.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
ModeGameEnd::ModeGameEnd(){

};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
ModeGameEnd::~ModeGameEnd(){

};
//----------------------------------------------------------------------
// @brief ����������
// @return �������Ă��邩
//----------------------------------------------------------------------
bool ModeGameEnd::Initialize(){
	_currentTime = GetNowCount();
	// �I��UI���쐬
	_ui = NEW UIGameEnd();
	LocationAnim* anim = new LocationAnim(_ui, "Data/UIAnimation/GameEndAnimation.csv");
	_ui->SetAnimation(anim);
	return true;
};
//----------------------------------------------------------------------
// @brief �I������
// @return �������Ă��邩
//----------------------------------------------------------------------
bool ModeGameEnd::Terminate(){
	// UI���폜
	SuperManager::GetInstance()->GetManager("uiManager")->DeleteName(_ui->GetName());
	return true;
};
//----------------------------------------------------------------------
// @brief �X�V����
// @return �����������ǂ���
//----------------------------------------------------------------------
bool ModeGameEnd::Process(){
	ModeServer::GetInstance()->SkipProcessUnderLayer();
	int nowTime = GetNowCount() - _currentTime;
	if(nowTime >2500 && !ModeServer::GetInstance()->Search("ModeFadeComeBack")) {
		std::vector<std::string> modeName = {"ModeGame","ModeGameEnd"};
		ModeServer::GetInstance()->Add(NEW ModeResult(), 0, "ModeResult");
		ModeServer::GetInstance()->Add(NEW 	ModeFadeComeBack(500, modeName, false), 100,"ModeFadeComeBack");
	}
	return true;
};
