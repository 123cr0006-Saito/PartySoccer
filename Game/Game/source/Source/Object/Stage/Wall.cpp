//----------------------------------------------------------------------
// @filename Wall.cpp
// @author: saito ko
// @explanation
// �ǃN���X
//----------------------------------------------------------------------
#include "../../../Header/Object/Stage/Wall.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../../Header/Manager/CollisionManager.h"
#include "../AppFrame/MemoryLeak.h"
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @param �I�u�W�F�N�g�̖��O
// @param �ʒu
// @param ����
// @return ����
//----------------------------------------------------------------------
Wall::Wall(const std::string& name, const Vector3D& pos, const Vector3D& length) : ObjectBase(name) {
	_obb = NEW OBB(name,pos,this);
	_obb->SetLength(length);
	SuperManager::GetInstance()->GetManager("collisionManager")->Add(_obb);
};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
Wall::~Wall(){
	SuperManager::GetInstance()->GetManager("collisionManager")->Delete(_obb);
};