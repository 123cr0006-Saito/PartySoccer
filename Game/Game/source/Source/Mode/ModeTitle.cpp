#include "../../Header/Mode/ModeTitle.h"
#include "../AppFrame/source/CFile/CFile.h"
#include "../AppFrame/source/Mode/ModeServer.h"
#include "../../Header/Mode/ModeFadeComeBack.h"
#include "../../Header/Mode/ModeSelectPlayer.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/UIManager.h"
#include "../AppFrame/MemoryLeak.h"
ModeTitle::ModeTitle(){

};

ModeTitle::~ModeTitle(){

};

bool	ModeTitle::Initialize(){
	
	CFile file("Data/UITitleParam.csv");
	// �t�@�C�����J�����ꍇ
	if (file.Success()) {
		int c = 0;
		const char* p = (const char*)file.Data();
		int size = file.Size();
		while (c < size) {
			std::string handlePath;
			std::string name;
			UIRotaParam ui;
			//UIBase* ui = NEW UIBase();
			c += GetString(&p[c], &name); // �^�O���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetString(&p[c], &handlePath); // �t�@�C�������擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui._pos.x); //x���W���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui._pos.y); //y���W���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui._center.x); //���S���p���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui._center.y); //���S���p���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui._extrate.x); //x�g�嗦���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui._extrate.y); //y�g�嗦���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui._angle); //��]�����擾
			c += SkipSpace(&p[c], &p[size]); // �󔒂�R���g���[���R�[�h���X�L�b�v����

			ui._handle = LoadGraph(handlePath.c_str());
			ui._alpha = 255;
			_uiParam[name] = ui;
		}
	}
	else {
		DebugErrar();
	}

	_superManager = SuperManager::GetInstance();
	UIManager* ui = dynamic_cast<UIManager*>(_superManager->GetManager("uiManager"));
	int loopCount = 0;
	for (auto&& list : _uiParam) {
		UIRotaBase* base = NEW UIRotaBase(list.second);
		_ui[list.first] = base->GetParam();
		// �T�[�o�[�ɒǉ�
		ui->Add(list.first, 100 + loopCount, base);
		loopCount++;
	}

	for(int i = 0; i < 4 ; i ++){
		_handleShiftValue[i] = rand()%2000;
	}

	_input = NEW XInput(PLAYER_1);
	return true;
};

bool	ModeTitle::Terminate(){
	delete _input;
	UIManager* ui = dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"));
	for (auto&& list : _ui) {
		ui->Del(list.first);
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

	for(int i = 0; i < 4; i++){
		_ui["Player_"+std::to_string(i)]->_pos.y = _uiParam["Player_" + std::to_string(i)]._pos.y + 50 * sin(2*DX_PI_F*(GetNowCount() + _handleShiftValue[i]) / 2000.0f);
	}
	return true;
};

bool	ModeTitle::Render(){
	return true;
};
