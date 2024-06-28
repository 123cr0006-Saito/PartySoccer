//----------------------------------------------------------------------
// @filename IterationAnim.cpp
// @author: saito ko
// @explanation
// sin波を使ったxとyが移動するアニメーション
//----------------------------------------------------------------------
#include "../../../Header/UI/Animation/IterationAnim.h"
#include "../AppFrame/source/CFile/CFile.h"
#include "../AppFrame/source/Application/UtilMacro.h"
//----------------------------------------------------------------------
// @brief コンストラクタ
// @param UIのインスタンス
// @param ファイルパス
// @param 開始値をランダムにするかどうか
// @return 無し
//----------------------------------------------------------------------
IterationAnim::IterationAnim(UIRotaBase* ui,std::string filePath,bool isRandom):
 AnimationBase(ui)
{
	Load(filePath);
	_originPos = _ui->GetPos();
	if (isRandom) {
		_delayTime = rand() % _cycleTime;
	}
};
//----------------------------------------------------------------------
// @brief デストラクタ
// @return 無し
//----------------------------------------------------------------------
IterationAnim::~IterationAnim(){

};
//----------------------------------------------------------------------
// @brief アニメーションの読み込み
// @param ファイルパス
// @return 無し
//----------------------------------------------------------------------
void IterationAnim::Load(std::string filePath){
	CFile file(filePath);
	// ファイルが開けた場合
	if (file.Success()) {
		int c = 0;
		const char* p = (const char*)file.Data();
		int size = file.Size();
		while (c < size) {
			c += GetDecNum(&p[c], &_cycleTime);//終了時間を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetDecNum(&p[c], &_delayTime); //遅延時間を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &_movePos.x); //x座標を取得
			c += FindString(&p[c], ',', &p[size]); c++; c += GetFloatNum(&p[c], &_movePos.y); //y座標を取得
			c += SkipSpace(&p[c], &p[size]); // 空白やコントロールコードをスキップする
		}
	}
	else {
		DebugError();
	}
}
//----------------------------------------------------------------------
// @brief 更新処理
// @return 成功したかどうか
//----------------------------------------------------------------------
void IterationAnim::Update(){
	Vector3D pos;
	// sin波を使って座標を更新
	pos.x = _originPos.x +  _movePos.x * sin(2 * DX_PI * ((GetNowCount() + _delayTime) - _currentTime) / _cycleTime);
	pos.y = _originPos.y +  _movePos.y * sin(2 * DX_PI * ((GetNowCount() + _delayTime) - _currentTime) / _cycleTime);
	_ui->SetPos(pos);
};