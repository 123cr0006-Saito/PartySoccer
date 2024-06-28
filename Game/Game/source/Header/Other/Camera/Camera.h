//----------------------------------------------------------------------
// @filename Camera.cpp
// @author: saito ko
// @explanation
// �J�����𐧌䂷��N���X
//----------------------------------------------------------------------
#pragma once
#include "../../../AppFrame/source/System/Header/Function/Vector3D.h"
#include <utility>
class Camera
{
public:
	Camera();
	~Camera();
	bool Update();
	void UpdateSelectAndResult();
	void UpdateGame();
	bool Draw();

	static Camera* GetInstance() { return _instance; }

	void SetIsGame(const bool isGame) {_isGame = isGame;};
	void SetPos(const Vector3D& pos) { _pos.first = pos; }
	void SetTarget(const Vector3D& target) { _pos.second = target; }
	bool SpringDamperSystem(Vector3D& nowPos,const Vector3D& targetPos, Vector3D& speed,const double time);

private:
	class PlayerManager* _player;//�v���C���[�̏����擾���邽�߂̃|�C���^
	static Camera* _instance;//���̃N���X�̃C���X�^���X
	std::pair<Vector3D, Vector3D> _pos; // <�J�����ʒu,�����_>
	Vector3D _targetSpeed;//�J�����̈ړ����x
	Vector3D _cameraSpeed;//�J�����̈ړ����x
	bool _isGame;//���C���Q�[�����ǂ���
};

