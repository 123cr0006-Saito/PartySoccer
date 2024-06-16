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

bool ModeGoal::_isLoadUI = false;

std::map<std::string,UIBase::UIParam> ModeGoal::_uiParam;

ModeGoal::ModeGoal(std::string name){
	TimeLimit::GetInstance()->Stop();
	_score = Score::GetInstance();

	for(int i = 0; i < 2; i++){
		_nowScore[i] = _score->GetScore("Goal_" + std::to_string(i+1));
	}
	_score->AddScore(name,1);
	_name = name;
	_currentTime = 0;
	if(!_isLoadUI){
		LoadUIOnce();
		_isLoadUI = true;
	}

	for(int i = 0; i < 10; i++){
		_numHandle[i] = LoadGraph(("Res/UI/Number/timer_0" + std::to_string(i) + ".png").c_str());
	}

	UIManager* ui = dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"));
	int count  = 0;
	for (auto&& list :_uiParam) {
		UIBase* base = NEW UIBase(list.second);
		_ui[list.first] = base->GetParam();
		if(count > 2){
			_ui[list.first]->handle = _numHandle[_nowScore[count - 3]];
		}
		// �T�[�o�[�ɒǉ�
		ui->Add(list.first, 10000 + count, base);
		count++;
	}
};

ModeGoal::~ModeGoal(){
	_score = nullptr;
};

bool	ModeGoal::Initialize(){
	_currentTime = GetNowCount();
	return true;
};

void ModeGoal::LoadUIOnce(){
	CFile file("Data/GoalUIParam.csv");
	// �t�@�C�����J�����ꍇ
	if (file.Success()) {
		int c = 0;
		const char* p = (const char*)file.Data();
		int size = file.Size();
		while (c < size) {
			std::string handlePath;
			std::string name;
			UIBase::UIParam ui;
			//UIBase* ui = NEW UIBase();
			c += GetString(&p[c], &name); // �^�O���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetString(&p[c], &handlePath); // �t�@�C�������擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui.pos.x); //x���W���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui.pos.y); //y���W���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui.center.x); //���S���p���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui.center.y); //���S���p���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui.extrate.x); //x�g�嗦���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui.extrate.y); //y�g�嗦���擾
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui.angle); //��]�����擾
			c += SkipSpace(&p[c], &p[size]); // �󔒂�R���g���[���R�[�h���X�L�b�v����

			ui.handle = LoadGraph(handlePath.c_str());
			_uiParam[name] = ui;
		}
	}
	else {
		DebugErrar();
	}
};

bool	ModeGoal::Terminate(){
	UIManager* ui = dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"));
	for (auto&& list : _ui) {
		ui->Del(list.first);
	}
	return true;
};

bool	ModeGoal::Process(){
	AnimationProcess();
	return true;
};

void ModeGoal::AnimationProcess(){
	auto easing = [](float* value ,float nowTime, float start, float end, float maxTime,
							  float (*easing)(float, float, float, float))
	{
		if (nowTime > 0) {
			if (nowTime > maxTime) {
				nowTime = maxTime;
			}
			(*value) = easing(nowTime, start, end, maxTime);
		}
	};
	int nowTime = GetNowCount() - _currentTime;



	// �����ɃA�j���[�V��������������
	// �т�傫������
	_ui["obi"]->alpha = 255;
	easing(&_ui["obi"]->extrate.y,nowTime,0,1,500,Easing::OutSine);
	nowTime -= 800;
	if(nowTime < 0)return ;
	// �_���ł��E�Ɉړ�
	easing(&_ui["scoreBoard_01"]->alpha, nowTime, 0, 255, 200, Easing::Linear);
	easing(&_ui["scoreBoard_01"]->pos.x,nowTime,400,600,500,Easing::InQuad);

	easing(&_ui["scoreBoard_02"]->alpha, nowTime, 0, 255, 200, Easing::Linear);
	easing(&_ui["scoreBoard_02"]->pos.x, nowTime, 1520, 1320, 500, Easing::InQuad);

	_ui["score_01"]->pos.x = _ui["scoreBoard_01"]->pos.x + _ui["scoreBoard_01"]->center.x/2;
	_ui["score_01"]->pos.y = _ui["scoreBoard_01"]->pos.y + _ui["scoreBoard_01"]->center.y/2;
	_ui["score_02"]->pos.x = _ui["scoreBoard_02"]->pos.x + _ui["scoreBoard_01"]->center.x/2;
	_ui["score_02"]->pos.y = _ui["scoreBoard_02"]->pos.y + _ui["scoreBoard_01"]->center.y/2;

	easing(&_ui["score_01"]->alpha, nowTime, 0, 255, 200, Easing::Linear);
	easing(&_ui["score_02"]->alpha, nowTime, 0, 255, 200, Easing::Linear);

	nowTime -= 1000;
	if (nowTime < 0)return;

	// �_�����E�Ɉړ�
	if(_name == "Goal_1"){
		_ui["score_01"]->handle = _numHandle[_score->GetScore(_name)];
		easing(&_ui["score_01"]->extrate.x, nowTime, 1.3f, 1.0f, 300, Easing::Linear);
		easing(&_ui["score_01"]->extrate.y, nowTime, 1.3f, 1.0f, 300, Easing::Linear);
	}
	else{
		_ui["score_02"]->handle = _numHandle[_score->GetScore(_name)];
		easing(&_ui["score_02"]->extrate.x, nowTime, 1.3f, 1.0f, 300, Easing::Linear);
		easing(&_ui["score_02"]->extrate.y, nowTime, 1.3f, 1.0f, 300, Easing::Linear);
	}

	nowTime -= 1500;
	if (nowTime < 0)return;

	if(nowTime > 0){
		ModeServer::GetInstance()->Del(this);
		ModeGame* mode = dynamic_cast<ModeGame*>(ModeServer::GetInstance()->Get("Main"));
		mode->ReSetGame();
	}
};

bool	ModeGoal::Render(){
	return true;
};