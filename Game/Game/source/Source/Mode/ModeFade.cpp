//----------------------------------------------------------------------
// @filename ModeFade.cpp
// @date: 2024/02/29
// @author: saito ko
// @explanation
// ステージ遷移時にフェードイン、フェードアウトを行うためのクラス
//----------------------------------------------------------------------
#include "../../Header/Mode/ModeFade.h"
#include "../AppFrame/source/Mode/ModeServer.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/UIManager.h"
#include "../../Header/UI/UIFade.h"
#include "../AppFrame/MemoryLeak.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param time フェード時間
// @param isFadeIn フェードインかフェードアウトか
//----------------------------------------------------------------------
ModeFade::ModeFade(int time,bool isFadeIn) {
	_currentTime = GetNowCount();
	_fadeTime = time;
	_isFadeIn = isFadeIn;
	UIFade* ui = NEW UIFade(GetColor(0,0,0));
	_alphaFade = ui->LinkAlpha();
	// サーバーに追加
	UIManager* uiManager = dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"));
	uiManager->Add("Fade", 999999, ui);
	if (isFadeIn) {
		(*_alphaFade) = 255;
	}
	else {
		(*_alphaFade) = 0;
	}
};

ModeFade::~ModeFade() {
	UIManager* uiManager = dynamic_cast<UIManager*>(SuperManager::GetInstance()->GetManager("uiManager"));
	uiManager->Del("Fade");
}
//----------------------------------------------------------------------
// @brief 初期化
// @return 成功しているか
//----------------------------------------------------------------------
bool ModeFade::Initialize() {
	if (!base::Initialize()) { return false; }
	return true;
};
//----------------------------------------------------------------------
// @brief 終了処理
// @return 成功しているか
//----------------------------------------------------------------------
bool ModeFade::Terminate() {
	base::Terminate();
	return true;
};
//----------------------------------------------------------------------
// @brief 更新処理
// @return 成功しているか
//----------------------------------------------------------------------
bool ModeFade::Process() {
	base::Process();
	if (_isFadeIn) {
	    // FadeIn
		(*_alphaFade) = Easing::Linear(GetNowCount() - _currentTime,255,0,_fadeTime);
	}
	else {
		// FadeOut
		(*_alphaFade) = Easing::Linear(GetNowCount() - _currentTime, 0, 255, _fadeTime);
	}

	// 時間経過で削除
	if (GetNowCount() - _currentTime > _fadeTime) {
		ModeServer::GetInstance()->Del(this);
	}

	return true;
};
//----------------------------------------------------------------------
// @brief 描画処理
// @return 成功しているか
//----------------------------------------------------------------------
bool ModeFade::Render() {
	return true;
};