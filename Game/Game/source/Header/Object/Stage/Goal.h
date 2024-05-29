#include "../Base/ObjectBase.h"
class Goal : public ObjectBase {
	public:
	Goal(std::string name, Vector3D pos, Vector3D rotation);
	~Goal();
	bool Init()override;
	bool Update()override;
};