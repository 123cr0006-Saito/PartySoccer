//----------------------------------------------------------------------
// @filename SuperManager.cpp
// @author: saito ko
// @explanation
// �}�l�[�W���[�N���X���Ǘ�����N���X
//----------------------------------------------------------------------
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/ManagerBase.h"
#include "../AppFrame/source/Application/UtilMacro.h"
//----------------------------------------------------------------------
SuperManager* SuperManager::_instance = nullptr;
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
SuperManager::SuperManager() {
	if (_instance != nullptr) {
		DebugError();
		return;
	}
	_instance = this;
	_isSort = false;
	_isProcessSkip = false;
};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
SuperManager::~SuperManager() {
	DelAll();
	_instance = nullptr;
};
//----------------------------------------------------------------------
// @brief �C���X�^���X�̒ǉ�
// @param �ǉ�����C���X�^���X�̖��O
// @param layer�ԍ�
// @param �ǉ�����C���X�^���X
// @return ����
//----------------------------------------------------------------------
bool SuperManager::Add(std::string name,int layer, ManagerBase* manager){
	_superManager.emplace_back(std::make_tuple(name,layer,manager));
	_isSort = true;
	return true;
};
//----------------------------------------------------------------------
// @brief �폜����C���X�^���X�̖��O��}��
// @param �폜�������C���X�^���X�̖��O
// @return ����
//----------------------------------------------------------------------
bool SuperManager::DeleteName(std::string name){
	_delSuperManager.emplace_back(name);
	return true;
};
//----------------------------------------------------------------------
// @brief �i�[���Ă���C���X�^���X�����ׂč폜
// @return ����
//----------------------------------------------------------------------
bool SuperManager::DelAll(){
	for (auto&& list : _superManager) {
		std::get<2>(list)->Terminate();
	}
	for (auto&& list : _superManager) {
		delete std::get<2>(list);
	}
	_superManager.clear();
	return true;
};
//----------------------------------------------------------------------
// @brief �i�[���Ă���C���X�^���X�𖼑O�Ō������擾
// @param �C���X�^���X�̖��O
// @return �擾�����C���X�^���X�@�擾�ł��Ȃ������ꍇ�Anullptr
//----------------------------------------------------------------------
ManagerBase* SuperManager::GetManager(std::string name){
	for (auto&& list : _superManager) {
		if (std::get<0>(list) == name) {
			return std::get<2>(list);
		}
	}
	return nullptr;
};
//----------------------------------------------------------------------
// @brief ���C���[�ԍ����Q�Ƃ����Ԃ����ւ���
// @return ����
//----------------------------------------------------------------------
void SuperManager::Sort(){
	std::sort(_superManager.begin(), _superManager.end(), [](const std::tuple<std::string, int, ManagerBase*>& a, const std::tuple<std::string, int, ManagerBase*>& b) {
		return std::get<1>(a) < std::get<1>(b);
	});
};
//----------------------------------------------------------------------
// @brief �X�V����
// @return �����������ǂ���
//----------------------------------------------------------------------
bool SuperManager::Update() {

	for (auto&& list : _delSuperManager) {
		for (auto itr = _superManager.begin(); itr != _superManager.end(); ++itr) {
			if (std::get<0>((*itr)) == list) {
				std::get<2>((*itr))->Terminate();
				delete std::get<2>((*itr));
				_superManager.erase(itr);
				break;
			}
		}
	}

	_delSuperManager.clear();
	_isProcessSkip = false;
	if (_isSort) {
		Sort();
		_isSort = false;
	}

	for(auto itr = _superManager.rbegin() ; itr != _superManager.rend(); ++itr){
		std::get<2>((*itr))->UpdateInit();
		if(!_isProcessSkip){
			//�X�L�b�v���I������Ă����珈�����X�L�b�v
			std::get<2>((*itr))->Update();
		}
		std::get<2>((*itr))->UpdateEnd();
	}
	
	return true;
};
//----------------------------------------------------------------------
// @brief �`�揈��
// @return �����������ǂ���
//----------------------------------------------------------------------
bool SuperManager::Draw() {
	for (auto&& list : _superManager) {
		std::get<2>(list)->Draw();
	}
	return true;
};
