//----------------------------------------------------------------------
// @filename Stage.cpp
// @author: saito ko
// @explanation
// �I�u�W�F�N�g���Ǘ�����N���X
//----------------------------------------------------------------------
#include "../../../Header/Object/Stage/Stage.h"
#include "../../../Header/Manager/RenderManager.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../AppFrame/source/System/Header/Resource/ResourceServer.h"
#include "../../../Header/Model/Base/ModelBase.h"
#include "../AppFrame/MemoryLeak.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param �I�u�W�F�N�g�̖��O
// @return ����
//----------------------------------------------------------------------
Stage::Stage(std::string name) : ObjectBase(name) {
	int handle = ResourceServer::MV1LoadModel("Stage","Res/Model/Stage/Stadium.mv1");
	for (int i = 0; i < 3; i++) {
		MV1SetFrameVisible(handle, 351 + i, false);// �g�p���Ȃ��t���[���̔ԍ����w��@��\���ɐݒ�
	}

	_model = NEW ModelBase(name, 1,handle);
	_model->SetPos(_pos);
	SuperManager::GetInstance()->GetManager("renderManager")->Add(_model);
};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
Stage::~Stage() {
	SuperManager::GetInstance()->GetManager("renderManager")->Delete(_model);
};
//----------------------------------------------------------------------
// @brief �X�V����
// @return �����������ǂ���
//----------------------------------------------------------------------
bool Stage::Update() {
	return true;
};