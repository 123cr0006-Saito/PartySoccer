//----------------------------------------------------------------------
// @filename UIScore.cpp
// @author: saito ko
// @explanation
// �X�R�A��`�悷��UI�N���X
//----------------------------------------------------------------------
#include "../../../Header/UI/Score/UIScore.h"
#include "../../../Header/Other/Score.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../../Header/Manager/UIManager.h"
#include "../../../Header/Other/Score.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param �ʒu
// @param �`�[����
// @param �X�R�A
// @return ����
//----------------------------------------------------------------------
UIScore::UIScore(Vector3D pos, std::string name, Score* score) : 
	UIRotaBase(),
	_teamName(name),
	_score(score)
{
	_pos = pos;
	_layer = 15;
	_name = "scoreNum";
	for(int i = 0; i < 10; i++){
		_scoreHandle[i] = LoadGraph(("Res/UI/Number/timer_0" + std::to_string(i) + ".png").c_str());
	}
	int sizeX, sizeY;
	GetGraphSize(_scoreHandle[0], &sizeX, &sizeY);
	_center = Vector3D(sizeX / 2, sizeY / 2, 0);
	SuperManager::GetInstance()->GetManager("uiManager")->Add(this);
};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
UIScore::~UIScore(){

};
//----------------------------------------------------------------------
// @brief �X�V����
// @return ����
//----------------------------------------------------------------------
void UIScore::Update(){

};
//----------------------------------------------------------------------
// @brief �`�揈��
// @return ����
//----------------------------------------------------------------------
void UIScore::Draw(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	float rate = _screenSize.x / 1920;
	int num = _score->GetScore(_teamName);
	int w = 0;
	if(num >= 10) w = _center.x * rate;
	do
	{
		DrawRotaGraph3(_pos.x * rate + w, _pos.y * rate, _center.x * rate, _center.y * rate, _extrate.x * rate, _extrate.y * rate, _angle, _scoreHandle[num%10], true);
		w -= _center.x * 2 * rate;
		num /= 10;
	}
	while(num > 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
};
