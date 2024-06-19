#include "../../../Header/UI/Animation/IterationAnim.h"
#include "../AppFrame/source/CFile/CFile.h"
#include "../AppFrame/source/Application/UtilMacro.h"
IterationAnim::IterationAnim(UIRotaBase* ui,std::string filePath,bool isRandom):
 AnimationBase(ui)
{
	Load(filePath);
	_originPos = _ui->GetPos();
	if (isRandom) {
		_delayTime = rand() % _cycleTime;
	}
};

IterationAnim::~IterationAnim(){

};

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
		DebugErrar();
	}
}

void IterationAnim::Update(){
	Vector3D pos;
	pos.x = _originPos.x +  _movePos.x * sin(2 * DX_PI * ((GetNowCount() + _delayTime) - _currentTime) / _cycleTime);
	pos.y = _originPos.y +  _movePos.y * sin(2 * DX_PI * ((GetNowCount() + _delayTime) - _currentTime) / _cycleTime);
	_ui->SetPos(pos);
};