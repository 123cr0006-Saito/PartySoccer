//----------------------------------------------------------------------
// @filename IterationAnim.cpp
// @author: saito ko
// @explanation
// sin�g���g����x��y���ړ�����A�j���[�V����
//----------------------------------------------------------------------
#include "../../../Header/UI/Animation/IterationAnim.h"
#include "../AppFrame/source/CFile/CFile.h"
#include "../AppFrame/source/Application/UtilMacro.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param UI�̃C���X�^���X
// @param �t�@�C���p�X
// @param �J�n�l�������_���ɂ��邩�ǂ���
// @return ����
//----------------------------------------------------------------------
IterationAnim::IterationAnim(UIRotaBase* ui,std::string filePath,bool isRandom):
 AnimationBase(ui)
{
	Load(filePath);
	_originPos = _ui->GetPos();
	if (isRandom) {
		_delayTime = rand() % _cycleTime;
	}
};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
IterationAnim::~IterationAnim(){

};
//----------------------------------------------------------------------
// @brief �A�j���[�V�����̓ǂݍ���
// @param �t�@�C���p�X
// @return ����
//----------------------------------------------------------------------
void IterationAnim::Load(std::string filePath){
	CFile file(filePath);
	// �t�@�C�����J�����ꍇ
	if (file.Success()) {
		int c = 0;
		const char* p = (const char*)file.Data();
		int size = file.Size();
		while (c < size) {
			c += GetDecNum(&p[c], &_cycleTime);//�I�����Ԃ��擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &_delayTime); //�x�����Ԃ��擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &_movePos.x); //x���W���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &_movePos.y); //y���W���擾
			c += SkipSpace(&p[c], &p[size]); // �󔒂�R���g���[���R�[�h���X�L�b�v����
		}
	}
	else {
		DebugError();
	}
}
//----------------------------------------------------------------------
// @brief �X�V����
// @return �����������ǂ���
//----------------------------------------------------------------------
void IterationAnim::Update(){
	Vector3D pos;
	// sin�g���g���č��W���X�V
	pos.x = _originPos.x +  _movePos.x * sin(2 * DX_PI * ((GetNowCount() + _delayTime) - _currentTime) / _cycleTime);
	pos.y = _originPos.y +  _movePos.y * sin(2 * DX_PI * ((GetNowCount() + _delayTime) - _currentTime) / _cycleTime);
	_ui->SetPos(pos);
};