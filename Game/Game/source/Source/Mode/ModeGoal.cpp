#include "../../Header/Mode/ModeGoal.h"
#include "../AppFrame/source/Mode/ModeServer.h"
#include "../../Header/Other/Score.h"
#include "../AppFrame/source/CFile/CFile.h"
#include "../AppFrame/source/Application/UtilMacro.h"
#include "../AppFrame/MemoryLeak.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/UIManager.h"
#include "../../Header/Mode/ModeGame.h"
#include "../../Header/Other/TimeLimit.h"
#include "../../Header/UI/Score/UIScore.h"
#include "../../Header/UI/Animation/LocationAnim.h"
bool ModeGoal::_isLoadUI = false;

ModeGoal::ModeGoal(std::string name){
	TimeLimit::GetInstance()->Stop();
	_score = Score::GetInstance();
	_superManager = SuperManager::GetInstance();
	for(int i = 0; i < 2; i++){
		_nowScore[i] = _score->GetScore("Goal_" + std::to_string(i+1));
	}
	_score->AddScore(name,1);
	_name = name;
	_currentTime = 0;

	LoadUI();

	for(int i = 0; i < 10; i++){
		_numHandle[i] = LoadGraph(("Res/UI/Number/timer_0" + std::to_string(i) + ".png").c_str());
	}

	for(auto&& list : _ui){
		_superManager->GetManager("uiManager")->Add(list.second);

		if(list.first == "Goal_1"){
			list.second->SetHandle(_numHandle[_nowScore[0]]);
		}
		else if(list.first == "Goal_2"){
			list.second->SetHandle(_numHandle[_nowScore[1]]);
		}
	}

};

ModeGoal::~ModeGoal(){
	_score = nullptr;
};

bool	ModeGoal::Initialize(){
	_currentTime = GetNowCount();
	return true;
};

void ModeGoal::LoadUI(){
	int count = 0;
	CFile file("Data/GoalUIParam.csv");
	// �t�@�C�����J�����ꍇ
	if (file.Success()) {
		int c = 0;
		const char* p = (const char*)file.Data();
		int size = file.Size();
		while (c < size) {
			std::string name, handlePath, animPath;
			int handle;
			Vector3D pos, center, extrate;
			float angle, alpha;
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

			UIRotaBase* ui = NEW UIRotaBase(name, pos, center, extrate, angle, alpha, handle,10000+count);
			if (animPath != "") {
				LocationAnim* anim = NEW LocationAnim(ui, animPath);
				ui->SetAnimation(anim);
			}

			if(_name == name){
				LocationAnim* anim = NEW LocationAnim(ui, "Data/Goal/AddScoreAnimation.csv");
				ui->SetAnimation(anim);
			}

			_ui.emplace_back(name,ui);
			count++;
		}
	}
	else {
		DebugErrar();
	}
};

bool ModeGoal::Terminate(){
	for (auto&& list : _ui) {
		_superManager->GetManager("uiManager")->Del(list.first);
	}
	return true;
};

bool ModeGoal::Process(){
	AnimationProcess();
	return true;
};

void ModeGoal::AnimationProcess(){
	int nowTime = GetNowCount() - _currentTime;

	// �����ɃA�j���[�V��������������
	
	nowTime -= 800;
	if(nowTime < 0)return ;

	nowTime -= 1000;
	if (nowTime < 0)return;

	// �_�����E�Ɉړ�
	for(auto&& list : _ui){
		if(list.first == _name){
			list.second->SetHandle(_numHandle[_score->GetScore(_name)]);
		}
	}

	nowTime -= 1500;
	if (nowTime < 0)return;

	if(nowTime > 0){
		ModeServer::GetInstance()->Del(this);
		ModeGame* mode = dynamic_cast<ModeGame*>(ModeServer::GetInstance()->Get("ModeGame"));
		mode->ReSetGame();
	}
};

bool	ModeGoal::Render(){
	return true;
};