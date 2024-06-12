#include "../Base/ObjectBase.h"
#include "../AppFrame/source/System/Header/Collision/MyStructure.h"
class Goal : public ObjectBase {
	public:
	Goal(std::string name, Vector3D pos, Vector3D rotation);
	~Goal();
	bool Init()override;
	bool Update()override;
	bool DebugDraw()override;
protected:
	OBB* _obb;
};