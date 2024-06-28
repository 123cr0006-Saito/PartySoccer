//----------------------------------------------------------------------
// @filename PlayerManager.cpp
// @author: saito ko
// @explanation
// �v���C���[���Ǘ�����N���X
//----------------------------------------------------------------------
#include "../../Header/Manager/PlayerManager.h"
#include "../../Header/Object/Player/Player.h"
#include "../AppFrame/source/System/Header/Input/XInput.h"
#include "../AppFrame/source/Application/UtilMacro.h"
#include "../AppFrame/source/CFile/CFile.h"
#include "../../Header/UI/UIPlayerParam.h"
#include "../AppFrame/source/System/Header/Input/XInput.h"
#include "../MemoryLeak.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
PlayerManager::PlayerManager() {
	
};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
PlayerManager::~PlayerManager(){
	_player.clear();
	_originPos.clear();
};
//----------------------------------------------------------------------
// @brief �I������
// @return �������Ă��邩
//----------------------------------------------------------------------
bool PlayerManager::Terminate(){
	DelAll();
	return true;
};
//----------------------------------------------------------------------
// @brief �X�V����
// @return �����������ǂ���
//----------------------------------------------------------------------
bool PlayerManager::Update(){
	for (auto&& list : _player) {
		list->Update();
	}
	return true;
};
//----------------------------------------------------------------------
// @brief �X�V�I����ɍs������
// @return �����������ǂ���
//----------------------------------------------------------------------
bool PlayerManager::UpdateEnd(){
	for (auto&& list : _player) {
		list->UpdateEnd();
	}
	return true;
};
//----------------------------------------------------------------------
// @brief �v���C���[�̒ǉ��@����ɍ��킹�ăv���C���[�L�����ɑΉ�����UI��ǉ�
// @param �v���C���[�̖��O
// @param �p�b�h�̓���
// @param �v���C���[�̃��f���n���h��
// @return ����
//----------------------------------------------------------------------
void PlayerManager::Add(const std::vector<std::tuple<std::string, class XInput*, int>>& param) {

	float uiX = 1920.0f / (param.size() + 1);
	for (int i = 0; i < param.size(); i++) {
		_player.emplace_back(NEW Player(std::get<0>(param[i]), std::get<1>(param[i]), std::get<2>(param[i])));
		UIPlayerParam* ui = NEW UIPlayerParam(_player[i], std::get<0>(param[i]), Vector3D(uiX * (i + 1), 900, 0));
	}
	InitParam();
};
//----------------------------------------------------------------------
// @brief �i�[���Ă���C���X�^���X�����ׂč폜
// @return ����
//----------------------------------------------------------------------
void PlayerManager::DelAll(){
	for (auto&& list : _player) {
		delete list;
	}
	_player.clear();
	_originPos.clear();
};
//----------------------------------------------------------------------
// @brief �v���C���[�̈ʒu�@�X�^�~�i�@�V���[�g�͂�������
// @return ����
//----------------------------------------------------------------------
void PlayerManager::InitParam(){
	for(int i = 0; i < _player.size(); i++){
		_player[i]->SetPos(Vector3D(1500.0f * pow(-1, i+1), 0,i / 2 * 2000.0f));
		_player[i]->SetStamina(100);
		_player[i]->SetPower(0);
	}
};
//----------------------------------------------------------------------
// @brief �`�揈��
// @return �����������ǂ���
//----------------------------------------------------------------------
bool PlayerManager::Draw(){
#ifdef _DEBUG
	for(auto&& list : _player){
		list->DebugDraw();
	}
#endif
	return true;
}