//----------------------------------------------------------------------
// @filename ModeGame.cpp
// @date: 2023/12/14
// @author: saito ko
// @explanation
// ボスバトル以外のステージを管理するクラス
//----------------------------------------------------------------------
#include "../../Header/Mode/ModeGame.h"
//----------------------------------------------------------------------
// @brief 初期化処理
// @return 成功しているか
//----------------------------------------------------------------------
bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }
	return true;
}
//----------------------------------------------------------------------
// @brief 削除処理
// @return 無し
//----------------------------------------------------------------------
bool ModeGame::Terminate() {
	base::Terminate();
	return true;
}
//----------------------------------------------------------------------
// @brief 更新処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool ModeGame::Process() {
	base::Process();
	ModeServer::GetInstance()->SkipProcessUnderLayer();
	ModeServer::GetInstance()->PauseProcessUnderLayer();
	return true;
}
//----------------------------------------------------------------------
// @brief 描画処理
// @return 成功したかどうか
//----------------------------------------------------------------------
bool ModeGame::Render() {

	base::Render();
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);
	return true;
}
