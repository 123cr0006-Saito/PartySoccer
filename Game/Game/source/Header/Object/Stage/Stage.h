#include "../Base/ObjectBase.h"
#include "../../AppFrame/source/System/Header/Collision/MyStructure.h"
class Stage : public ObjectBase
{
public:
	Stage(std::string name);
	~Stage();
	virtual bool Update()override;
protected:
	class ModelBase* _model;
};