//----------------------------------------------------------------------
// @filename ModeTitle.cpp
// @author: saito ko
// @explanation
// �I�u�W�F�N�g���Ǘ�����N���X
//----------------------------------------------------------------------
#include "../../Header/Mode/ModeTitle.h"
#include "../AppFrame/source/CFile/CFile.h"
#include "../AppFrame/source/Mode/ModeServer.h"
#include "../../Header/Mode/ModeFadeComeBack.h"
#include "../../Header/Mode/ModeSelectPlayer.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/UIManager.h"
#include "../AppFrame/MemoryLeak.h"
#include "../../Header/UI/Animation/IterationAnim.h"
#include "../../Header/UI/Animation/LocationAnim.h"
#include "../AppFrame/source/Application/Global.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
ModeTitle::ModeTitle(){

};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
ModeTitle::~ModeTitle(){

};
//----------------------------------------------------------------------
// @brief ����������
// @return �������Ă��邩
//----------------------------------------------------------------------
bool ModeTitle::Initialize(){
	_superManager = SuperManager::GetInstance();
	int loopCount = 0;
	CFile file("Data/UITitleParam.csv");
	// �t�@�C�����J�����ꍇ
	if (file.Success()) {
		int c = 0;
		const char* p = (const char*)file.Data();
		int size = file.Size();
		while (c < size) {
			std::string name,handlePath,animPath;
			int handle;
			Vector3D pos, center, extrate;
			float angle,alpha;
			c += GetString(&p[c], &name); // �^�O���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetString(&p[c], &handlePath); // �摜�t�@�C�������擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetString(&p[c], &animPath); // �A�j���[�V�����t�@�C�������擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &pos.x); //x���W���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &pos.y); //y���W���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &center.x); //���S���p���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &center.y); //���S���p���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &extrate.x); //x�g�嗦���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &extrate.y); //y�g�嗦���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &angle); //��]�����擾
			c += SkipSpace(&p[c], &p[size]); // �󔒂�R���g���[���R�[�h���X�L�b�v����

			handle = ResourceServer::LoadGraph(name,handlePath.c_str());
			alpha = 255;

			UIRotaBase* ui = NEW UIRotaBase(name,pos, center, extrate, angle, alpha, handle,100+loopCount);
			if(animPath != ""){
				IterationAnim* anim = NEW IterationAnim(ui, animPath,true);
				ui->SetAnimation(anim);
			}
			_superManager->GetManager("uiManager")->Add(ui);
			_uiName.push_back(name);
			loopCount++;
		}
	}
	else {
		DebugErrar();
	}

	
	//�p�b�h�̍쐬
	_input = NEW XInput(PLAYER_1);
	//BGM��ݒ�
	global._soundServer->DirectPlay("BGM_Title");
	return true;
};
//----------------------------------------------------------------------
// @brief �I������
// @return �������Ă��邩
//----------------------------------------------------------------------
bool ModeTitle::Terminate(){
	delete _input;
	// UI���폜
	for(auto&& name : _uiName){
		SuperManager::GetInstance()->GetManager("uiManager")->DeleteName(name);
	}
	return true;
};
//----------------------------------------------------------------------
// @brief �X�V����
// @return �����������ǂ���
//----------------------------------------------------------------------
bool ModeTitle::Process(){
	_input->Input();
	//A�{�^���ŃZ���N�g��ʂɈړ�
	if(_input->GetTrg(XINPUT_BUTTON_A)){
		ModeServer::GetInstance()->Add(NEW ModeSelectPlayer(), 0, "ModeSelectPlayer");
		std::vector<std::string> modeName = {"ModeTitle"};
		ModeServer::GetInstance()->Add(NEW ModeFadeComeBack(1000, modeName, "ModeSelectPlayer", 10, true), 100, "ModeFadeComeBack");
	}

	return true;
};
//----------------------------------------------------------------------
// @brief �`�揈��
// @return �����������ǂ���
//----------------------------------------------------------------------
bool ModeTitle::Render(){
	return true;
};
