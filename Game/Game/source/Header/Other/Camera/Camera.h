#pragma once
#include "../../../AppFrame/source/System/Header/Function/Vector3D.h"
#include <utility>
class Camera
{
public:
	Camera();
	~Camera();
	bool Update();
	bool Draw();

	bool SpringDamperSystem(Vector3D targetPos);

private:
	std::pair<Vector3D, Vector3D> _pos; // <カメラ位置,注視点>
	Vector3D _speed;
	class PlayerManeger* _player;
};

