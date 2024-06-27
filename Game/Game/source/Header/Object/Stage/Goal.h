#include "../Base/ObjectBase.h"
#include "../AppFrame/source/System/Header/Collision/MyStructure.h"
class Goal : public ObjectBase {
public:
	Goal(std::string name, Vector3D pos, Vector3D rotation);
	~Goal();
	
	bool Update()override;
	bool DebugDraw()override;

	OBB* GetOBB() { return _obb; }
protected:
	OBB* _obb;
	class ModelBase* _model;
};