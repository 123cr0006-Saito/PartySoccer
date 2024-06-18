#include "../../Header/Animation/Animation.h"
#include "../../Header/UI/Base/UIRotaBase.h"
#include "../AppFrame/source/CFile/CFile.h"
#include "../AppFrame/source/Application/UtilMacro.h"
#include "../AppFrame/source/System/Header/Function/Easing.h"
Animation::Animation(class UIRotaBase* parent,std::string filePath):
	_ui(parent),
	_isEnd(false)
{
	Load(filePath);
	_startParam = _ui->GetParam();
	_currentTime = GetNowCount();
};

Animation::~Animation(){
	_ui = nullptr;
};

void Animation::Load(std::string filePath){
	CFile file(filePath);
	// �t�@�C�����J�����ꍇ
	if (file.Success()) {
		int c = 0;
		const char* p = (const char*)file.Data();
		int size = file.Size();
		while (c < size) {
			c += GetDecNum(&p[c], &_endTime);//�I�����Ԃ��擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &_delayTime); //�x�����Ԃ��擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &_endParam._pos.x); //x���W���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &_endParam._pos.y); //y���W���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &_endParam._extrate.x); //x�g�嗦���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &_endParam._extrate.y); //y�g�嗦���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &_endParam._angle); //��]�����擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &_endParam._alpha); //�����x���擾
			c += SkipSpace(&p[c], &p[size]); // �󔒂�R���g���[���R�[�h���X�L�b�v����
		}
	}
	else {
		DebugErrar();
	}
};

bool Animation::Update(){
	if(_isEnd) return true;
	int nowTime = GetNowCount() - _currentTime - _delayTime;
	UIRotaParam param;

	// ���W��ݒ�
	Easing::CallingFunction(&param._pos.x,nowTime,_startParam._pos.x, _endParam._pos.x, _endTime,Easing::Linear);
	Easing::CallingFunction(&param._pos.y, nowTime, _startParam._pos.y, _endParam._pos.y, _endTime, Easing::Linear);
	// �g�嗦��ݒ�
	Easing::CallingFunction(&param._extrate.x, nowTime, _startParam._extrate.x, _endParam._extrate.x, _endTime, Easing::Linear);
	Easing::CallingFunction(&param._extrate.y, nowTime, _startParam._extrate.y, _endParam._extrate.y, _endTime, Easing::Linear);
	// ��]����ݒ�
	Easing::CallingFunction(&param._angle, nowTime, _startParam._angle, _endParam._angle, _endTime, Easing::Linear);
	// �����x��ݒ�
	Easing::CallingFunction(&param._alpha, nowTime, _startParam._alpha, _endParam._alpha, _endTime, Easing::Linear);

	_ui->SetParam(param);
};
