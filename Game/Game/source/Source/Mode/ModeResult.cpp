//----------------------------------------------------------------------
// @filename ModeResult.cpp
// @author: saito ko
// @explanation
// クリア画面のクラス
//----------------------------------------------------------------------
#include "../../Header/Mode/ModeResult.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/PlayerManager.h"
#include "../../Header/Object/Player/Player.h"
#include "../../Header/Mode/ModeTitle.h"
#include "../AppFrame/source/Mode/ModeServer.h"
#include "../../Header/Mode/ModeFadeComeBack.h"
#include "../../Header/Other/Score.h"
#include "../../Header/Other/Camera/Camera.h"
#include "../AppFrame/MemoryLeak.h"
#include "../AppFrame/source/CFile/CFile.h"
#include "../../Header/UI/Animation/LocationAnim.h"
#include "../../Header/Manager/UIManager.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @return 無し
//----------------------------------------------------------------------
ModeResult::ModeResult(){

};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
ModeResult::~ModeResult(){

};
//----------------------------------------------------------------------
// @brief 初期化処理
// @return 成功しているか
//----------------------------------------------------------------------
bool ModeResult::Initialize(){
	_superManager = SuperManager::GetInstance();
	_playerManager = dynamic_cast<PlayerManager*>(_superManager->GetManager("playerManager"));
	_score = Score::GetInstance();
	_camera = Camera::GetInstance();
	_input = NEW XInput(PLAYER_1);
	_currentTime = GetNowCount();
	// 勝者を取得
	_winnerTeam = _score->GetWinner();
	// プレイヤーのリストを取得
	std::vector<Player*> player = _playerManager->GetList();
	int playerNum = player.size();
	// プレイヤーの位置を設定
	for (int i = 0; i < playerNum; i++) {
		if (playerNum == 1) {
			// プレイヤーが一人の場合　中心
			player[i]->SetPos(Vector3D(0, 0, 0));
			player[i]->SetForwardVec(Vector3D(0, 0, -1));
		}
		else {
		// プレイヤーが複数の場合　等間隔
			float dis = 1500.0f;
			float length = dis / (playerNum - 1);
			player[i]->SetPos(Vector3D(-dis / 2 + length * i, 0, 0));
			player[i]->SetForwardVec(Vector3D(0, 0, -1));
		}
	}
	// 勝ったチームの名前が出て来るUIを作成
	int handle,x,y;
	handle = ResourceServer::LoadGraph("WinFrame" + _winnerTeam, ("Res/UI/WinFrame/WinFrame" + _winnerTeam + ".png").c_str());
	GetGraphSize(handle, &x, &y);
	UIRotaBase* ui = NEW UIRotaBase("WinTeam",Vector3D(1920 / 2, -500, 0), Vector3D(x / 2, y / 2, 0), Vector3D(1.0f, 1.0f, 0.0f), 0, 255, handle, 100);
	//アニメーションの設定
	LocationAnim* anim = NEW LocationAnim(ui, "Data/UIAnimation/WinTeamAnimation.csv");
	ui->SetAnimation(anim);
	//追加
	_superManager->GetManager("uiManager")->Add(ui);
	//BGMを変更
	global._soundServer->DirectPlay("BGM_Cheers");
	return true;
};
//----------------------------------------------------------------------
// @brief 終了処理
// @return 成功しているか
//----------------------------------------------------------------------
bool ModeResult::Terminate(){
	_superManager->DeleteName("playerManager");
	_superManager->GetManager("objectManager")->DelAll();
	_superManager->GetManager("uiManager")->DelAll();
	delete _camera;
	delete _score;
	delete _input;
	return true;
};
//----------------------------------------------------------------------
// @brief 更新処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool ModeResult::Process(){
	int nowTime = GetNowCount() - _currentTime;
	_input->Input();
	_camera->Update();
	ModeServer* modeServer = ModeServer::GetInstance();
	// 5秒後にAボタンでタイトルに戻る
	// タイトルに戻る
	if(nowTime > 5000 &&_input->GetTrg(XINPUT_BUTTON_A) && !modeServer->Search("ModeTitle")){
		// モードを変更
		ModeServer::GetInstance()->Add(NEW ModeTitle(), 0, "ModeTitle");
		std::vector<std::string> modeName = {"ModeResult"};
		ModeServer::GetInstance()->Add(NEW ModeFadeComeBack(100, modeName, "ModeTitle",1, true),10,"ModeFadeComeBack");
		ModeServer::GetInstance()->Del(this);
	}
	return true;
};
//----------------------------------------------------------------------
// @brief 描画処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool ModeResult::Render(){
	return true;
};
