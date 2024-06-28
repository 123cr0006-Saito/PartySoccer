//----------------------------------------------------------------------
// @filename ModeGoal.cpp
// @author: saito ko
// @explanation
// ゴール時の演出を行うクラス
//----------------------------------------------------------------------
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
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param 得点を入れたチームの名前
// @return 無し
//----------------------------------------------------------------------
ModeGoal::ModeGoal(const std::string& name){
	TimeLimit::GetInstance()->Stop();
	_score = Score::GetInstance();
	_superManager = SuperManager::GetInstance();
	//点数の取得
	for(int i = 0; i < 2; i++){
		_nowScore[i] = _score->GetScore("Goal_" + std::to_string(i+1));
	}
	//得点を追加
	_score->AddScore(name,1);
	_name = name;
	_currentTime = 0;
	//UIの読み込み
	LoadUI();
	//点数の画像を読み込む
	for(int i = 0; i < 10; i++){
		std::string num = std::to_string(i);
		_numHandle[i] = ResourceServer::LoadGraph("Score_" + num, ("Res/UI/Number/timer_0" + num + ".png").c_str());
	}
	//UIを追加
	for(auto&& list : _ui){
		_superManager->GetManager("uiManager")->Add(list.second);

		// チームの得点を設定
		if(list.first == "Goal_1"){
			list.second->SetHandle(_numHandle[_nowScore[0]]);
		}
		else if(list.first == "Goal_2"){
			list.second->SetHandle(_numHandle[_nowScore[1]]);
		}
	}

};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
ModeGoal::~ModeGoal(){
	_score = nullptr;
};
//----------------------------------------------------------------------
// @brief 初期化処理
// @return 無し
//----------------------------------------------------------------------
bool ModeGoal::Initialize(){
	_currentTime = GetNowCount();
	return true;
};
//----------------------------------------------------------------------
// @brief UIの読み込み
// @return 無し
//----------------------------------------------------------------------
void ModeGoal::LoadUI(){
	int count = 0;
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

			handle = ResourceServer::LoadGraph(name,handlePath.c_str());
			alpha = 255;
			//UIクラスの作成
			UIRotaBase* ui = NEW UIRotaBase(name, pos, center, extrate, angle, alpha, handle,10000+count);
			if (animPath != "") {
				//アニメーションの読み込み
				LocationAnim* anim = NEW LocationAnim(ui, animPath);
				ui->SetAnimation(anim);
			}

			if(_name == name){
				//ゴールしたチームは別のアニメーションを追加読み込み
				LocationAnim* anim = NEW LocationAnim(ui, "Data/Goal/AddScoreAnimation.csv");
				ui->SetAnimation(anim);
			}

			_ui.emplace_back(name,ui);
			count++;
		}
	}
	else {
		DebugError();
	}
};
//----------------------------------------------------------------------
// @brief 終了処理
// @return 成功しているか
//----------------------------------------------------------------------
bool ModeGoal::Terminate(){
	for (auto&& list : _ui) {
		_superManager->GetManager("uiManager")->DeleteName(list.first);
	}
	return true;
};
//----------------------------------------------------------------------
// @brief 更新処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool ModeGoal::Process(){
	AnimationProcess();
	return true;
};
//----------------------------------------------------------------------
// @brief アニメーションの更新処理
// @return 成功したかどうか
//----------------------------------------------------------------------
void ModeGoal::AnimationProcess(){
	int nowTime = GetNowCount() - _currentTime;

	// ここにアニメーション処理を書く
	// 1.8秒
	nowTime -= 1800;
	if (nowTime < 0)return;

	// 1.8秒後、点数の画像を更新
	for(auto&& list : _ui){
		if(list.first == _name){
			list.second->SetHandle(_numHandle[_score->GetScore(_name)]);
		}
	}
	//3.3秒
	nowTime -= 1500;
	if (nowTime < 0)return;
	//アニメーションが終了したので削除
	if(nowTime > 0){
		ModeServer::GetInstance()->Del(this);
		//座標や状態を初期化
		dynamic_cast<ModeGame*>(ModeServer::GetInstance()->Get("ModeGame"))->ReSetGame();
	}
};
//----------------------------------------------------------------------
// @brief 描画処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool ModeGoal::Render(){
	return true;
};