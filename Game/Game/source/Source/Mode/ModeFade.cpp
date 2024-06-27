//----------------------------------------------------------------------
// @filename ModeFade.cpp
// @author: saito ko
// @explanation
// �X�e�[�W�J�ڎ��Ƀt�F�[�h�C���A�t�F�[�h�A�E�g���s�����߂̃N���X
//----------------------------------------------------------------------
#include "../../Header/Mode/ModeFade.h"
#include "../AppFrame/source/Mode/ModeServer.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/UIManager.h"
#include "../../Header/UI/UIFade.h"
#include "../AppFrame/MemoryLeak.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param time �t�F�[�h����
// @param isFadeIn �t�F�[�h�C�����t�F�[�h�A�E�g��
//----------------------------------------------------------------------
ModeFade::ModeFade(int time,bool isFadeIn) {
	_currentTime = GetNowCount();
	_fadeTime = time;
	_isFadeIn = isFadeIn;
	_ui = NEW UIFade(GetColor(0,0,0));
	// �T�[�o�[�ɒǉ�
	UIManager* uiManager = dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"));
	uiManager->Add(_ui);
	if (isFadeIn) {
		_alphaFade = 255;
	}
	else {
		_alphaFade = 0;
	}
};

ModeFade::~ModeFade() {
	SuperManager::GetInstance()->GetManager("uiManager")->DeleteName("Fade");;
}
//----------------------------------------------------------------------
// @brief ������
// @return �������Ă��邩
//----------------------------------------------------------------------
bool ModeFade::Initialize() {
	if (!base::Initialize()) { return false; }
	return true;
};
//----------------------------------------------------------------------
// @brief �I������
// @return �������Ă��邩
//----------------------------------------------------------------------
bool ModeFade::Terminate() {
	base::Terminate();
	return true;
};
//----------------------------------------------------------------------
// @brief �X�V����
// @return �������Ă��邩
//----------------------------------------------------------------------
bool ModeFade::Process() {
	base::Process();
	if (_isFadeIn) {
	    // FadeIn
		_alphaFade = Easing::Linear(GetNowCount() - _currentTime,255,0,_fadeTime);
	}
	else {
		// FadeOut
		_alphaFade = Easing::Linear(GetNowCount() - _currentTime, 0, 255, _fadeTime);
	}

	_ui->SetAlpha(_alphaFade);
	// ���Ԍo�߂ō폜
	if (GetNowCount() - _currentTime > _fadeTime) {
		ModeServer::GetInstance()->Del(this);
	}

	return true;
};
//----------------------------------------------------------------------
// @brief �`�揈��
// @return �������Ă��邩
//----------------------------------------------------------------------
bool ModeFade::Render() {
	return true;
};