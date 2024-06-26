#include "../Base/ObjectBase.h"
#include "../AppFrame/source/System/Header/Collision/MyStructure.h"
class Ball : public ObjectBase {
	public:
	Ball(std::string name);
	~Ball();
	bool Init()override;
	bool Update()override;
	bool UpdateEnd()override;
	bool DebugDraw()override;

	bool GetIsShoot() { return _isShoot; }
	const Sphere* GetSphere() { return _sphere; }
	const float GetSpeed() { return _speed; }

	void SetSpeed(float speed) { _speed = speed; }
	void AddSpeed(float speed) { _speed += speed; }
	void SetPosToOldPos() { _pos = _oldPos; }

	void SetForwardVec(Vector3D forwardVec) ;
protected: 
	class ModelBase* _model;
	bool _isShoot;
	Sphere* _sphere;
	Vector3D _dirVec;
	float _speed;
	int _glavity;
};