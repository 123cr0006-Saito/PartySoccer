//----------------------------------------------------------------------
// @filename Camera.cpp
// @author: saito ko
// @explanation
// �v���C���[�̒��S�ɃJ������Ǐ]������N���X
//----------------------------------------------------------------------
#include "../../../Header/Other/Camera/Camera.h"
#include "../.../../AppFrame/source/System/Header/Function/Timer.h"
#include "../../../Header/Manager/SuperManager.h"
#include "../../../Header/Manager/PlayerManager.h"
#include "../AppFrame/source/Application/UtilMacro.h"
#include "../AppFrame/source/System/Header/Function/mymath.h"
#include "../../../Header/Object/Player/Player.h"
Camera* Camera::_instance = nullptr;
//----------------------------------------------------------------------
// @brief �R���X�g���N�^
// @return ����
//----------------------------------------------------------------------
Camera::Camera() :
	_isGame(false)
{
	if (_instance != nullptr) {
		DebugError();
		return;
	}
	_instance = this;
	_player = dynamic_cast<PlayerManager*>(SuperManager::GetInstance()->GetManager("playerManager"));
	
};
//----------------------------------------------------------------------
// @brief �f�X�g���N�^
// @return ����
//----------------------------------------------------------------------
Camera::~Camera(){
	_instance = nullptr;
};
//----------------------------------------------------------------------
// @brief �X�V����
// @return �����������ǂ���
//----------------------------------------------------------------------
bool Camera::Update(){
	if(_isGame){
		UpdateGame();
	}	
	else{
		UpdateSelectAndResult();
	}
	return true;
};
//----------------------------------------------------------------------
// @brief �I����ʂƃ��U���g��ʂ̃J�����̍X�V����
// @return ����
//----------------------------------------------------------------------
void Camera::UpdateSelectAndResult(){
	SetCameraPositionAndTarget_UpVecY(_pos.first.toVECTOR(), _pos.second.toVECTOR());
};
//----------------------------------------------------------------------
// @brief ���C���Q�[���̃J�����̍X�V����
// @return ����
//----------------------------------------------------------------------
void Camera::UpdateGame(){

	if(_player == nullptr){
		DebugError();
	}

	std::vector<Player*> player = _player->GetList();

	Vector3D pos;
	for (int i = 0; i < player.size(); i++) {
		pos += player[i]->GetPos();
	}

	Vector3D targetPos = pos / player.size();
	Vector3D cameraPos = targetPos + Vector3D(0, 7000, -6000); // �^�[�Q�b�g���痣�������������𑫂�

	double elapsedTime = Timer::GetInstance()->TimeElapsed();
    SpringDamperSystem(_pos.first,cameraPos, _cameraSpeed,elapsedTime);
	SpringDamperSystem(_pos.second,targetPos,_targetSpeed, elapsedTime);

	SetCameraPositionAndTarget_UpVecY(_pos.first.toVECTOR(), _pos.second.toVECTOR());
};
//----------------------------------------------------------------------
// @brief �J�����̒Ǐ]�V�X�e��
// @return �����������ǂ���
//----------------------------------------------------------------------
bool Camera::SpringDamperSystem(Vector3D& nowPos,const Vector3D& targetPos, Vector3D& speed,const double time){
	float springConstant = 100.0f;
	float dampingConstant = 20.0f;

	Vector3D pos = nowPos - targetPos;
	Vector3D springForce = pos * -springConstant; // �o�l�̗� -kx �e����
	Vector3D dampingForce = speed * -dampingConstant; // �_���p�̗� -cv ��R��
	Vector3D force = springForce + dampingForce; // ����

	speed += force * time;
	nowPos += speed * time;

	return true;
};
//----------------------------------------------------------------------
// @brief �`�揈��
// @return �����������ǂ���
//----------------------------------------------------------------------
bool Camera::Draw(){
	printfDx("x:%f y:%f z:%f\n",_pos.first.x, _pos.first.y, _pos.first.z);
	printfDx("x:%f y:%f z:%f\n", _pos.second.x, _pos.second.y, _pos.second.z);
	printfDx("x:%f y:%f z:%f\n", _cameraSpeed.x, _cameraSpeed.y, _cameraSpeed.z);
	printfDx("x:%f y:%f z:%f\n", _targetSpeed.x, _targetSpeed.y, _targetSpeed.z);
	return true;
};
