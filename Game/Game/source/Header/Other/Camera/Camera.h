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
	class PlayerManager* _player;
	static Camera* _instance;
	std::pair<Vector3D, Vector3D> _pos; // <ƒJƒƒ‰ˆÊ’u,’Ž‹“_>
	Vector3D _targetSpeed;
	Vector3D _cameraSpeed;
	bool _isGame;
};

