#include "../Base/ObjectBase.h"
class Stage : public ObjectBase
{
public:
	Stage();
	~Stage();
	virtual bool Init()override;
	virtual bool Update()override;
};