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
ModeTitle::ModeTitle(){

};

ModeTitle::~ModeTitle(){

};

bool	ModeTitle::Initialize(){
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

			handle = LoadGraph(handlePath.c_str());
			alpha = 255;

			UIRotaBase* ui = NEW UIRotaBase(name,pos, center, extrate, angle, alpha, handle,100+loopCount);
			if(animPath != ""){
				IterationAnim* anim = NEW IterationAnim(ui, animPath,true);
				ui->SetAnimation(anim);
			}
			_ui[name] = ui;
			loopCount++;
		}
	}
	else {
		DebugErrar();
	}

	_superManager = SuperManager::GetInstance();
	//UIManager* ui = dynamic_cast<UIManager*>(_superManager->GetManager("uiManager"));
	for (auto&& list : _ui) {
		//ui->Add(list.second);
		_superManager->GetManager("uiManager")->Add(list.second);
	}

	_input = NEW XInput(PLAYER_1);
	global._soundServer->DirectPlay("BGM_Title");
	return true;
};

bool	ModeTitle::Terminate(){
	delete _input;
	UIManager* ui = dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"));
	for(auto&& name : _ui){
		ui->Del(name.first);
	}
	return true;
};

bool	ModeTitle::Process(){
	_input->Input();

	if(_input->GetTrg(XINPUT_BUTTON_A)){
		ModeServer::GetInstance()->Add(NEW ModeSelectPlayer(), 0, "ModeSelectPlayer");
		std::vector<std::string> modeName = {"ModeTitle"};
		ModeServer::GetInstance()->Add(NEW ModeFadeComeBack(1000, modeName, "ModeSelectPlayer", 10, true), 100, "ModeFadeComeBack");
	}

	return true;
};

bool	ModeTitle::Render(){
	return true;
};
