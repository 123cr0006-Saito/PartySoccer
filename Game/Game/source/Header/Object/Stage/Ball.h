#include "../Base/ObjectBase.h"
#include "../AppFrame/source/System/Header/Collision/MyStructure.h"
class Ball : public ObjectBase {
	public:
	Ball(const std::string& name);
	~Ball();
	
	bool Update()override;
	bool UpdateEnd()override;
	bool DebugDraw()override;

	bool GetIsShoot() const { return _isShoot; }
	Sphere* GetSphere() const { return _sphere; }
	float GetSpeed() const { return _speed; }

	void SetPos(const Vector3D& pos) override { _pos = pos; _sphere->pos = pos; };
	void SetSpeed(const float speed) { _speed = speed; }
	void AddSpeed(const float speed) { _speed += speed; }
	void SetPosToOldPos() { _pos = _oldPos; }

	void SetForwardVec(const Vector3D& forwardVec) ;
protected: 
	class ModelBase* _model;
	bool _isShoot;
	Sphere* _sphere;
	Vector3D _dirVec;
	float _speed;
	int _gravity;
};