#include "../Base/ObjectBase.h"
class Ball : public ObjectBase {
	public:
	Ball(std::string name);
	~Ball();
	bool Init()override;
	bool Update()override;
	bool GetIsShoot() { return _isShoot; }
protected: 	
	bool _isShoot;
};