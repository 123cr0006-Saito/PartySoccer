#include "../Base/ObjectBase.h"
class Ball : public ObjectBase {
	public:
	Ball(std::string name);
	~Ball();
	bool Init()override;
	bool Update()override;
};