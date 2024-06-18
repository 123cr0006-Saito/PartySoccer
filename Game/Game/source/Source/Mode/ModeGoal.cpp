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

std::map<std::string,UIRotaParam> ModeGoal::_uiParam;

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
		UIRotaBase* base = NEW UIRotaBase(list.second);
		_ui[list.first] = base->GetParamPtr();
		_ui[list.first]->_alpha = 0;
		if(count > 2){
			_ui[list.first]->_handle = _numHandle[_nowScore[count - 3]];
		}
		// サーバーに追加
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
	// ファイルが開けた場合
	if (file.Success()) {
		int c = 0;
		const char* p = (const char*)file.Data();
		int size = file.Size();
		while (c < size) {
			std::string handlePath;
			std::string name;
			UIRotaParam ui;
			//UIBase* ui = NEW UIBase();
			c += GetString(&p[c], &name); // タグを取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetString(&p[c], &handlePath); // ファイル名を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui._pos.x); //x座標を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui._pos.y); //y座標を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui._center.x); //中心座用を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui._center.y); //中心座用を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui._extrate.x); //x拡大率を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui._extrate.y); //y拡大率を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &ui._angle); //回転率を取得
			c += SkipSpace(&p[c], &p[size]); // 空白やコントロールコードをスキップする

			ui._handle = LoadGraph(handlePath.c_str());
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
	int nowTime = GetNowCount() - _currentTime;

	// ここにアニメーション処理を書く
	// 帯を大きくする
	_ui["obi"]->_alpha = 255;
	Easing::CallingFunction(&_ui["obi"]->_extrate.y,nowTime,0,1,500,Easing::OutSine);
	nowTime -= 800;
	if(nowTime < 0)return ;
	// 点数版を右に移動
	Easing::CallingFunction(&_ui["scoreBoard_01"]->_alpha, nowTime, 0, 255, 200, Easing::Linear);
	Easing::CallingFunction(&_ui["scoreBoard_01"]->_pos.x,nowTime,400,600,500,Easing::InQuad);

	Easing::CallingFunction(&_ui["scoreBoard_02"]->_alpha, nowTime, 0, 255, 200, Easing::Linear);
	Easing::CallingFunction(&_ui["scoreBoard_02"]->_pos.x, nowTime, 1520, 1320, 500, Easing::InQuad);

	_ui["score_01"]->_pos.x = _ui["scoreBoard_01"]->_pos.x + _ui["scoreBoard_01"]->_center.x/2;
	_ui["score_01"]->_pos.y = _ui["scoreBoard_01"]->_pos.y + _ui["scoreBoard_01"]->_center.y/2;
	_ui["score_02"]->_pos.x = _ui["scoreBoard_02"]->_pos.x + _ui["scoreBoard_01"]->_center.x/2;
	_ui["score_02"]->_pos.y = _ui["scoreBoard_02"]->_pos.y + _ui["scoreBoard_01"]->_center.y/2;

	Easing::CallingFunction(&_ui["score_01"]->_alpha, nowTime, 0, 255, 200, Easing::Linear);
	Easing::CallingFunction(&_ui["score_02"]->_alpha, nowTime, 0, 255, 200, Easing::Linear);

	nowTime -= 1000;
	if (nowTime < 0)return;

	// 点数を右に移動
	if(_name == "Goal_1"){
		_ui["score_01"]->_handle = _numHandle[_score->GetScore(_name)];
		Easing::CallingFunction(&_ui["score_01"]->_extrate.x, nowTime, 1.3f, 1.0f, 300, Easing::Linear);
		Easing::CallingFunction(&_ui["score_01"]->_extrate.y, nowTime, 1.3f, 1.0f, 300, Easing::Linear);
	}
	else{
		_ui["score_02"]->_handle = _numHandle[_score->GetScore(_name)];
		Easing::CallingFunction(&_ui["score_02"]->_extrate.x, nowTime, 1.3f, 1.0f, 300, Easing::Linear);
		Easing::CallingFunction(&_ui["score_02"]->_extrate.y, nowTime, 1.3f, 1.0f, 300, Easing::Linear);
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