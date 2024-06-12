#include "../Base/ObjectBase.h"
#include "../AppFrame/source/System/Header/Collision/MyStructure.h"
class Ball : public ObjectBase {
	public:
	Ball(std::string name);
	~Ball();
	bool Init()override;
	bool Update()override;
	bool DebugDraw()override;
	bool GetIsShoot() { return _isShoot; }
	void SetSpeed(float speed) { _speed = speed; }
	void AddSpeed(float speed) { _speed += speed; }
	void SetForwardVec(Vector3D forwardVec) ;
	Vector3D GetForwardVec() { return _forwardVec; }
protected: 	
	bool _isShoot;
	Sphere* _sphere;
	Vector3D _dirVec;
	Vector3D _forwardVec;
	float _speed;
	int _glavity;
};