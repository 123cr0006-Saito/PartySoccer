//----------------------------------------------------------------------
// @filename UIPlayerParam.cpp
// @author: saito ko
// @explanation
// �I�u�W�F�N�g���Ǘ�����N���X
//----------------------------------------------------------------------
#include "../../Header/UI/UIPlayerParam.h"
#include "../../Header/Manager/SuperManager.h"
#include "../../Header/Manager/UIManager.h"
#include "../../Header/Object/Player/Player.h"
#include "../AppFrame/source/System/Header/Resource/ResourceServer.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param �v���C���[
// @param ���O
// @param �ʒu
// @return ����
//----------------------------------------------------------------------
UIPlayerParam::UIPlayerParam(Player* player,std::string name,Vector3D pos) : 
	UIBase()
{
	// ������
	_player = player;
	_name = name + "Frame";
	_pos = pos;
	_layer = 10;
	_handle = ResourceServer::LoadGraph(name+"Frame",("Res/UI/Frame/" + name + "Frame.png").c_str());

	// �p�����[�^�̐ݒ�
	COLOR_U8 color = GetColorU8(0, 255, 0, 255);

	Vector3D vertexPos[4] = {
		Vector3D(30,0,0),
		Vector3D(30,0,0),
		Vector3D(0,20,0),
		Vector3D(0,20,0)
	};

	float uv[4][2] = {
		{0,0},
		{1,0},
		{0,1},
		{1,1}
	};

	float staminaHeight = -35.0f;
	float shootHeight = 25.0f;

	for(int i = 0; i < 4; i++){
		// �X�^�~�i�Q�[�W�̏�����
		_staminaGauge[i].pos = (pos + Vector3D(0,staminaHeight,0) + vertexPos[i]).toVECTOR();
		_staminaGauge[i].dif = color;
		_staminaGauge[i].u = uv[i][0];
		_staminaGauge[i].v = uv[i][1];
		_staminaGauge[i].rhw = 1.0f;
		// �V���[�g�Q�[�W�̏�����
		_shootGauge[i].pos = (pos + Vector3D(0, shootHeight, 0) + vertexPos[i]).toVECTOR();
		_shootGauge[i].dif = color;
		_shootGauge[i].u = uv[i][0];
		_shootGauge[i].v = uv[i][1];
		_shootGauge[i].rhw = 1.0f;
	}
	SuperManager::GetInstance()->GetManager("uiManager")->Add(this);
};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
UIPlayerParam::~UIPlayerParam(){
	_player = nullptr;
};
//----------------------------------------------------------------------
// @brief �X�V����
// @return ����
//----------------------------------------------------------------------
void UIPlayerParam::Update(){
	int shootGauge = _player->GetPower();
	int staminaGauge = _player->GetStamina();
	for(int i = 1; i <= 3; i+=2){
		_staminaGauge[i].pos.x = _staminaGauge[i-1].pos.x + staminaGauge*1.5;
		_shootGauge[i].pos.x = _shootGauge[i-1].pos.x + shootGauge*3;
	}
};
//----------------------------------------------------------------------
// @brief �`�揈��
// @return ����
//----------------------------------------------------------------------
void UIPlayerParam::Draw(){
	UIBase::Draw();
	unsigned short index[6] = {0,1,2,2,1,3};
	DrawPolygonIndexed2D(_staminaGauge.data(), _staminaGauge.size(),index,2, DX_NONE_GRAPH, false);
	DrawPolygonIndexed2D(_shootGauge.data(), 4, index, 2, DX_NONE_GRAPH, false);
};

