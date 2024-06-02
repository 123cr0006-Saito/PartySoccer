#pragma once
#include "../../../AppFrame/source/System/Header/Function/Vector3D.h"
#include "../../../Header/Manager/PlayerManeger.h"
#include <utility>
// #define LERP 0;
class Camera
{
	public:
	Camera();
	~Camera();
	bool Update();
	bool Draw();

	bool SpringDamperSystem(Vector3D targetPos);

	private:
	std::pair<Vector3D, Vector3D> _pos; // <ƒJƒƒ‰ˆÊ’u,’Ž‹“_>
	Vector3D _speed;
	PlayerManeger* _player;

#ifdef LERP
	float _lerp;
#endif
};

