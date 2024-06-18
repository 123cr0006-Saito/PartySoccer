//----------------------------------------------------------------------
// @filename ModeFadeComeBack.cpp
// @date: 2024/03/02
// @author: saito ko
// @explanation
// �X�e�[�W�J�ڎ��Ƀt�F�[�h�C���A�t�F�[�h�A�E�g���s�����߂̃N���X
// ModeFade�ƈႤ�_�͏�Ƀt�F�[�h�C�����Ă���t�F�[�h�A�E�g���A
// �w��̃��[�h���폜���Ȃ���J�ڂ���
//----------------------------------------------------------------------
#include "../../Header/Mode/ModeFadeComeBack.h"
#include "../AppFrame/source/Mode/ModeServer.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param Time �t�F�[�h����
// @param modeName ���C���[��ύX���郂�[�h��
// @param layer �w�肵�����[�h�̃��C���[�����̒l�ɕύX
// @param IsProcessSkip �t�F�[�h���v���Z�X���X�L�b�v���邩�ǂ���
//----------------------------------------------------------------------
ModeFadeComeBack::ModeFadeComeBack(int Time, std::string modeName, int layer, bool IsProcessSkip) :ModeFade(Time, false) {
	_fadeEnd = 255;
	_fadeStart = 0;
	_deleteModeName.clear();
	_changeLayer = layer;
	_changeModeName = modeName;
	_IsProcessSkip = IsProcessSkip;
};
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param Time �t�F�[�h����
// @param mode �폜���郂�[�h��
// @param IsProcessSkip �t�F�[�h���v���Z�X���X�L�b�v���邩�ǂ���
//----------------------------------------------------------------------
ModeFadeComeBack::ModeFadeComeBack(int Time, std::vector<std::string> mode, bool IsProcessSkip) :ModeFade(Time,false){
	_fadeEnd = 255;
    _fadeStart = 0;
	_deleteModeName = mode;
	_changeLayer = 0;
	_changeModeName = "";
	_IsProcessSkip = IsProcessSkip;
};
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param Time �t�F�[�h����
// @param mode �폜���郂�[�h��
// // @param modeName ���C���[��ύX���郂�[�h��
// @param layer �w�肵�����[�h�̃��C���[�����̒l�ɕύX
// @param IsProcessSkip �t�F�[�h���v���Z�X���X�L�b�v���邩�ǂ���
//----------------------------------------------------------------------
ModeFadeComeBack::ModeFadeComeBack(int Time, std::vector<std::string> mode, std::string modeName, int layer, bool IsProcessSkip) :ModeFade(Time, false) {
	_fadeEnd = 255;
	_fadeStart = 0;
	_deleteModeName = mode;
	_changeLayer = layer;
	_changeModeName = modeName;
	_IsProcessSkip = IsProcessSkip;
};

ModeFadeComeBack::~ModeFadeComeBack(){
	_deleteModeName.clear();
};
//----------------------------------------------------------------------
// @brief ������
// @return �������Ă��邩
//----------------------------------------------------------------------
bool ModeFadeComeBack::Initialize(){
	if (!base::Initialize()) { return false; }
	return true;
};
//----------------------------------------------------------------------
// @brief �I������
// @return �������Ă��邩
//----------------------------------------------------------------------
bool ModeFadeComeBack::Terminate(){
	base::Terminate();
	return true;
};
//----------------------------------------------------------------------
// @brief �X�V����
// @return �������Ă��邩
//----------------------------------------------------------------------
bool ModeFadeComeBack::Process(){
	// �v���Z�X���X�L�b�v����ꍇ
	if(_IsProcessSkip){
	   ModeServer::GetInstance()->SkipProcessUnderLayer();
	}
	ModeServer::GetInstance()->PauseProcessUnderLayer();
	int nowTime = GetNowCount() - _currentTime;
	// �t�F�[�h����
	(*_alphaFade) = Easing::Linear(nowTime, _fadeStart, _fadeEnd, _fadeTime);
	// �t�F�[�h�I��
	if ((*_alphaFade) >= 255) {
		// �l�̓���ւ�
		(*_alphaFade) = _fadeEnd;

		int temp = _fadeStart;
        _fadeStart = _fadeEnd;
        _fadeEnd = temp;
		_currentTime = GetNowCount();

		// �폜���郂�[�h������Ƃ�
		if(!_deleteModeName.empty()){
			for (auto mode : _deleteModeName) {
				ModeServer::GetInstance()->Del(mode.c_str());
			}
	    }
		// ���C���[��ύX����ꍇ
		if(_changeModeName != ""){
			ModeServer::GetInstance()->ChangeLayer(_changeModeName, _changeLayer);
		}
	}
	else if ((*_alphaFade) < 0) {
		// �t�F�[�h�I�� �폜
		ModeServer::GetInstance()->Del(this);
	}

	return true;
};
//----------------------------------------------------------------------
// @brief �`�揈��
// @return �������Ă��邩
//----------------------------------------------------------------------
bool ModeFadeComeBack::Render() {
	return true;
};