#include "../Base/ObjectBase.h"
#include "../AppFrame/source/System/Header/Collision/MyStructure.h"
class Goal : public ObjectBase {
public:
	Goal(const std::string& name, const Vector3D& pos, const Vector3D& rotation);
	~Goal();
	
	bool Update()override;
	bool DebugDraw()override;

	OBB* GetOBB() const { return _obb; }
protected:
	OBB* _obb;
	class ModelBase* _model;
};