//----------------------------------------------------------------------
// @filename ModeGame.cpp
// @date: 2023/12/14
// @author: saito ko
// @explanation
// �{�X�o�g���ȊO�̃X�e�[�W���Ǘ�����N���X
//----------------------------------------------------------------------
#include "../../Header/Mode/ModeGame.h"
//----------------------------------------------------------------------
// @brief ����������
// @return �������Ă��邩
//----------------------------------------------------------------------
bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }
	return true;
}
//----------------------------------------------------------------------
// @brief �폜����
// @return ����
//----------------------------------------------------------------------
bool ModeGame::Terminate() {
	base::Terminate();
	return true;
}
//----------------------------------------------------------------------
// @brief �X�V����
// @return �����������ǂ���
//----------------------------------------------------------------------
bool ModeGame::Process() {
	base::Process();
	ModeServer::GetInstance()->SkipProcessUnderLayer();
	ModeServer::GetInstance()->PauseProcessUnderLayer();
	return true;
}
//----------------------------------------------------------------------
// @brief �`�揈��
// @return �����������ǂ���
//----------------------------------------------------------------------
bool ModeGame::Render() {

	base::Render();
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);
	return true;
}
