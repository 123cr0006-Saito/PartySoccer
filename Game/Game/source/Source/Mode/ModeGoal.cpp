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

	UIManager* ui = dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"));

	int count = 0;
	for(auto&& list : _ui){
		ui->Add(list.first, 10000 + count, list.second);
		count++;

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
	CFile file("Data/GoalUIParam.csv");
	// ファイルが開けた場合
	if (file.Success()) {
		int c = 0;
		const char* p = (const char*)file.Data();
		int size = file.Size();
		while (c < size) {
			std::string name, handlePath, animPath;
			int handle;
			Vector3D pos, center, extrate;
			float angle, alpha;
			c += GetString(&p[c], &name); // タグを取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetString(&p[c], &handlePath); // 画像ファイル名を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetString(&p[c], &animPath); // アニメーションファイル名を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &pos.x); //x座標を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &pos.y); //y座標を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &center.x); //中心座用を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &center.y); //中心座用を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &extrate.x); //x拡大率を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &extrate.y); //y拡大率を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &angle); //回転率を取得
			c += SkipSpace(&p[c], &p[size]); // 空白やコントロールコードをスキップする

			handle = LoadGraph(handlePath.c_str());
			alpha = 255;

			UIRotaBase* ui = NEW UIRotaBase(pos, center, extrate, angle, alpha, handle);
			if (animPath != "") {
				LocationAnim* anim = NEW LocationAnim(ui, animPath);
				ui->SetAnimation(anim);
			}

			if(_name == name){
				LocationAnim* anim = NEW LocationAnim(ui, "Data/Goal/AddScoreAnimation.csv");
				ui->SetAnimation(anim);
			}

			_ui.emplace_back(name,ui);
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
	
	nowTime -= 800;
	if(nowTime < 0)return ;

	nowTime -= 1000;
	if (nowTime < 0)return;

	// 点数を右に移動
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